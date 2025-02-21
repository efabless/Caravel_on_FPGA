'''
Created on Oct 3, 2023

@author: Pat Deegan
@copyright: Copyright (C) 2023 Pat Deegan, https://psychogenic.com
'''

from caravelflash.spiflash.serialflash import SerialFlash, SerialFlashManager

FTDIDeviceURIDefault = 'ftdi://ftdi:2232:TG1000a9/2'

flash = SerialFlashManager.get_flash_device(FTDIDeviceURI)

def setReset(flash:SerialFlash, putInReset:bool=True):
    '''
        set the caravel reset switch
        @param flash: the SerialFlash instance
        @param putInReset: boolean, whether to put in or take out of reset
    ''' 
    setTo = 0
    if putInReset:
        setTo = 1
    
    # house-keeping reset command,
    # sent on 'raw' spi port so we don't have pass-through
    flash.spi_port_raw.exchange([0x80, 0xb, setTo])


def upload(flash:SerialFlash, filepath:str, startAddress:int=0):
    '''
        upload contents of binary file to flash
        @param flash: the SerialFlash instance
        @param filepath: the file to source data from
        @param startAddress: (optional) start address (must be on sector bounds)  
    '''
    flashSectorSize = flash.get_erase_size()
    with open(filepath, 'rb') as file:
        contents = file.read()
        contLen = len(contents)
        sectorExtraCount = contLen % flashSectorSize
        if sectorExtraCount:
            print(f"Contents need to be multiples of sector size {flashSectorSize}, padding")
            paddingBytes = bytearray(flashSectorSize - sectorExtraCount)
            contents = bytearray(list(contents))
            contents.extend(paddingBytes)
            contLen = len(contents)
            
        setReset(flash, True)
        flash.erase(startAddress, contLen)
        flash.write(startAddress, contents)
        setReset(flash, False)
        
if __name__ == '__main__':
    print(f"\n\nFlash detected (JEDEC id: {hex(flash.JEDEC_ID)}): capacity is {flash.get_capacity()}")
    features = [
        ('     chip erase', flash.FEAT_CHIPERASE),
        ('           lock', flash.FEAT_LOCK),
        ('   sector erase', flash.FEAT_SECTERASE),
        ('subsector erase', flash.FEAT_SUBSECTERASE),
        ('      unique id', flash.FEAT_UNIQUEID)
        ]

    print("Features")
    for f in features:
        print(f'{f[0]}:  {flash.has_feature(f[1])}')
        