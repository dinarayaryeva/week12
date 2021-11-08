#include <stdio.h>
#include <linux/input.h>
#include <stdlib.h>

int main(void) {

  struct input_event s = {0,0,0,0};
 
  FILE* in_file = fopen("/dev/input/by-path/platform-i8042-serio-0-event-kbd", "rb"); 
         
  if (!in_file ) 
  {  
    exit(-1);
  } 

while(1){

  fread(&s, sizeof(s), 1, in_file); 

  if (s.type==EV_KEY) {

    if (s.value==0) 
        printf("RELEASED");
    else if (s.value==1) 
        printf("PRESSED");
    printf(" %#08X %i\n", s.code, s.code);
  }
}
fclose(in_file); 

  return 0;
}
