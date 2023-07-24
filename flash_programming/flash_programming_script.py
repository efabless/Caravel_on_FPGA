#from turtle import delay
import numpy as np
import serial
import time
import array


port = "/dev/ttyUSB1"
baud = 125000

ser = serial.Serial(port, baud, timeout=1)

if ser.isOpen():
  print (ser.name + ' is open...')


def FW_RD(A, D):
         
     temp= int('A5',16)
   
     Byte= temp.to_bytes(1, 'big')
     mask = (1 << 8) - 1
     Firs_byte = A & mask   
     mask = ((1 << 8) - 1) << 8
     Second_byte= (A & mask)>>8
     mask = ((1 << 8) - 1) << 16
     Third_byte= (A & mask)>>16
     mask = ((1 << 8) - 1) << 24
     Fourth_byte= (A & mask)>>24
     
     ser.write(Byte) 
     ser.write(Firs_byte.to_bytes(1, 'big'))  # first byte
     ser.write(Second_byte.to_bytes(1, 'big'))    #second byte
     ser.write(Third_byte.to_bytes(1, 'big'))
     ser.write(Fourth_byte.to_bytes(1, 'big'))

     out1 = ser.read()
     
     out2 = ser.read()
     
     out3 = ser.read()
     
     out4 = ser.read()
     firstByte = int.from_bytes(out4,'big') & 0xff000000
     secondByte = int.from_bytes(out3,'big') & 0x00ff0000
     thirdByte = int.from_bytes(out2,'big') & 0x0000ff00
     fourthByte = int.from_bytes(out1,'big') & 0x000000ff
     D= firstByte | secondByte | thirdByte | fourthByte

     return D
     
     


def FW_WR(A,D):
    temp= int('A3',16)
    Byte= temp.to_bytes(1, 'big')
    mask = (1 << 8) - 1
    Firs_byte_A = A & mask
    mask = ((1 << 8) - 1) << 8
    Second_byte_A= (A & mask)>>8
    mask = ((1 << 8) - 1) << 16
    Third_byte_A= (A & mask)>>16
    mask = ((1 << 8) - 1) << 24
    Fourth_byte_A= (A & mask)>>24
    mask = (1 << 8) - 1
    Firs_byte_D = D & mask
    mask = ((1 << 8) - 1) << 8
    Second_byte_D= (D & mask)>>8
    mask = ((1 << 8) - 1) << 16
    Third_byte_D= (D & mask)>>16
    mask = ((1 << 8) - 1) << 24
    Fourth_byte_D= (D & mask)>>24
    ser.write(Byte)
    #SENDING ADRESS
    ser.write(Firs_byte_A.to_bytes(1, 'big'))
    ser.write(Second_byte_A.to_bytes(1, 'big'))
    ser.write(Third_byte_A.to_bytes(1, 'big'))
    ser.write(Fourth_byte_A.to_bytes(1, 'big'))
    #SENDING DATA
    ser.write(Firs_byte_D.to_bytes(1, 'big'))
    ser.write(Second_byte_D.to_bytes(1, 'big'))
    ser.write(Third_byte_D.to_bytes(1, 'big'))
    ser.write(Fourth_byte_D.to_bytes(1, 'big'))
    


def FW_ENABLE():
    FW_WR(0x4c000000,0xA5A85501)

def SPI_OE(data):
 FW_WR(0x4c00000c,data)

def SPI_STATRT():
 FW_WR(0x4c000004,0)

def SPI_STOP():
 FW_WR(0x4c000004,1)

def SPI_BYTE_WR(data):
    for x in range(7, -1,-1):
        mask = ((1 << 1) - 1) <<x
        bit = (data & mask)>>x
        FW_WR(0x4c000010, bit)
        FW_WR(0x4c000008, 1)
        FW_WR(0x4c000008, 0)    

def SPI_BYTE_RD():
    word=0
    data=0
    temp={}
    for x in range(7, -1,-1):
        FW_WR(0x4c000008, 1)
        word=FW_RD(0x4c000014,word)
        temp[x]= ((word) & 1)#(word[0])0000000000000000000001
        FW_WR(0x4c000008, 0)
        
    num =0
    for x in range(7, -1,-1):
      if (temp[x]== 1):
         num+=2**(x)
    data = num
    return hex(data)

def FLASH_WDI():
    SPI_OE(0X1)
    SPI_STATRT()
    SPI_BYTE_WR(0X04)
    SPI_STOP()
def FLASH_WEN():
    SPI_OE(0X1)
    SPI_STATRT()
    SPI_BYTE_WR(0X06)
    SPI_STOP()
def FLASH_WEN_VOL():
    SPI_OE(0X1)
    SPI_STATRT()
    SPI_BYTE_WR(0X50)
    SPI_STOP()

def FLASH_CHIP_ERASE():
    SPI_OE(0X1)
    SPI_STATRT()
    SPI_BYTE_WR(0XC7)
    SPI_STOP()


def FLASH_BLOCK_ERASE(A):
    mask = ((1 << 8) - 1) << 16
    Third_byte_A= (A & mask)>>16
    mask = ((1 << 8) - 1) << 8
    Second_byte_A= (A & mask)>>8
    mask = (1 << 8) - 1
    Firs_byte_A = A & mask

    SPI_OE(0X1)
    SPI_STATRT()
    SPI_BYTE_WR(0XD8)

    SPI_BYTE_WR(Third_byte_A)
    SPI_BYTE_WR(Second_byte_A)
    SPI_BYTE_WR(Firs_byte_A)
    SPI_STOP()

def FLASH_PAGE_PROG(A, arr):
    print("Loading page")
    mask = ((1 << 8) - 1) << 16
    Third_byte_A= (A & mask)>>16
    mask = ((1 << 8) - 1) << 8
    Second_byte_A= (A & mask)>>8
    mask = (1 << 8) - 1
    Firs_byte_A = A & mask
    SPI_OE(0X1)
    SPI_STATRT()
    SPI_BYTE_WR(0X02)
    SPI_BYTE_WR(Third_byte_A)
    SPI_BYTE_WR(Second_byte_A)
    SPI_BYTE_WR(Firs_byte_A)

    for byte in arr:
        SPI_BYTE_WR(byte)
  
    SPI_STOP()



def FLASH_PAGE_RD(A):
    print("reading page")

    mask = ((1 << 8) - 1) << 16
    Third_byte_A= (A & mask)>>16
    
    mask = ((1 << 8) - 1) << 8
    Second_byte_A= (A & mask)>>8
    
    mask = (1 << 8) - 1
    Firs_byte_A = A & mask
    
    SPI_OE(0X1)
    SPI_STATRT()
    SPI_BYTE_WR(0X03)
    SPI_BYTE_WR(Third_byte_A)
    SPI_BYTE_WR(Second_byte_A)
    SPI_BYTE_WR(Firs_byte_A)
  
    f= open("out.txt", "a")
    x=0
    for i in range (128):
     f.write(SPI_BYTE_RD())
     x=x+1
     f.write(" ")
     if x==16:
         f.write("\n")
         x=0

    SPI_STOP()
    f.close()


def FLASH_WORD_PROG(A,D):
    mask = ((1 << 8) - 1) << 24
    Fourth_byte_D= (D & mask)>>24
    mask = ((1 << 8) - 1) << 16
    Third_byte_A= (A & mask)>>16
    third_byte_D=(D & mask)>>16
    mask = ((1 << 8) - 1) << 8
    Second_byte_A= (A & mask)>>8
    Second_byte_D= (D & mask)>>8
    mask = (1 << 8) - 1
    Firs_byte_A = A & mask
    Firs_byte_D = D & mask
    SPI_OE(0X1)
    SPI_STATRT()
    SPI_BYTE_WR(0X02)
    SPI_BYTE_WR(Third_byte_A)
    SPI_BYTE_WR(Second_byte_A)
    SPI_BYTE_WR(Firs_byte_A)

    SPI_BYTE_WR(Firs_byte_D)
    SPI_BYTE_WR(Second_byte_D)
    SPI_BYTE_WR(third_byte_D)
    SPI_BYTE_WR(Fourth_byte_D)
    SPI_STOP()

def FLASH_WORD_RD(A):
    mask = ((1 << 8) - 1) << 16
    Third_byte_A= (A & mask)>>16
    
    mask = ((1 << 8) - 1) << 8
    Second_byte_A= (A & mask)>>8
    
    mask = (1 << 8) - 1
    Firs_byte_A = A & mask
    
    SPI_OE(0X1)
    SPI_STATRT()
    SPI_BYTE_WR(0X0B)
    SPI_BYTE_WR(Third_byte_A)
    SPI_BYTE_WR(Second_byte_A)
    SPI_BYTE_WR(Firs_byte_A)
    SPI_BYTE_WR(0X00)
    
    print(SPI_BYTE_RD())
    print(SPI_BYTE_RD())
    print(SPI_BYTE_RD())
    print(SPI_BYTE_RD())
    SPI_STOP()

def PROG_WR():
   K=0
   n=0
   flag=1
   #f= open("test.txt", "a")
   arr= array.array('B',)
   with open('gpio_debug.hex','r') as f:
    lines=f.read().splitlines()
    lines= [x for x in lines if not x.startswith('@')]
    lines = [i.split(" ") for i in lines]
    for x in lines:
        for i in x[:-1]:
        #for i in x:
            #print(x)
            #print("\n")
            temp= int(i,16)
            if (n<128):
                arr.append(temp)
                n=n+1
            if(n==128):   
                n=0
                arr_str = ' '.join(str(x) for x in arr)
                with open('test.txt', 'a') as f:
                    f.write(arr_str)
                    f.write("\n")
                FLASH_WEN()
                FLASH_PAGE_PROG(K, arr)
                time.sleep(0.1)
                K = K + 128
                flag=flag+1
                for i in range(128):
                    arr.pop()
    if (len(arr) != 0):
                FLASH_WEN()
                FLASH_PAGE_PROG(K, arr)
                time.sleep(0.1)
                for i in range(len(arr)):
                            arr.pop()          
    
def PROG_RD():
    A = 0
    for i in range(10):
        FLASH_PAGE_RD(A)
        A = A + 128

      


##########################
# To exit the QPI mode
###########################
FW_ENABLE()
SPI_OE(0x1)
SPI_STATRT()
SPI_BYTE_WR(0xFF)
SPI_STOP()
############################
time.sleep(1)
###############################################
# FOR SST26VF080A flash 
# reading the Configuration & Staus Register
###############################################
#for Status Register 
SPI_OE(0X1)
SPI_STATRT()
SPI_BYTE_WR(0X05)
SR= SPI_BYTE_RD()
SPI_STOP()
print("Status Register",SR)
#for configuration Register 
SPI_OE(0X1)
SPI_STATRT()
SPI_BYTE_WR(0X35)
CR= SPI_BYTE_RD()
SPI_STOP()
print("configuration Register", CR)

####################
#write the SR & CR 
####################
SR = int(SR,16)
CR = int(CR,16)
FLASH_WEN()
time.sleep(1)
SPI_OE(0x1)
SPI_STATRT()
SPI_BYTE_WR(0x01)
SPI_BYTE_WR(0x00)  # write SR
SPI_BYTE_WR(0x3e)  #Write Configuration Register 
SPI_STOP()

##############################################
# reading the Configuration & Staus Register
###############################################
SPI_OE(0X1)
SPI_STATRT()
SPI_BYTE_WR(0X05)
SR= SPI_BYTE_RD()
SPI_STOP()
print("SR after writing",SR)
#for configuration Register 
SPI_OE(0X1)
SPI_STATRT()
SPI_BYTE_WR(0X35)
CR= SPI_BYTE_RD()
SPI_STOP()
print("CR after writing: ",CR)



############################
# To read the JEDEC ID
############################
#print('Reading JEDEC ID')
#SPI_STATRT()
#SPI_BYTE_WR(0x9F)
#D1 =SPI_BYTE_RD()
#D2= SPI_BYTE_RD()
#D3=SPI_BYTE_RD()
#print(D1)
#print(D2)
#print(D3)
#SPI_STOP()
#############################

###########################
#To write and read word
###########################
#FLASH_WEN()
#FLASH_PORT_UNLK()
#FLASH_WEN()
#time.sleep(10)
#FLASH_BLOCK_ERASE(0)
#time.sleep(10)
#FLASH_WEN()
#time.sleep(1)
#FLASH_WORD_PROG(0,0X0A0B0C0D)
#time.sleep(20)
#FLASH_WDI()
#FLASH_WORD_RD(0)
#####################


#####################################
#To program the whole mem file
#####################################
FLASH_WEN()
time.sleep(10)
FLASH_BLOCK_ERASE(0)
time.sleep(10)
#FLASH_CHIP_ERASE()
#time.sleep(50)
FLASH_WEN()
time.sleep(10)
start=time.time()
PROG_WR()
time.sleep(2)
end=time.time()
print(end-start)

PROG_RD()
############################################################################
