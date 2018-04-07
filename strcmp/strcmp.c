/* 

    AUTHOR: Bruce Nelson
    DATE: 4/5/2017

    CONTRIBUTIONS: Chrisheyd 
    www.chrisheydrick.com

    PURPOSE:
    * The purpose of this program to demostrate a simple example of reading
    and writing data from a linux system to an Arduino. The program setups
    the serial stream at a selected baud rate (matched with the Arduino's)
    and initializes communication. This program sends a single character to
    initiate communication to the Arduino. The arduino will then send a string
    to the host system. Afterwards that string will be compared to an expected
    string. If they are equal, it will display a match otherwise it display no
    match.

    COMPARE:
    Arduino "println" function will add a carriage return and newline to the
    string being read.

    For standard strcmp, you will need to add the carriage return \r and
    new line \n as well as the string terminator \0 which together is \r\n\0
    that needs to be added to the end of the string

    Optionally you can replace the "strcmp" in the program with the "strncmp"
    example below. This is you know how many characters you need to match and
    match it to the read string's size excluding the carriage return, newline,
    and null terminator.
    
    if( strncmp(buf, "hello world!",12) == 0) // matches first 12 characters
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
void clientStart(char *msg);
void transmitReceive(char *msg, int size);
void clientMessage(char* msg, int size); // prints a char array

int main(int argc, char *argv[])
{
    int n;
    char buf[64] = "temp text";

    serialSetup();
   
    write(fd, "1", 1);     // write a single character to the Arduino
    n = read(fd, buf, 64); // read the message into buf and record the length
    buf[n] = 0;            // add null terminator to char array
    usleep(10000);
    clientMessage(buf, n);


    if( strcmp(buf, "hello world!\r\n\0") == 0) 
    {
        printf("MATCH!\n");
    }
    else
    {
        printf("NO MATCH!\n");
    }
    
    return 0;
}


void serialSetup()
{
    struct termios toptions;

    /* open serial port */
    fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
    printf("fd opened as %i\n\n", fd);
    
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

void transmitReceive(char *msg, int size)
{
    char buf[64];

    write(fd, msg, size);     // write a single character to the Arduino
    size = read(fd, buf, 64); // read the message into buf and record the length
    buf[size] = 0;            // add null terminator to char array
    usleep(10000);
    clientMessage(buf, size); // print the char array message
}

void clientMessage(char *msg, int size)
{
	int i;
	
    printf("CLIENT: ");
    for(i = 0; i < size; i++)
    {
        printf("%c", msg[i]);
    }
    //printf("\n");
}
