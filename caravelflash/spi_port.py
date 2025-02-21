'''
Created on Oct 3, 2023

@author: Pat Deegan
@copyright: Copyright (C) 2023 Pat Deegan, https://psychogenic.com
'''


from typing import Iterable, Union
from pyftdi.spi import SpiPort

import logging 
log = logging.getLogger(__name__)


class CaravelPassThroughSpiPort(SpiPort):
    CaravelPassthroughByte = 0xC4 
    
    @classmethod 
    def newFromSpiPort(cls, port:SpiPort):
        return CaravelPassThroughSpiPort(port._controller, port.cs, 
                                  port._cs_hold,
                                  port.mode, port)
        
        
    
    def __init__(self, controller:'SpiController', cs:int, cs_hold:int=3, 
        spi_mode:int=0, orig_port = None):
        super().__init__(controller, cs, cs_hold, spi_mode)
        self.spi_port_raw = orig_port
    
    def exchange(self, out:Union[bytes, bytearray, Iterable[int]]=b'', 
                 readlen:int=0, start:bool=True, stop:bool=True, 
                 duplex:bool=False, droptail:int=0)->bytes:
        # augment the data going out with the 
        # pass-through byte
        bts = bytearray([self.CaravelPassthroughByte])
        bts.extend(out)
        # perform the exchange with through the pass-through
        v = self.spi_port_raw.exchange(bts, readlen, start=start, stop=stop, duplex=duplex, droptail=droptail)
        return v
        