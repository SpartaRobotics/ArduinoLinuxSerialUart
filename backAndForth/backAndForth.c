/* 

    AUTHOR: Bruce Nelson
    DATE: 4/5/2017

    CONTRIBUTIONS: Chrisheyd 
    www.chrisheydrick.com

    PURPOSE:
    * The purpose of this program to demostrate a simple example of reading
    and writing data from a linux system to an Arduino. The program setups
    the serial stream at a selected baud rate (matched with the Arduino's)
    and initializes communication. The program sends a single character string
    "2" to the Arduino. The Arduino will convert it to an integer add 4 to the
    value read, which should add up to 6. This value will then write from the
    Arduino to the host.

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>

int fd;

void serialSetup(); // Sets up serial communication to the Arduino
void clientMessage(char* message, int size); // prints a char array

int main(int argc, char *argv[])
{
    int n;
    char buf[64] = "temp text";

    serialSetup();

	while(strcmp("START",buf) != 0)
	{
		n = read(fd, buf, 64);
		buf[n] = 0;
	}
	write(fd, "7", 1);
	//clientMessage(buf, n);
	//usleep(1000000);

    write(fd, "1", 1);     // write a single character to the Arduino
    n = read(fd, buf, 64); // read the message into buf and record the length
    buf[n] = 0;            // add null terminator to char array
    clientMessage(buf, n); // print the char array message

    write(fd, "2", 1);     // write a single character to the Arduino
    n = read(fd, buf, 64); // read the message into buf and record the length
    buf[n] = 0;            // add null terminator to char array
    clientMessage(buf, n); // print the char array message

	write(fd, "3", 1);     // write a single character to the Arduino
    n = read(fd, buf, 64); // read the message into buf and record the length
    buf[n] = 0;            // add null terminator to char array
    clientMessage(buf, n); // print the char array message

    return 0;
}

void serialSetup()
{
    struct termios toptions;

    /* open serial port */
    fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
    printf("fd opened as %i\n", fd);
    
    /* wait for the Arduino to reboot */
    usleep(3500000);
    
    /* get current serial port settings */
    tcgetattr(fd, &toptions);
    /* set 115200 baud both ways */
    cfsetispeed(&toptions, B115200);
    cfsetospeed(&toptions, B115200);
    /* 8 bits, no parity, no stop bits */
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    /* Canonical mode */
    toptions.c_lflag |= ICANON;
    /* commit the serial port settings */
    tcsetattr(fd, TCSANOW, &toptions);
}

void clientMessage(char* message, int size)
{
	int i;
	
    printf("CLIENT: ");
    for(i = 0; i < size; i++)
    {
        printf("%c", message[i]);
    }
}
