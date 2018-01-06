#ifndef _POSTTALCODE_H_
#define _POSTTALCODE_H_

#include "list_post.h"

#define KANA_PERF_LEN	256
#define KANA_CITY_LEN	256
#define KANA_TOWN_LEN	256
#define KANJI_PERF_LEN	256
#define KANJI_CITY_LEN	256
#define KANJI_TOWN_LEN	256

/* 郵便番号データを切り出し */
int split_jppost(char *p, postal_data *d);

/* データの先頭と末尾についている「"」を削除 */
int del_quote(char **p);

/* データを画面に表示 */
//void print_postal(const postal_data *p);
void print_postal(const postal_list *p);

#endif /* _POSTTALCODE_H_ */
