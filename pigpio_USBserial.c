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
	int startPoint = 0, isFirstPoint = 0, NewLine = 1;
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


  while(1)
  {
     // read signal
     if(serDataAvailable (fd)){
       char newChar = serReadByte (fd);

       if(isFirstPoint == 0)
       {
              if(newChar == 's')
              {
                     isFirstPoint = 1;
                     startPoint = 1;
                     gpioDelay(5 * 1000 * 1000);
              }
       }

       if(startPoint == 1)
       {
              printf("%d ", newChar);
              if(NewLine++ > 14)
              {
                 printf("\n");
                 NewLine = 1;
              }
              fflush(stdout);
       }
     }
  }

  return 0;
}
