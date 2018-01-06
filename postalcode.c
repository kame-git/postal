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

    int err_count = 0;
    int count = 0;
	while (fgets(temp, sizeof(temp), fp)) {
		temp[strlen(temp)-1] = '\0';

		int ret = split_jppost(temp, &data); 
		if (ret < 0) {
            err_count++;
            continue;
		} else {
            count++;
        }
        
        if (!set_post(&data)) {
            fprintf(stderr, "can not insert postal_data.\n");
            return 1;
        }
	}

    printf("正常に読み込んだデータ数 %d/%d\n", count - err_count, count);
	
    printf("検索郵便番号: ");
    uint32_t postal_code;
    scanf("%d", &postal_code);

    postal_data *find_post = search_post(postal_code);
    if (find_post != NULL) {
        print_post(find_post);
    }

    /* 動的メモリはOSに回収してもらう */
    /* clear_post(); */

	return 0;
}

void print_post(const postal_data *p)
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

/** @brief カンマで区切られたデータを切り分
 *  @notice マルチバイト文字列に対してstrtokを使用しているため
 *  特定の文字列で正常に動作しないかもしれない。
 */
#define FIELD_NUM 15
int split_jppost(char *temp, postal_data *data)
{
    char *p;
    int i = 0;
    int ret = 0;

    p = strtok(temp, ",");
    while (p) {
        
		/* 文字列のコピーにstrncpyではなくstrcpyを用いている。 */
		/* 対象文字列がマルチバイト文字コードで必要バイを求め  */
		/* る標準ライブラリがないため。                        */
		switch (i) {
			case 2:		/* 郵便番号7桁 */
				ret = del_quote(&p);
                if (ret < 0)
                    return ret;
				data->postal_code = atoi(p);
				break;
			case 3:		/* 都道府県名（カタカナ） */
				ret = del_quote(&p);
                if (ret < 0)
                    return ret;
				strcpy(data->kana.perf, p);
				break;
			case 4:		/* 市区町村名（カタカナ） */
				ret = del_quote(&p);
                if (ret < 0)
                    return ret;
				strcpy(data->kana.city, p);
				break;
			case 5:		/* 町域名（カタカナ） */
				ret = del_quote(&p);
                if (ret < 0)
                    return ret;
				strcpy(data->kana.town, p); 
				break;
			case 6:		/* 都道府県名（漢字） */
				ret = del_quote(&p);
                if (ret < 0)
                    return ret;
				strcpy(data->kanji.perf, p);
				break;
			case 7:		/* 市区町村名（漢字） */
				ret = del_quote(&p);
                if (ret < 0)
                    return ret;
				strcpy(data->kanji.city, p);
				break;
			case 8:		/* 町域名（漢字） */
				ret = del_quote(&p);
                if (ret < 0)
                    return ret;
				strcpy(data->kanji.town, p);
				break;
			default:
				break;
        }
        p = strtok(NULL, ",");
        i++;
    }

    /* 切り出したフィールド数が15でなければエラー */
    if (i != 15) 
        return -1;
    else
        return 0;
}

