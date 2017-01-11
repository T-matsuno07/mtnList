#include <stdio.h>
#include "mtnList.h"

/* mtnListデバッグ用プログラム */
int main(void){
  int *iTemp;
  int iLoop;
  mtnListS list;
  /* リストを初期化 */
  mtnList_Initialize(&list, sizeof(int));

  for(iLoop = 0; iLoop < 10; iLoop++){
    iTemp = (int *)malloc(sizeof(int));
    *iTemp = iLoop * 10;
    mtnList_add(&list, iTemp);
  }
  //mtnList_DBG_print(&list);
  iTemp = (int *)malloc(sizeof(int));
  *iTemp = 77;
  mtnList_insert(&list, 2, iTemp);
  //mtnList_DBG_print(&list);

  mtnList_delete(&list, 8);
  mtnList_DBG_print(&list);

  mtnList_Clear(&list);
  mtnList_DBG_print(&list);
  
  return 0;
}

