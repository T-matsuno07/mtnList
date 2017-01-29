#include <mtnMem.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
  int *foo;
  int iLoop;
  int *pp_3;
  int *pp_5;
  int *pp_7;

  printf("void* = %d \n", sizeof(void*));
  
  for(iLoop = 0; iLoop < 20; iLoop++){
    foo = mtnMalloc(sizeof(int));
    *foo = 256 + 3 + (iLoop * 10);
    switch(iLoop){
      case 3 :
        pp_3 = foo;
        break;
      case 5 :
        pp_5 = foo;
        break;
      case 7 :
        pp_7 = foo;
        break;
      default:
        break;
    }
  }

  mtnMemDGBPrint();
  printf("\n");

  mtnMemOutputFile("abc.dmp");

  printf("\n");
  printf("\n");
}

