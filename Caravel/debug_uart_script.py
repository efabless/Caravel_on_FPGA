#from turtle import delay
import numpy as np
import serial
import time
import array


port = "/dev/ttyUSB1"
#baud = 459770
baud = 138236

ser = serial.Serial(port, baud, timeout=1)

if ser.isOpen():
  print (ser.name + ' is open...')



def wb_write(addr, word):

  temp= int('01',16)
  cmd= temp.to_bytes(1, 'big')
  temp= int('01',16)
  size= temp.to_bytes(1, 'big')

  mask = (1 << 8) - 1
  First_byte_addr = addr & mask
  mask = ((1 << 8) - 1) << 8
  Second_byte_addr= (addr & mask)>>8
  mask = ((1 << 8) - 1) << 16
  Third_byte_addr= (addr & mask)>>16
  mask = ((1 << 8) - 1) << 24
  Fourth_byte_addr= (addr & mask)>>24

  mask = (1 << 8) - 1
  First_byte_word = word & mask
  mask = ((1 << 8) - 1) << 8
  Second_byte_word= (word & mask)>>8
  mask = ((1 << 8) - 1) << 16
  Third_byte_word= (word & mask)>>16
  mask = ((1 << 8) - 1) << 24
  Fourth_byte_word= (word & mask)>>24

  #SENDING_CMD
  ser.write(cmd)
  #SENDING_SIZE
  ser.write(size)
  #SENDING ADRESS
  ser.write(Fourth_byte_addr.to_bytes(1, 'big'))
  ser.write(Third_byte_addr.to_bytes(1, 'big'))
  ser.write(Second_byte_addr.to_bytes(1, 'big'))
  ser.write(First_byte_addr.to_bytes(1, 'big'))
  #SENDING DATA
  ser.write(Fourth_byte_word.to_bytes(1, 'big'))
  ser.write(Third_byte_word.to_bytes(1, 'big'))
  ser.write(Second_byte_word.to_bytes(1, 'big'))
  ser.write(First_byte_word.to_bytes(1, 'big'))



def wb_read(addr, word):
         
  temp= int('02',16)
  cmd= temp.to_bytes(1, 'big')
  temp= int('01',16)
  size= temp.to_bytes(1, 'big')

  mask = (1 << 8) - 1
  First_byte_addr = addr & mask
  mask = ((1 << 8) - 1) << 8
  Second_byte_addr= (addr & mask)>>8
  mask = ((1 << 8) - 1) << 16
  Third_byte_addr= (addr & mask)>>16
  mask = ((1 << 8) - 1) << 24
  Fourth_byte_addr= (addr & mask)>>24
     
  #SENDING_CMD
  ser.write(cmd)
  #SENDING_SIZE
  ser.write(size)
  #SENDING ADRESS
  ser.write(Fourth_byte_addr.to_bytes(1, 'big'))
  ser.write(Third_byte_addr.to_bytes(1, 'big'))
  ser.write(Second_byte_addr.to_bytes(1, 'big'))
  ser.write(First_byte_addr.to_bytes(1, 'big'))

  out1 = ser.read()
     
  out2 = ser.read()
     
  out3 = ser.read()
     
  out4 = ser.read()

  firstByte = int.from_bytes(out4,'big') & 0xff000000
  secondByte = int.from_bytes(out3,'big') & 0x00ff0000
  thirdByte = int.from_bytes(out2,'big') & 0x0000ff00
  fourthByte = int.from_bytes(out1,'big') & 0x000000ff
  word = firstByte | secondByte | thirdByte | fourthByte

  return word

word = 0

#wb_write (0x00400024, 0x775555ab)
wb_write (0x00000110, 0x775555ab)

#word = wb_read (0x00400024, word)
word = wb_read (0x00000110, word)

print ("The word read is", word)
