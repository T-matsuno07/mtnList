#include <stdio.h>
#include <string.h>
#include <mtnList.h>


struct _mtn_obj{
  unsigned int size; /* mallocしたサイズ */
  void* p_obj;       /* mallocしたメモリへのポインタ */
};

typedef struct _mtn_obj mtnObj;

struct _mtn_restore{
  unsigned int size;
  void* p_origin;
  void* p_restor;
};

typedef struct _mtn_restore mtnRes;


/*
 * @name   : メモリ確保
 * @param1 : mallocへ渡す引数
 * @return : mallocで確保したメモリへのポインタ
 */
void *mtnMalloc(size_t);

/*
 * @name   : メモリ解放
 * @param1 : freeで渡す引数
 * @return : void
 */
void mtnFree(void *);

/*
 * @name   : メモリダンプ処理
 * @param1 : 出力するファイル名称
 * @param2 : 
 * @return : 処理結果 1:正常終了 0:異常終了
 * @abst   : メモリリストの内容をファイルに書き出す
 */
void mtnMemOutputFile(char*);

/*
 * @name   : ダンプファイル復元処理
 * @param1 : 入力元ファイル名
 * @param2 : 
 * @return : 処理結果 1:正常終了 0:異常終了
 * @abst   : メモリダンプ処理で出力したファイルを読み込んでメモリ上に復元する処理
 */
void mtnMemInputFile(char*);

void mtnMemDGBPrint();

