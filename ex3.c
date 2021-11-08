#include <stdio.h>
#include <linux/input.h>
#include <stdlib.h>

struct shortcut{
  int size;
  int* codes; 
  char message[128];
};

void find_shortcut(struct shortcut* ar, int size, int* last_shortcut, int max_i){
  for (int k=0; k < size; k++) //check each shortcut
  { 
    int m;
    for (m=0; m<ar[k].size; m++){
      if (ar[k].codes[m]!=last_shortcut[m]) break;
    }
    if (m==ar[k].size) {
      printf("%s\n", ar[k].message);
    }
  }
}

int main(void) {

  int last_shortcut[6] = {0, 0, 0, 0, 0, 0};

  int b1[2] = {25, 18};
  int b2[3] = {46, 30, 25};
  int b3[2] = {21, 32};

  struct shortcut a1 = {2, b1, "I passed the Exam!"};
  struct shortcut a2 = {3, b2, "Get some cappuccino"};
  struct shortcut a3 = {2, b3, "Give me A grade, please :)"};


  struct shortcut ar[3] = {a1, a2, a3};

  struct input_event s = {0,0,0,0};
 
  FILE* in_file = fopen("/dev/input/by-path/platform-i8042-serio-0-event-kbd", "rb"); 
         
  if (!in_file )
  {  
    exit(-1);
  } 

int index = 0;

while(1){

  fread(&s, sizeof(s), 1, in_file);

  if (s.type==EV_KEY) {

    if (s.value==0) {

      find_shortcut(ar, 3, last_shortcut, 6);
      index=0;
    }
    else if (s.value==1) {

      last_shortcut[index] = s.code;
      index++;
    }
  }
}
fclose(in_file); 

  return 0;
}