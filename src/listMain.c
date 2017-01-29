#include <stdio.h>
#include "mtnList.h"

/* mtnListデバッグ用プログラム */
int main(void){
  int *iTemp;
  unsigned int iLoop;
  mtnListS list;
  
  /* リストを初期化 */
  mtnList_Initialize(&list, sizeof(int));

  for(iLoop = 0; iLoop < 10; iLoop++){
    iTemp = (int *)malloc(sizeof(int));
    *iTemp = (iLoop * 10) + 2;
    mtnList_add(&list, iTemp);
  }
  //mtnList_DBG_print(&list);
  iTemp = (int *)malloc(sizeof(int));
  *iTemp = 77;
  mtnList_insert(&list, 2, iTemp);
  //mtnList_DBG_print(&list);

  mtnList_delete(&list, 8);
  mtnList_DBG_print(&list);

  iTemp = mtnList_convertArray(&list);

  for(iLoop = 0; iLoop < list.count; iLoop++){
    printf("Array[%d] = %d \n", iLoop, iTemp[iLoop]);
  }

  
  free(iTemp);
  mtnList_Clear(&list);
  mtnList_DBG_print(&list);
  
  return 0;
}

