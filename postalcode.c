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

/*
	while (fgets(temp, sizeof(temp), fp)) {
		temp[strlen(temp)-1] = '\0';
		puts(temp);
	}
*/
	fgets(temp, sizeof(temp), fp);
	temp[strlen(temp)-1] = '\0';
	puts(temp);

/*
	p[1] = strchr(temp, ',');
	*(p[1]) = '\0';
	p[1]++;
*/


	postal_data data;
	int ret = split_jppost(temp, &data); 
	if (ret < 0) {
		fprintf(stderr, "error: split_function\n");
		return 1;
	}

	print_postal(&data);

	return 0;
}

void print_postal(const postal_data *p)
{
	printf("%d\n", p->postal_code);
	puts(p->kana.perf);
	puts(p->kana.city);
	puts(p->kana.town);
	puts(p->kanji.perf);
	puts(p->kanji.city);
	puts(p->kanji.town);
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


		switch (i) {
			case 2:		/* 郵便番号7桁 */
				ret = del_quote(&temp);
				data->postal_code = atoi(temp);
				break;
			case 3:		/* 都道府県名（カタカナ） */
				ret = del_quote(&temp);
				strncpy(data->kana.perf, temp,  strlen(temp));
				break;
			case 4:		/* 市区町村名（カタカナ） */
				ret = del_quote(&temp);
				strncpy(data->kana.city, temp, strlen(temp));
				break;
			case 5:		/* 町域名（カタカナ） */
				ret = del_quote(&temp);
				strncpy(data->kana.town, temp, strlen(temp));
				break;
			case 6:		/* 都道府県名（漢字） */
				ret = del_quote(&temp);
				strncpy(data->kanji.perf, temp, strlen(temp));
				break;
			case 7:		/* 市区町村名（漢字） */
				ret = del_quote(&temp);
				strncpy(data->kanji.city, temp, strlen(temp));
				break;
			case 8:		/* 町域名（漢字） */
				ret = del_quote(&temp);
				strncpy(data->kanji.town, temp, strlen(temp));
				break;
			default:
				break;
		}	
		if (i < FIELD_NUM-2) 
			temp = p+1;	
	}

	return ret;
}

