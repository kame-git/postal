#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "postalcode.h"

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: prog filename\n");
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "Can not open file\n");
		return 1;
	}

	char temp[256];

	/* 片方向リストとして実装する */
	postal_list *head_node, *last_node, *new_node;
	head_node = last_node = NULL;

	while (fgets(temp, sizeof(temp), fp)) {
		temp[strlen(temp)-1] = '\0';

		postal_data *data = (postal_data*)malloc(sizeof(postal_data));

		//新しいノードを作成
		new_node = (postal_list*)malloc(sizeof(postal_list));
		if (new_node == NULL) {
			fprintf(stderr, "can not allocate memory for node.\n");
			return 1;
		}

		new_node->data = data;
	
		if (last_node == NULL) {	 //最初のノード
			new_node->next = NULL;
			head_node = last_node = new_node;
		} else {					 //リストの末尾にデータを追加
			last_node->next = new_node;
			last_node = new_node;
		}

		int ret = split_jppost(temp, data); 
		if (ret < 0) {
			fprintf(stderr, "error: split_function\n");
			return 1;
		}
	}
	
	print_postal(head_node);

	return 0;
}

void print_postal(const postal_list *p)
{
	const postal_list *this_node = p;
	int i = 0;

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

int del_quote(char **p)
{
	if (**p != '"') {
		return -1;
	}
	(*p)++;			/* 先頭の「"」を飛ばす */
	int len = strlen(*p);
	char *t = (*p)+len-1;	/* 残りの文字列の長さを取得 */
	*t = '\0';		/* 末尾の「"」を削除 */

	return 0;
}

#define FIELD_NUM 15
int split_jppost(char *temp, postal_data *data)
{
	int i;
	int ret = 0;

	for (i = 0; i < FIELD_NUM-1; i++) {
		/* 「,」を探して\0に置き換え */
		char *p = strchr(temp, ',');
		if (p == NULL) {
			fprintf(stderr, "Invalid number of fields.\n");
			return -1;
		}
		*p = '\0';


		/* 文字列のコピーにstrncpyではなくstrcpyを用いている。 */
		/* 対象文字列がマルチバイト文字コードで必要バイを求め  */
		/* る標準ライブラリがないため。                        */
		switch (i) {
			case 2:		/* 郵便番号7桁 */
				ret = del_quote(&temp);
				data->postal_code = atoi(temp);
				break;
			case 3:		/* 都道府県名（カタカナ） */
				ret = del_quote(&temp);
				strcpy(data->kana.perf, temp);
				break;
			case 4:		/* 市区町村名（カタカナ） */
				ret = del_quote(&temp);
				strcpy(data->kana.city, temp);
				break;
			case 5:		/* 町域名（カタカナ） */
				ret = del_quote(&temp);
				strcpy(data->kana.town, temp); 
				break;
			case 6:		/* 都道府県名（漢字） */
				ret = del_quote(&temp);
				strcpy(data->kanji.perf, temp);
				break;
			case 7:		/* 市区町村名（漢字） */
				ret = del_quote(&temp);
				strcpy(data->kanji.city, temp);
				break;
			case 8:		/* 町域名（漢字） */
				ret = del_quote(&temp);
				strcpy(data->kanji.town, temp);
				break;
			default:
				break;
		}	
		if (i < FIELD_NUM-2) 
			temp = p+1;	
	}

	return ret;
}

