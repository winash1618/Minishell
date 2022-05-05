#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define WR_VALUE _IOW('a', 'a', int32_t*)
#define RD_VALUE _IOR('a', 'b', int32_t*)

int main()
{
	int fileDescriptor;
	int32_t val, num;
	 printf("\nOpening the Driver\n");
	 fileDescriptor=open("/dev/random", O_RDWR);
	 if (fileDescriptor < 0)
	 {
		 printf("Unable to open the device file \n");
		 return (0);
	 }
	 printf("Enter the value that you want to send \n");
	 scanf("%d", &num);
	 printf("Writing the value to the driver \n");
	 ioctl(fileDescriptor, WR_VALUE, (int32_t *)&num);

	 printf("Reading the value from the driver \n");
	 ioctl(fileDescriptor, RD_VALUE, (int32_t *) &val);
	 printf("The value is %d \n", val);

	 printf("Closing the driver \n");
	 close(fileDescriptor);
	 return (0);
}