#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int randomgen(){
  int file = open("/dev/random", O_RDONLY);
  int i;
  read(file, &i, sizeof(int));

  if(errno){
    printf("Error number: %d \t Error message: %s\n", errno, strerror(errno));
  }

  close(file);
  return i;
}

int main(){
  int list[10];
  printf("Generating random numbers:\n");

  for(int i = 0; i < 10;i++){
    list[i] = randomgen();
    printf("\trandom %d: %d\n", i, list[i]);
  }

  printf("Writing numbers to file...\n");
  int randfile = open("numbers.txt", O_RDWR|O_CREAT, 0644);
  int written = write(randfile, list, sizeof(list));
  close(randfile);
  if(errno){
    printf("Error number: %d \t Error message: %s\n", errno, strerror(errno));
  }

  printf("Reading numbers from file...\n");
  int check[10];
  int reading = open("numbers.txt", O_RDONLY);
  read(reading, &check, sizeof(check));
  close(reading);
  if(errno){
    printf("Error number: %d \t Error message: %s\n", errno, strerror(errno));
  }

  printf("Verification that written values were the same:\n");
  for(int i = 0; i<10; i++){
    printf("\trandom %d: %d\n", i, check[i]);
  }
  return 0;
}
