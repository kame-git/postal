#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "list_post.h"

/* 郵便番号データを保存 */
inline bool set_post(const postal_data *d)
{
    return insert_post(d);
}

/* リスト制御 */

static postal_list *head_node = NULL;
static postal_list *last_node = NULL;
static postal_list *new_node;

/* ノードをリストに追加 */
bool insert_post(const postal_data *p)
{
	postal_data *data = (postal_data*)malloc(sizeof(postal_data));
	if (data == NULL) {
		fprintf(stderr, "can not allocate memory for node.\n");
		return false;
	}
    /* データをコピー(浅い) */
    *data = *p;

	//新しいノードを作成
	new_node = (postal_list*)malloc(sizeof(postal_list));
	if (new_node == NULL) {
		fprintf(stderr, "can not allocate memory for node.\n");
		return false;
	}

	new_node->data = data;

	if (last_node == NULL) {	 //最初のノード
		new_node->next = NULL;
		head_node = last_node = new_node;
	} else {					 //リストの末尾にデータを追加
		last_node->next = new_node;
		last_node = new_node;
	}

    return true;
}

/* 郵便番号から該当するノードを検索 */
postal_data *search_post(const uint32_t post)
{
    postal_list *p = head_node;
    while (p != NULL) {
        if (p->data->postal_code == post) {
            return p->data;
        } else {
            p = p->next;
        }
    }
    return NULL;
}

/* ノードを全て削除 */
void clear_post()
{
    postal_list *p = head_node;
    postal_list *t;

    while (p != NULL) {
        free(p->data);
        t = p->next;
        free(p);
        p = t;
    }
}

/* ノードの情報を全て表示 */
void print_post_all()
{
	const postal_list *this_node = head_node;

	while (this_node != NULL) {
		printf("%d\n", this_node->data->postal_code);
		puts(this_node->data->kana.perf);
		puts(this_node->data->kana.city);
		puts(this_node->data->kana.town);
		puts(this_node->data->kanji.perf);
		puts(this_node->data->kanji.city);
		puts(this_node->data->kanji.town);
		puts("-----------------------------------");
		this_node = this_node->next;

	}
}

