#ifndef _LIST_POST_H_
#define _LIST_POST_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	char perf[256];
	char city[256];
	char town[256];
} address;

typedef struct postal_data {
	uint32_t postal_code;
	address kana;
	address kanji;
} postal_data;

typedef struct postal_list {
	postal_data *data;
	struct postal_list *next;
} postal_list;

bool set_post(const postal_data *d);

/* リスト制御 */
/* 郵便番号データを保存 */
inline bool set_post(const postal_data *d);
/* ノードをリストに追加 */
bool insert_post(const postal_data *p);
/* 郵便番号から該当するノードを検索 */
postal_data *search_post(const int post);
/* ノードを全て削除 */
void clear_post();

/* ノードの情報を全て表示 */
void print_post_all();

#endif /* _LIST_POST_H_ */

