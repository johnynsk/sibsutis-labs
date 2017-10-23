#include <locale>
#include <stdlib.h>
#include <string.h>
#include <cstdio>

const int maxn=10000;
struct node
{
    char znac[20];
    int key;
};

int kolcol; // количество коллизий
int kolsl; // количество слов
int ObTable; // хз

node hashtable[maxn];

int hash(char* s)
{
    int result=0;
    int i=0;
    for (i=0; i<(int)strlen(s); i++)
    {
        result=(255*result+abs(s[i]))%kolsl;
    }
    return result;
}

//линейные пробы
int linhash(char* s)
{
    //получаем хэш-код слова
    int hs=hash(s);
    int num=hs;
    //идем по массиву пока не найдем ему место
    //сразу же считаем количество коллизий
    while (1)
    {
        //если в ячейке таблицы уже есть значение
        //то коллизия и переходим к следующему полю
        if (hashtable[num].key!=0)
        {
            kolcol++;
            //строки равны то выходим
            if (strcmp(hashtable[num].znac,s)==0) break;
            num++;
            //если вышли за пределы хэш-таблицы, то увеличиваем ее размер
            if (num>kolsl && num<kolsl) kolsl=num;
            if (num>maxn) num=num%maxn;
        }
        else
        {
            ObTable++;
            strcpy(hashtable[num].znac,s);
            hashtable[num].key=hs;
            break;
        }
    }
    return 0;
}

//квадратичные пробы
int kvhash(char* s)
{
    //получаем хэш-код слова
    int hs=hash(s);
    int num=hs;
    int zn=1;
    int i=1;
    //идем по массиву пока не найдем ему место
    //сразу же считаем количество коллизий
    while (1)
    {
        //если в ячейке таблицы уже есть значение
        //то коллизия и переходим к следующему полю
        if (hashtable[num].key!=0)
        {
            kolcol++;
            //строки равны то выходим
            if (strcmp(hashtable[num].znac,s)==0) break;
            //находим новую позицию как квадрат, меняем знак
            num=(num+i*zn)*(num+i*zn); zn=-zn;
            if (zn==1) i++;
            //если вышли за пределы хэш-таблицы, то увеличиваем ее размер
            if (num>kolsl && num<maxn) kolsl=num;
            //проверяем, не вышли ли за пределы массива
            if (num>maxn) num=num%maxn;
            if (num<0) num=1;
        }
        else
        {
            ObTable++;
            strcpy(hashtable[num].znac,s);
            hashtable[num].key=hs;
            break;
        }
    }
    return 0;
}


int main()
{
    setlocale(0,"");
    char s[20];
    int KolSlFile=0;
    kolsl=200;
    ObTable=0;
    kolcol=0;
    FILE* f = fopen( "text.txt", "r" ); // читаем текст с файла
    //очищаем хеш-таблицу
    memset(hashtable,NULL,sizeof(hashtable));
    while (!feof(f)) // пока не конец файла
    {
        KolSlFile++; // количество слов в файле
        fscanf(f,"%s",s); // читаем очередное слово
        kvhash(s); // квадратичные пробы
    }
    fclose(f);
    printf("Линейные пробы:\n  Число слов в файле= %i\n  Размер хэш-таблицы= %i\n  Число коллизий= %i\n\n", KolSlFile, ObTable, kolcol);
    f = fopen( "text.txt", "rt" );
    memset(hashtable,0,sizeof(hashtable));
    KolSlFile=0;
    ObTable=0;
    kolcol=0;
    while (!feof(f))
    {
        KolSlFile++;
        fscanf(f,"%s",s);
        kvhash(s);
    }
    printf("Квадратичные пробы:\n  Число слов в файле= %i\n  Размер хэш-таблицы= %i\n  Число коллизий= %i\n\n", KolSlFile, ObTable, kolcol);
    fclose(f);
    return 0;
}
