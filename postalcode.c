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
    postal_data data = {0};

	while (fgets(temp, sizeof(temp), fp)) {
		temp[strlen(temp)-1] = '\0';

		int ret = split_jppost(temp, &data); 
		if (ret < 0) {
			fprintf(stderr, "error: split_function\n");
			return 1;
		}
        
        if (!set_post(&data)) {
            fprintf(stderr, "can not insert postal_data.\n");
            return 1;
        }
	}
	
    print_post_all();

	return 0;
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

