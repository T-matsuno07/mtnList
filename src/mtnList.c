#include "mtnList.h"

void mtnList_Initialize(mtnListS *argList, size_t argSize){
  argList->count = 0;
  argList->top = NULL;
  argList->buttom = NULL;
  argList->contentsSize = argSize;
}

void mtnList_add(mtnListS *argList, void *argValue){
  mtnNode *but_node;
  mtnNode *new_node;

  new_node = (mtnNode*)malloc(sizeof(mtnNode));
  memset(new_node, 0x00, sizeof(mtnNode));

  new_node->p_Next = NULL;

  /* リストに既存のノードが存在するか否かで処理分岐 */
  if(argList->top == NULL){
    /* 既存ノードがない(空リスト)の場合 */
    /* 先頭ノードと終端ノードに新しいノードを設定 */
    argList->top = new_node;
    argList->buttom = new_node;
    argList->count = 1;
  }else{
    /* 既存ノードがある場合 */
    /* 終端ノードの次ノードに新しいノードを設定 */
    but_node = argList->buttom;
    but_node->p_Next = new_node;
    argList->buttom = new_node;
    /* リストの要素数をインクリメント */
    argList->count++;
  }
}



















