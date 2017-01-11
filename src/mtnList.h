#ifndef _MTN_LIST_
#define _MTN_LIST_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _mtn_node{
  void *p_Content;  /* ノードの要素(データ部) */
  struct _mtn_node *p_Next; /* 次ノードへのポインタ */
};

typedef struct _mtn_node mtnNode;

struct _mtn_list{
  int count;       /* 格納している要素数 */
  unsigned int contentsSize; /* ノードの要素サイズ */
  mtnNode *top;    /* 先頭ノードへのポインタ */
  mtnNode *buttom; /* 終端ノードへのポインタ */
};

typedef struct _mtn_list mtnListS;

/*
 * @name   : mtnList_Initialize (リスト初期化)
 * @param1 : 初期化対象リスト
 * @param2 : リストで管理するデータ型のサイズ
 * @return : void
 * @abst   : 第1引数で受け取ったリストの要素を初期化する
 */
void mtnList_Initialize(mtnListS*, size_t);

/*
 * @name   : mtnList_add (リストの末尾へ要素追加)
 * @param1 : 要素を追加するリスト
 * @param2 : リストの末尾に追加する要素へのポインタ
 * @return : 処理結果 true:正常 false:異常
 * @abst   : 第1引数で受け取ったリストの末尾に第2引数の要素を追加する
 */
void mtnList_add(mtnListS*, void*);

/*
 * @name   : mtnList_insert(リストへの要素挿入)
 * @param1 : ノードを挿入するリスト
 * @param2 : ノードを挿入する場所
 * @param3 : 挿入するノードの要素
 * @return : 要素を挿入した後のノード数
 * @abst   : 第2引数で指定した箇所に第3引数の要素を持つノードを挿入する
 */
int mtnList_insert(mtnListS*, int, void*);

/*
 * @name   : mtnList_freeNode (リスト解放)
 * @param1 : free対象となるノード
 * @return : void
 * @abst   : 引数で受け取ったノードをfreeする
 */
void mtnList_freeNode(mtnNode*);

/*
 * @name   : mtnList_Clear(リスト全要素解放処理)
 * @param1 : 全要素freeを実施するリスト
 * @param2 : 
 * @return : void
 * @abst   : リストの全てのノードに関するメモリをfreeする。
 *         : 注意事項として，リスト自体がfreeされるわけではないので，
 *         : リストそのモノのfreeはユーザが実施する必要がある。
 */
void mtnList_Clear(mtnListS*);

/*
 * @name   : mtnList_get(リスト要素取得)
 * @param1 : 要素を取得する対象のリスト
 * @param2 : 取得する要素の番号(先頭の要素は0)
 * @return : 第1引数で受け取ったリスト内における第2引数番目の要素へのポインタを返す。
 *           (ノードへのポインタではなく，要素そのものへのポインタを返す)
 * @abst   : 先頭ノードから順番にNextポインタを辿って行き，指定された順序のノードの要素を返す。
 * 注意事項:
 * 引数の指定方法などに不備があるときなどは全て戻り値がNULLとなる。
 * 本メソッドを用いるときは，戻り値のNULL判定を実施することを推奨する。
 */
void* mtnList_get(mtnListS*, int);

/*
 * @name   : mtnList_delete(ノード削除処理)
 * @param1 : 要素を削除する対象リスト
 * @param2 : 削除する要素の番号(先頭要素は0)
 * @return : 削除後のリストのノード数 処理異常が発生した場合は-1
 * @abst   : 第2引数で指定された番号のノードを削除する。
 */
int mtnList_delete(mtnListS*, int);

/*
 * @name   : (デバッグプリント処理)
 * @param1 : デバッグ出力対象リスト
 * @return : void
 * @abst   : 引数で受け取ったリストの内容を表示する
 */

void mtnList_DBG_print(mtnListS*);

#endif

