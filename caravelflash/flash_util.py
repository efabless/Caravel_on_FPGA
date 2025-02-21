'''
Created on Oct 3, 2023

@author: Pat Deegan
@copyright: Copyright (C) 2023 Pat Deegan, https://psychogenic.com
'''
import logging
import time
import argparse
from pyftdi.spi import SpiPort
from caravelflash.spi_port import CaravelPassThroughSpiPort
from caravelflash.spiflash.serialflash import SerialFlash, SerialFlashManager
from pyftdi.spi import SpiController
import pyftdi.ftdi

log = logging.getLogger(__name__)

UseCaravelPassThrough = False
# FTDIDeviceURIDefault = 'ftdi://ftdi:2232:TG1000a9/2'
FTDIDeviceURIDefault = 'ftdi://ftdi:2232:TG1108fb/2' # with SensiML
# FTDIDeviceURIDefault = 'ftdi://ftdi:2232:TG11091f/2'
# FTDIDeviceURIDefault = 'ftdi://ftdi:2232:TG110cc6/1'

class FlashUtil:
    def __init__(self):
        self._ctrl = SpiController()
        self._spi_port = None 
        self._flash = None 
        self._ctrl_configured = False 
        self.deviceURI = FTDIDeviceURIDefault 
        
        
    @classmethod
    def listFTDIDevices(cls):
        f = pyftdi.ftdi.Ftdi()
        num = 0
        for devEntry in f.list_devices():
            num += 1
            devDesc = devEntry[0]
            print(f'{devDesc.description} @ USB{devDesc.vid:04X}:{devDesc.pid:04X} ')
            for i in range(1,3):
                print(f'\tftdi://ftdi:2232:{devDesc.sn}/{i}')
        
        return num
        
        
    @property
    def spi_controller(self) -> SpiController:
        
        if self._ctrl_configured:
            return self._ctrl
        
        if not self.deviceURI:
            raise RuntimeError('Provide deviceURI prior to using spi controller')
        try:
            self._ctrl.configure(self.deviceURI)
        except Exception as e:
            log.error(f'Could not access FTDI device? {e}')
            raise RuntimeError(str(e))
        self._ctrl_configured = True
        return self._ctrl
        
        
    @property 
    def spi_port(self):
        if self._spi_port is not None:
            return self._spi_port
        
        self._spi_port = self.spi_controller.get_port(cs=0, freq=1E5, mode=0)
        return self._spi_port
    
    
    @property 
    def flash(self) -> SerialFlash:
        if self._flash is not None:
            return self._flash 
        try:
            rawSPIPort = self.spi_port
        except RuntimeError as e:
            return None 
        
        if UseCaravelPassThrough:
            caravelSPIPortWrapper = CaravelPassThroughSpiPort.newFromSpiPort(rawSPIPort)
        else:
            caravelSPIPortWrapper = rawSPIPort
        
        try:
            self._flash = SerialFlashManager.get_from_spi_port(caravelSPIPortWrapper)
        except Exception as e:
            raise RuntimeError(f"Issue connecting to flash!\n\n{str(e)}")
        
        return self._flash 
    
    
    def caravelHoldInReset(self, setInReset:bool=True):
        val = 0
        if setInReset:
            val = 1
        # house-keeping reset command,
        # sent on 'raw' spi port so we don't have pass-through
        self.spi_port.exchange([0x80, 0xb, val])
        if setInReset:
            time.sleep(0.01) # give it a sec
        
    def getFileContents(self, filepath:str):
        with open(filepath, 'rb') as file:
            contents = file.read()
            file.close()
            return contents
        
    def uploadFile(self, filepath:str, startAddress:int=0):
        '''
            upload contents of binary file to flash
            @param filepath: the file to source data from
            @param startAddress: (optional) start address (must be on sector bounds)  
        '''
        contents = self.getFileContents(filepath)
        return self.upload(contents, startAddress)
    
    def upload(self, contents:bytes, startAddress:int=0):
        '''
            upload bytes to flash
            @param contents: the iterable array of bytes
            @param startAddress: (optional) start address (must be on sector bounds)  
        '''
        flash = self.flash
        flashSectorSize = flash.get_erase_size()
        contLen = len(contents)
        sectorExtraCount = contLen % flashSectorSize
        if sectorExtraCount:
            log.info(f"Contents need to be multiples of sector size {flashSectorSize}, padding")
            paddingBytes = bytearray(flashSectorSize - sectorExtraCount)
            contents = bytearray(list(contents))
            contents.extend(paddingBytes)
            contLen = len(contents)
            
        self.caravelHoldInReset(True)
        print(f"starting erase...")
        flash._erase_chip(0x60,[20,60])
        # flash.erase(startAddress, contLen)
        print(f"starting write...")
        flash.write(startAddress, contents)
        self.caravelHoldInReset(False)
        
    def read(self, size:int, startAddress:int=0):
        self.caravelHoldInReset(True)
        contents = self.flash.read(startAddress, size)
        self.caravelHoldInReset(False)
        return contents 
    
    def readToFile(self, filepath:str, size:int, startAddress:int=0):
        contents = self.read(size, startAddress)
        with open(filepath, 'wb') as file:
            file.write(contents)
            log.info(f'File {filepath} written with {len(contents)} bytes.')
            file.close()
            return len(contents)
        


def getArgParser():
    parser = argparse.ArgumentParser()
    parser.add_argument("--list", action='store_true',
                        required=False,
                    help="list ftdi devices")
    
    parser.add_argument("--capacity", action='store_true',
                        required=False,
                    help="read and dump flash capacity")
    parser.add_argument("--read", type=str,
                        required=False,
                    help="read and dump flash to this file")
    parser.add_argument("--size", type=int,
                        required=False,
                    help="size of flash to fetch for read (defaults to --write file size if doing that)")
    parser.add_argument("--write", type=str,
                        required=False,
                    help="write this file to flash")
    parser.add_argument("--address", type=int, default=0,
                        required=False,
                    help="start address [0]")
    parser.add_argument("--uri", type=str, default=FTDIDeviceURIDefault,
                        required=False,
                    help=f"FTDI device URI [{FTDIDeviceURIDefault}]")
    
    return parser 

def getArguments(parser=None):
    if parser is None:
        parser = getArgParser()
        
    args = parser.parse_args()
    
    return args 

def argumentsValid(args):
    if args.read:
        if not args.write:
            if not args.size:
                log.error('Must provide --size for reads')
                return False
            
            
    if args.read or args.write or args.capacity or args.list:
        return True 

    
            
    return False
            

def main():
    
    logging.basicConfig(level=logging.WARN)
    
    arg_parser = getArgParser()
    args = getArguments(arg_parser)
    if not argumentsValid(args):
        arg_parser.print_help()
        return
    
    if args.list:
        if not FlashUtil.listFTDIDevices():
            print("NO FTDI devices found!")
        return
        
    
    
    flashUtil = FlashUtil()
    flashUtil.deviceURI = args.uri
    
    if flashUtil.flash is None:
        print(f"\n\nCould not access FTDI device {flashUtil.deviceURI}\n\n")
        return
    
    if args.capacity:
        flashUtil.caravelHoldInReset(True)
        capacity = flashUtil.flash.get_capacity()
        log.info(f"Flash capacity: {capacity}")
        print(capacity)
        flashUtil.caravelHoldInReset(False)
        
    if args.write:
        writeContents = flashUtil.getFileContents(args.write)
        
    if args.read:
        if args.size:
            size = args.size 
        else:
            size = len(writeContents) 
        
        print(f"Reading {size} bytes from flash starting at {args.address}, dump to {args.read}")
        flashUtil.readToFile(args.read, size, args.address)
        
    if args.write:
        print(f"Writing {len(writeContents)} to flash starting at {args.address}")
        flashUtil.upload(writeContents, args.address)


if __name__ == '__main__':
    main()
    
    
    


