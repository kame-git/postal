郵便番号データ（CSV）から特定の項目を取り出し、最大バイト数を取得する。

LinuxはUTF-8なので文字コードをShift JISから変更する。
# nkf -w -Lu --overwrite 08IBARAK.csv

例　ルビの市名の最大バイト数を取得する。
前後のダブルクォーテーション(2バイト）と改行文字を含む

$ cat 08IBARAK.CSV | cut -f 5 -d "," | while read line; do echo $line | wc -c ; done > result.txt
$ sort -r resltl.txt | head

改行文字を含まない場合は

$ cat 08IBARAK.CSV | cut -f 5 -d "," | while read line; do echo -n $line | wc -c ; done > result.txt
$ sort -r result.txt | head

初めの確認は
# head -2
# head -2 | cut -f 5 -d ","

wcの確認
# head -1 | cut -f 5 -d "," | wc -c
これだと行ごとではなく、トータルのバイト数を表示してしまうので、

1行ずつ処理するためにはシェルスクリプトの力を借りる。

while文の確認
ワンライナー
# while read line; do echo $line; done <<EOF

インタラクティブ
# while read line
> do
> echo $line
> done <<EOF
> polytech
> center
>EOF
polytechcenter#

結論
ルビの市名の最大バイト数（両脇のダブルクォーテーションを含み、改行は含まない）は、50バイトであることが分かる。

---------------------
重複した行を取り除く

# head -1000 08IBARAK.CSV | sort -t, -k5,5d -u
子のコマンドだと、市名の重複行の先頭は全て「イカニケイサイガナイバアイ」になるため、この行を削除したデータから重複行を削除する。

# grep -v イカニケイサイガナイバアイ 08IBARAK.CSV | sort -t, -k5,5d -u

----------
常総市と水海道を含む行を抽出する。
# grep 常総市 08IBARAK.CSV | grep 水海道

-----------
数字だけで構成され、先頭が0で始まるデータをエクセルで読み込むとうまく表示ができない。
このようなデータは先頭に'（シングルクォーテーション）を付けるとよい？

----------------
郵便番号のホームページによると、「※7 全角となっている町域名の文字数が38文字を超える場合、また、半角カタカナとなっている町域名のフリガナが76文字を越える場合には、複数レコードに分割しています。」とある。
このようなデータが存在するか確認するコマンドは？

郵便番号で同じデータが2行以上続く
データを探す？

