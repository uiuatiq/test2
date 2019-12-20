#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
  int fd;
  char *end;
  volatile void *cfg;
 // volatile uint8_t *gpio_out;
  long number;

  errno = 0;
  number = (argc == 2) ? strtol(argv[1],&end, 10) : -1;
  if(errno != 0 || end == argv[1] || number < 0 || number > 255)
  {
    fprintf(stderr, "Usage: gpio-output [0-255]\n");
    return EXIT_FAILURE;
  }
    printf("the end value is %d \n",argc);

    printf("the end value is %s \n",&argv[1]);
  if((fd = open("/dev/mem", O_RDWR)) < 0)
  {
    fprintf(stderr, "Cannot open /dev/mem.\n");
    return EXIT_FAILURE;
  }
  
  // printf("The number is %d \n",argc);
  cfg = mmap(NULL, sysconf(_SC_PAGESIZE), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0x40001000);

   printf("The first cfg is %s \n",&cfg);
   
  *(uint8_t *)(cfg + 2) = (uint8_t)number;
  // printf("The 2nd cfg is %s \n",&cfg);
 //  printf("last time number % d \n",argc);
   
  // sleep(10);
   return EXIT_SUCCESS;
}
