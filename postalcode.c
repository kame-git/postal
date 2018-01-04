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
	char *pfield[15];	/* 各フィールドの先頭アドレス */
	int ret = 0;

	pfield[0] = temp;
	int i;
	for (i = 0; i < FIELD_NUM-1; i++) {
		/* 「,」を探して\0に置き換え */
		char *p = strchr(pfield[i], ',');
		if (p == NULL) {
			fprintf(stderr, "Invalid number of fields.\n");
			return -1;
		}
		*p = '\0';

		if (i < FIELD_NUM-2) 
			pfield[i+1] = p+1;	/* 次のフィールドの先頭アドレス */

		switch (i) {
			case 2:		/* 郵便番号7桁 */
				ret = del_quote(&pfield[i]);
				data->postal_code = atoi(pfield[i]);
				break;
			case 3:		/* 都道府県名（カタカナ） */
				ret = del_quote(&pfield[i]);
				strncpy(data->kana.perf, pfield[i], strlen(pfield[i]));
				break;
			case 4:		/* 市区町村名（カタカナ） */
				ret = del_quote(&pfield[i]);
				strncpy(data->kana.city, pfield[i], strlen(pfield[i]));
				break;
			case 5:		/* 町域名（カタカナ） */
				ret = del_quote(&pfield[i]);
				strncpy(data->kana.town, pfield[i], strlen(pfield[i]));
				break;
			case 6:		/* 都道府県名（漢字） */
				ret = del_quote(&pfield[i]);
				strncpy(data->kanji.perf, pfield[i], strlen(pfield[i]));
				break;
			case 7:		/* 市区町村名（漢字） */
				ret = del_quote(&pfield[i]);
				strncpy(data->kanji.city, pfield[i], strlen(pfield[i]));
				break;
			case 8:		/* 町域名（漢字） */
				ret = del_quote(&pfield[i]);
				strncpy(data->kanji.town, pfield[i], strlen(pfield[i]));
				break;
			default:
				break;
		}	
	}

	return 0;
}

