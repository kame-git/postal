�X�֔ԍ��f�[�^�iCSV�j�������̍��ڂ����o���A�ő�o�C�g�����擾����B

Linux��UTF-8�Ȃ̂ŕ����R�[�h��Shift JIS����ύX����B
# nkf -w -Lu --overwrite 08IBARAK.csv

��@���r�̎s���̍ő�o�C�g�����擾����B
�O��̃_�u���N�H�[�e�[�V����(2�o�C�g�j�Ɖ��s�������܂�

$ cat 08IBARAK.CSV | cut -f 5 -d "," | while read line; do echo $line | wc -c ; done > result.txt
$ sort -r resltl.txt | head

���s�������܂܂Ȃ��ꍇ��

$ cat 08IBARAK.CSV | cut -f 5 -d "," | while read line; do echo -n $line | wc -c ; done > result.txt
$ sort -r result.txt | head

���߂̊m�F��
# head -2
# head -2 | cut -f 5 -d ","

wc�̊m�F
# head -1 | cut -f 5 -d "," | wc -c
���ꂾ�ƍs���Ƃł͂Ȃ��A�g�[�^���̃o�C�g����\�����Ă��܂��̂ŁA

1�s���������邽�߂ɂ̓V�F���X�N���v�g�̗͂��؂��B

while���̊m�F
�������C�i�[
# while read line; do echo $line; done <<EOF

�C���^���N�e�B�u
# while read line
> do
> echo $line
> done <<EOF
> polytech
> center
>EOF
polytechcenter#

���_
���r�̎s���̍ő�o�C�g���i���e�̃_�u���N�H�[�e�[�V�������܂݁A���s�͊܂܂Ȃ��j�́A50�o�C�g�ł��邱�Ƃ�������B

---------------------
�d�������s����菜��

# head -1000 08IBARAK.CSV | sort -t, -k5,5d -u
�q�̃R�}���h���ƁA�s���̏d���s�̐擪�͑S�āu�C�J�j�P�C�T�C�K�i�C�o�A�C�v�ɂȂ邽�߁A���̍s���폜�����f�[�^����d���s���폜����B

# grep -v �C�J�j�P�C�T�C�K�i�C�o�A�C 08IBARAK.CSV | sort -t, -k5,5d -u

----------
�푍�s�Ɛ��C�����܂ލs�𒊏o����B
# grep �푍�s 08IBARAK.CSV | grep ���C��

-----------
���������ō\������A�擪��0�Ŏn�܂�f�[�^���G�N�Z���œǂݍ��ނƂ��܂��\�����ł��Ȃ��B
���̂悤�ȃf�[�^�͐擪��'�i�V���O���N�H�[�e�[�V�����j��t����Ƃ悢�H

----------------
�X�֔ԍ��̃z�[���y�[�W�ɂ��ƁA�u��7 �S�p�ƂȂ��Ă��钬�於�̕�������38�����𒴂���ꍇ�A�܂��A���p�J�^�J�i�ƂȂ��Ă��钬�於�̃t���K�i��76�������z����ꍇ�ɂ́A�������R�[�h�ɕ������Ă��܂��B�v�Ƃ���B
���̂悤�ȃf�[�^�����݂��邩�m�F����R�}���h�́H

�X�֔ԍ��œ����f�[�^��2�s�ȏ㑱��
�f�[�^��T���H

