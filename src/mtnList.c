#include "mtnList.h"

/* リスト初期化処理
 * 引数で受け取ったリストを初期化する
 * @param 
 */
void mtnList_Initialize(mtnListS *argList, size_t argSize){
  argList->count = 0;
  argList->top = NULL;
  argList->buttom = NULL;
  argList->contentsSize = argSize;
}

int mtnList_add(mtnListS *argList, void *argValue){
  mtnNode *but_node;
  mtnNode *new_node;

  new_node = (mtnNode*)malloc(sizeof(mtnNode));
  if(new_node == NULL){
    return 0; /* 異常終了 */
  }
  memset(new_node, 0x00, sizeof(mtnNode));
#ifdef DEBUG
  printf("   Add  malloc = %x \n", (unsigned int)new_node);
#endif
  new_node->p_Next = NULL;
  new_node->p_Content = argValue;

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
  return 1; /* 正常終了 */
}

int mtnList_insert(mtnListS *argList, unsigned int argIndex, void *argValue){
  mtnNode *newNode;
  mtnNode *currentNode;
  int iLoop = 0;
  int iRtn = 0;
  /* 引数の異常チェック */
  if( argList->count < argIndex  ){
    /* 引数が異常の場合、戻り値に異常値を設定して処理終了 */
    return 0;
  }

  /* 挿入箇所が終端ノードの場合、add処理と同等 */
  if( argIndex == argList->count ){
    /* add処理を呼ぶ */
    iRtn = mtnList_add(argList, argValue);
    return iRtn; 
  }

  /* 先頭ノード取得 */
  currentNode = argList->top;
  /* 挿入するノードのメモリを確保 */
  newNode = (mtnNode *)malloc(sizeof(mtnNode));
  /* 新規ノードメモリ領域を初期化 */
  memset(newNode, 0x00, sizeof(mtnNode));
  /* 新規ノードの値を設定 */
  newNode->p_Content = argValue;
  /* リストのノード数をインクリメント */
  argList->count++;

#ifdef DEBUG
  printf("   Ins  malloc = %x \n", (unsigned int)newNode);
#endif
  

  /* 挿入箇所が先頭ノードの場合 */
  if( argIndex == 0 ){
    /* 挿入ノードの次ノードに既存の先頭ノードを設定 */
    newNode->p_Next = currentNode;
    /* リストの先頭ノードポインタに挿入ノードを設定 */
    argList->top = newNode;
    return 1; /* 正常終了 */
  }
  /* 処理ノードを挿入箇所まで進める */
  while( iLoop < (argIndex  -1 )){
    /* ノードを進める */
    currentNode = currentNode->p_Next;
    iLoop++;
  }

  /* 挿入ノードの次ノードに既存ノードの次ノードを設定 */  
  newNode->p_Next = currentNode->p_Next;
  /* 処理ノードの次ノードに挿入ノードを設定 */
  currentNode->p_Next = newNode;
  return 1; /* 正常終了 */
  
}


void mtnList_freeNode(mtnNode *argNode){

#ifdef DEBUG
  printf("   free Node   = %x \n", (unsigned int)argNode);
#endif
  /* ノードの要素を解放 */
  free(argNode->p_Content);
  argNode->p_Content = NULL;
  /* ノードそのものを解放 */
  free(argNode);
  argNode = NULL;
}


void mtnList_Clear(mtnListS *argList){
  mtnNode *current_node; /* 処理対象ノード             */
  mtnNode *next_node;    /* 処理対象ノードの次のノード */

  /* 要素数が0の場合，一切処理をせずに終了 */
  if( argList->count == 0 ){
    return;
  }

  /* 先頭要素にポインタをあわせる */
  current_node = argList->top;

  /* 先頭の要素から順番にノードを解放していく */
  while( current_node != NULL ){
    /* ポインタがNULL参照になるまで繰り返し処理                              */
    /* Nextポインタを辿っていくと最後のノードのNextポインタがNULLとなるので  */
    /* ループは収束する                                                      */
    next_node = current_node->p_Next;
    mtnList_freeNode(current_node); /* ノードの解放処理 */
    current_node = next_node;
  }

  argList->count  = 0; /* 要素数を0に再初期化 */
  argList->top    = NULL;/* 先頭ノードへのポインタをNULL参照で再初期化 */
  argList->buttom = NULL;/* 末尾ノードへのポインタをNULL参照で再初期化 */
  return;  
}

void* mtnList_get(mtnListS *argList, unsigned int argIndex){
  mtnNode *current_node; /* 処理用ノード */
  int loop = 0; /* ループ処理用変数 */
  /* 第一引数異常チェック */
  if( argList == NULL){
    /* 引数がNULLポインタなら異常終了 */
    return NULL;
  }

  /* リストに要素が入っているかをチェック */
  if( argList->count == 0 ){
    /* 要素が空の場合は異常終了 */
    return NULL;
  }

  /* 第2引数の異常チェック */
  if ( argList->count <= argIndex ){
    /* リストの要素数より大きいインデックスを指定している場合 */
    /* 当該要素が存在しないので異常終了 */
    return NULL;
  }

  /* リストの先頭ノード取得 */
  current_node = argList->top;

  /* 第2引数番目のノードまでポインタを辿っていく */
  while( loop < argIndex ){
    /* 次のノードへ進む */
    current_node = (mtnNode *)current_node->p_Next;
    loop++;    
  }

  /* ノード内における要素ポインタを戻り値に指定して正常終了 */
  return (void *)current_node->p_Content;
}

int mtnList_delete(mtnListS *argList,unsigned int argIndex){
  mtnNode *current_Node;  /* 処理対象ノード */
  mtnNode *previous_Node; /* 処理対象ノードの一つ前 */
  int loop = 0; /* ループ処理用変数 */
  
    /* 第一引数異常チェック */
  if( argList == NULL){
    /* 引数がNULLポインタなら異常終了 */
    return 0;
  }

  /* リストに要素が入っているかをチェック */
  if( argList->count == 0 ){
    /* 要素が空の場合は異常終了 */
    return 0;
  }

  /* 第2引数の異常チェック */
  if ( argList->count <= argIndex ){
    /* 第2引数が負の値 or リストの要素数より大きいインデックスを指定している場合 */
    /* 当該要素が存在しないので異常終了 */
    return 0;
  }

  /* リストのノード数が1かつ削除対象ノードが先頭の場合，リストクリア処理 */
  if ( (argList->count == 1 ) && (argIndex == 0 ) ){
    mtnList_Clear(argList); /* 全要素削除(クリア) */
    return 1;               /* 要素数0を返す      */
  }

  /* 削除対象ノードが先頭ノードの場合の処理 */
  if ( argIndex == 0 ){
    current_Node = argList->top;         /* リストの先頭要素を取得 */
    argList->top = current_Node->p_Next; /* リストの先頭ポインタを2番目のノードに合わせる */
    mtnList_freeNode(current_Node);      /* 先頭ノードを解放 */
    argList->count--;                    /* リストの要素数をデクリメント */
    return 1; /* 正常終了 */
  }

  /* 第2引数で指定された番号まで処理対象ノードを進める */
  previous_Node = argList->top;          /* 処理対象前ノードを先頭ノードに合わせる */
  current_Node  = previous_Node->p_Next; /* 処理対象ノードを2番目のノードに合わせる */
  
  while ( loop < ( argIndex - 1 ) ){
    /* 処理対象ノードが第2引数で指定された番号のノードに一致するまで進める */
    previous_Node = current_Node;
    current_Node = current_Node->p_Next;
    loop++;
  }

  /* 削除対象ノードが終端ノードか否かで処理分岐 */
  if( argIndex == ( argList->count - 1 ) ){
    /* 削除対象ノードが終端ノードの場合の処理 */
    mtnList_freeNode(current_Node);  /* 終端ノードを解放 */
    argList->buttom = previous_Node; /* 処理対象前ノードを終端ノードに指定 */
    previous_Node->p_Next = NULL;    /* 処理対象前ノードのNextポインタにNULLを指定 */
    argList->count--;                /* リストの要素数をデクリメント */
  }else{
    previous_Node->p_Next = current_Node->p_Next;
    /* 処理対象前ノードのNextポインタを削除対象ノードの次ノードに合わせる */
    mtnList_freeNode(current_Node);  /* 終端ノードを解放 */
    argList->count--;                /* リストの要素数をデクリメント */
  }
  return 1; /* 正常終了 */
}

void mtnList_DBG_print(mtnListS* argList){
  int iloop = 0;
  int *pValue;
  printf("Contents Size   = %d \n", argList->contentsSize);
  printf("Contents Length = %d \n", argList->count);

  for(iloop = 0; iloop < argList->count ; iloop++){
    pValue = (int*)mtnList_get(argList, iloop);
    printf("[%03d]  %4d \n", iloop, *pValue);
  }
}

void* mtnList_convertArray(mtnListS* argList){
  void *rtnArray;   /* 戻り値用配列 */
  int iLoop;        /* 繰り返し処理用変数 */
  mtnNode* curNode; /* 処理中のノード */
  rtnArray = (void *)malloc((size_t) argList->contentsSize * argList->count);
  curNode = argList->top;
  for(iLoop = 0; iLoop < argList->count; iLoop++){
    memcpy(&rtnArray[ iLoop * argList->contentsSize ], curNode->p_Content, (size_t) argList->contentsSize);
    curNode = curNode->p_Next;
  }
  return rtnArray;    
}

