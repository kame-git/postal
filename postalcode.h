#ifndef _POSTTALCODE_H_
#define _POSTTALCODE_H_

#include <stdint.h>

#define KANA_PERF_LEN	256
#define KANA_CITY_LEN	256
#define KANA_TOWN_LEN	256
#define KANJI_PERF_LEN	256
#define KANJI_CITY_LEN	256
#define KANJI_TOWN_LEN	256

typedef struct {
	char perf[256];
	char city[256];
	char town[256];
} address;

typedef struct {
	uint32_t postal_code;
	address kana;
	address kanji;
} postal_data;

/* 郵便番号データを切り出し */
int split_jppost(char *p, postal_data *d);

/* データの先頭と末尾についている「"」を削除 */
int del_quote(char **p);

/* データを画面に表示 */
void print_postal(const postal_data *p);

#endif /* _POSTTALCODE_H_ */
