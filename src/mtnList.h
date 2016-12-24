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

void mtnList_Initialize(mtnListS*, size_t);
void mtnList_add(mtnListS*, void*);

#endif



















