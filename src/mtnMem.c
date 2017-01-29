#include <mtnList.h>
#include <mtnMem.h>

/* mallocメモリ管理用リスト */
static mtnListS _list_memory;
static int _init_Flag = 0;
/* 復元メモリ管理用リスト */
static mtnListS _rest_memory;
static int _rest_Flag = 0;


void *mtnMalloc(size_t argSize){
  void *rtnPointa;  /* malloc取得アドレス */
  mtnObj *newObj;   /* 管理リストの1ノード */

  /* メモリを確保 */
  rtnPointa = malloc(argSize);

  /* メモリ確保に成功したか? */
  if (rtnPointa == NULL){
    /* メモリ取得異常時，処理終了 */
    return NULL;
  }
  /* mtnMalloが呼ばれたのが初めてか? */
  if ( _init_Flag == 0 ){
    /* 初めての場合，管理リストを初期化 */
    mtnList_Initialize(&_list_memory, sizeof(mtnObj));
    /* 初期化済みフラグを立てる */
    _init_Flag = 1;
  }

  /* 管理用リストにノードを追加 */
  newObj = (mtnObj*)malloc(sizeof(mtnObj));
  newObj->size = argSize;
  newObj->p_obj = rtnPointa;
  mtnList_add(&_list_memory, newObj);

  /* mallocで取得したアドレスを返す */
  return rtnPointa;
}


void mtnFree(void *argAddr){
  unsigned int iLoop = 0;  /* 繰り返し処理用変数 */
  mtnObj *curobj;          /* 管理用ノード */

  /* 解放先アドレスを管理しているノードをリストから探すループ */
  for(iLoop = 0; iLoop < _list_memory.count; iLoop++){
    /* iLoop番目のノードを取得 */
    curobj = mtnList_get(&_list_memory, (int)iLoop);
    /* 取得したノードで管理しているアドレスが引数と一致するか? */
    if( memcmp(argAddr, curobj->p_obj, sizeof(void*)) == 0 ){
      /* 解放するアドレスのノードを削除する */
      mtnList_delete(&_list_memory, (int)iLoop);
    }
  }
  /* 通常のfreeを実行 */
  free(argAddr);
}


void mtnMemOutputFile(char* argPath){
  unsigned int iLoop; /* 繰り返処理用変数 */
  unsigned int iTotalSize; /* 書き出し用バッファサイズ */
  unsigned int iOffset;
  char *p_Dump;  /* 書き出し用バッファポインタ */
  mtnObj *curObj;
  FILE *fp;

  fp = fopen(argPath, "wb");

  if( fp == NULL){
    return;
  } 
  /* ファイルに書き出す際のバッファサイズを計算する */
  iTotalSize = sizeof(unsigned int);
  for(iLoop = 0; iLoop < _list_memory.count ; iLoop++){
    curObj = mtnList_get(&_list_memory, iLoop);
    iTotalSize += sizeof(unsigned int); /* mallocした際の引数を保管した変数のサイズ */
    iTotalSize += sizeof(void*);  /* mallocしたアドレスを確保するサイズ*/
    iTotalSize += (curObj->size);   /* mallocで確保したサイズ */
  }

  /* 書き出し用バッファのメモリ領域を確保 */
  p_Dump = (char *)malloc(iTotalSize);
  /* 書き出し用バッファのメモリ領域を初期化 */
  memset(p_Dump, 0x00, iTotalSize);
  iOffset = 0;

  memcpy(&p_Dump[iOffset], &(_list_memory.count) , sizeof(unsigned int));
  iOffset += sizeof(unsigned int);
  
  for(iLoop = 0; iLoop < _list_memory.count ; iLoop++){
    curObj = mtnList_get(&_list_memory, iLoop);
    memcpy(&p_Dump[iOffset], &(curObj->size) , sizeof(unsigned int));
    iOffset += sizeof(unsigned int);
  
    memcpy(&p_Dump[iOffset], &(curObj->p_obj) , sizeof(void*));
    iOffset += sizeof(void*);

    memcpy(&p_Dump[iOffset], curObj->p_obj , curObj->size);
    iOffset += curObj->size;
  }
#if 0
  for(iLoop=0; iLoop < iTotalSize; iLoop++){
    printf("%02X ",p_Dump[iLoop] & 0x000000FF);    
    if( ((iLoop+1) % 16) == 0 ){
      printf("\n");
    }
  }
#endif

  /* バイナリモードでファイルに書き込み */
  fwrite( p_Dump, 1, iTotalSize, fp );
  
  fclose(fp); /* ファイルをクローズ */
  free(p_Dump); /* 書き出し用バッファ領域解放  */
}

void mtnMemInputFile(char* argPath){
  unsigned int iLoop; /* 繰り返し処理用変数 */
  unsigned int iReadCount; /* 読み込むサイズ */
  char p_Restore; /* 読み込み用バッファ */
  mtnRes *resObj; /* 読込結果 格納オブジェクト */
  FILE *fp;       /* 読み込み用ファイルポインタ */

  fp = fopen(argPath, "rb");

  if ( fp == NULL ){
    return;
  }
  
  if ( _rest_Flag == 0 ){
    mtnList_Initialize(&_rest_memory, sizeof(mtnRes));
    _rest_Flag = 1;
  }else{
    mtnList_Clear(&_rest_memory);
  }

  fread( &iReadCount, sizeof(unsigned int), 1, fp );
  printf("iread = %d \n", iReadCount);

  for(iLoop = 0; iLoop < iReadCount; iLoop++){
    resObj = (mtnRes*)malloc(sizeof(resObj));
    fread( &(resObj->size), sizeof(unsigned int), 1, fp );
    fread(&(resObj->p_origin), sizeof(void*), 1, fp);
    resObj->p_restor = (void*)malloc(resObj->size);
    fread(resObj->p_restor, resObj->size, 1, fp);
    mtnList_add(&_rest_memory, resObj);
  }

  printf("Count = %d \n", _rest_memory.count);
  fclose(fp);
  return;
  

  
}

void mtnMemDGBPrint(){
  unsigned int iLoop; /* 繰り返処理用変数 */
  int *p_value; /* 出力対象ポインタ */
  mtnObj *curObj;
  for(iLoop = 0; iLoop < _list_memory.count; iLoop++){
    curObj = mtnList_get(&_list_memory, iLoop);
    p_value = curObj->p_obj;
    printf("Indx[%4d] Size[%5d] Addr[0x%8x] ", (int)iLoop, (int)curObj->size,  (unsigned int)(curObj->p_obj) & (0xFFFFFFFF));
    printf("value = %3d (0x%8x) " , *p_value, (*p_value) & (0xFFFFFFFF));
    printf("\n");
  }
}

void mtnMemReadPrint(){
  unsigned int iLoop; /* 繰り返処理用変数 */
  int *p_value; /* 出力対象ポインタ */
  mtnRes *curObj;
  for(iLoop = 0; iLoop < _rest_memory.count; iLoop++){
    curObj = mtnList_get(&_rest_memory, iLoop);
    p_value = curObj->p_restor;
    printf("Indx[%4d] Size[%5d] Addr[0x%8x] -> Origin[0x%8x] ", (int)iLoop, (int)curObj->size,  (unsigned int)(curObj->p_restor) & (0xFFFFFFFF), (unsigned int)(curObj->p_origin) & (0xFFFFFFFF));
    printf("value = %3d (0x%8x) " , *p_value, (*p_value) & (0xFFFFFFFF));
    printf("\n");
  }
}

