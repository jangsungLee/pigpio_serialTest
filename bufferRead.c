#include <pigpio.h>

#include <stdio.h> //for printf
#include <string.h> //for errno
#include <errno.h> //error output


// Find Serial device on Raspberry with ~ls /dev/tty*
// ARDUINO_UNO "/dev/ttyACM0"
// FTDI_PROGRAMMER "/dev/ttyUSB0"
// HARDWARE_UART "/dev/ttyAMA0"
char device[]= "/dev/ttyACM0";
// filedescriptor
int fd;
unsigned long baud = 9600;
unsigned long time1=0;

int main(void)
{
     int recvLen = 0;
     char buf[15], prevChar, newChar;
  printf("%s \n", "Raspberry Startup!");

  //setup PIGPIO
  if (gpioInitialise ()  < 0){
    fprintf (stdout, "Unable to gpioInitialise\n") ;
    return 1;
  }

  //get filedescriptor
  if ((fd = serOpen (device, baud, 0)) < 0){
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1;
  }

  while(1) // sync(fake infinite loop)
  {
     // Serial Interrupt.

     // read signal
     serWriteByte(fd, 's');
     if(serDataAvailable (fd)){
              newChar = serReadByte (fd);
              if(newChar == 's')
              {
                       buf[recvLen++] = newChar;
                       break;
              }
     }
  }


  while(1)
  {
     // Serial Interrupt.
     serWriteByte(fd, 's');

     // read signal
     if(serDataAvailable (fd)){
          buf[recvLen++] = serReadByte(fd);
          if(recvLen == 15)
          {
               recvLen = 0;
               for(int i = 0;i<15;i++)
                    printf("%d ", buf[i]);printf("\n");
          }
     }
     
  }

  return 0;
}
