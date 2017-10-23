/*
* Написать программу "Телефонный справочник", которая обрабатывает
* данные об абонентах телефонной станции.
* Каждый абонент имеет имя, адрес, телефонный номер.
* В программе описать массив абонентов (назовем его справочник).
* В справочнике должно быть не менее 20 элементов, которые заполняются
* либо программно, либо считываются из файла.
* С помощью индексов и фильтров упорядочить справочник
* по телефонному номеру по убыванию
*/
#include <stdlib.h>
#include <time.h>
#include <locale>

#define SIZE_buff 50

struct Kniga {
    char name[50];
    char address[50];
    unsigned number;
};
struct ListK {
    Kniga book;
    ListK *next;
};
struct List {
    ListK *first;
    ListK *last;
};

void VivodList(List &queue)
{
    ListK *p;
    p = queue.first;

    printf("\nЭлементы списка:\n");
    while (p != NULL) { // пока не онец списка - выводим каждый элемент
        printf("имя: %s адрес: %s номер:%d\n",
            p->book.name, p->book.address, p->book.number);
        p = p->next;
    }
    printf("\n");
}
void delList(List &queue)
{
    ListK *p, *temp;
    p = queue.first;

    while (p != NULL) { // пока не дойдем до конца списка - удаляем каждый
        temp = p;
        p = p->next;
        delete temp;
    }
    queue.first = queue.last = NULL;
}
void add(List &queue)
{
    char buffer[SIZE_buff];
    char ch;

    do {
        ListK *p;
        p = new ListK;

        p->next = NULL;

        printf("Имя: ");
        fgets(buffer, SIZE_buff, stdin); sscanf(buffer, "%s", p->book.name);

        printf("Адрес: ");
        fgets(buffer, SIZE_buff, stdin); sscanf(buffer, "%s", p->book.address);

        printf("Номер: ");
        fgets(buffer, SIZE_buff, stdin); sscanf(buffer, "%d", &p->book.number);

        if (queue.first != NULL) // если список существует - добавляем в конец
            queue.last->next = p;
        else
            queue.first = p; // новый становится первым
        queue.last = p;    // новый становится последним

        printf("Закончить? Y/n: ");
        fgets(buffer, SIZE_buff, stdin); sscanf(buffer, "%c", &ch);

    } while (toupper(ch) != 'Y');
}
void Vivod(List &queue)
{

    ListK **index_Q; // Массив указателей
    ListK *p;
    int n, i;
    char c[4];
    printf("Введите границы поиска по имени: (с какой по какую букву) через пробел\n");
    scanf("%c %c",&c[0],&c[1]);
    printf("Введите границы поиска по адрессу: (с какой по какую букву) через пробел\n");
    scanf("%c %c",&c[2],&c[3]);


    n = 0;
    p = queue.first; // на начало списка встаем
    while (p != NULL) { // считаем число элементов
        p = p->next;
        n++;
    }

    index_Q = new ListK*[n]; // выделяем память под указатель на список
    p = queue.first;     // на начало списка
    i = 0;
    while (p != NULL) { // каждый элемент массива указателей (МУ) - отдельный элемент списка
        index_Q[i] = p;
        p = p->next;
        i++;
    }

    for(int i=0;i<n;i++) // вывод по заданному критерию
    {
        if(index_Q[i]->book.name[0]>=c[0] && index_Q[i]->book.name[0]<=c[1] || index_Q[i]->book.address[0]>=c[3] && index_Q[i]->book.address[0]<=c[4] )
            printf("имя: %s адрес: %s номер:%d\n", index_Q[i]->book.name, index_Q[i]->book.address, index_Q[i]->book.number);
    }

    delete index_Q;
}
void save(List &queue)
{
    FILE *fp;
    ListK *p;

    fp = fopen("book.bin", "wb");
    if (fp == NULL) {
        perror("Невозможно создать файл");
        return;
    }

    printf("Сохранение списка... \n");

    p = queue.first;
    while (p != NULL)
    {
        // записывем структуру в файл
        fwrite(&p->book, sizeof(p->book), 1, fp);
        p = p->next;
    }

    fclose(fp);
}
void load(List &queue)
{
    FILE *fp;
    ListK *p;
    Kniga book;

    fp = fopen("book.bin", "rb");
    if (fp == NULL) {
        perror("Невозможно прочитать файл");
        return;
    }

    printf("Загрузка списка... \n");
    fread(&book, sizeof(book), 1, fp);
    while (!feof(fp)) {
        p = new ListK;
        p->book = book;
        p->next = NULL;

        if (queue.first != NULL)
            queue.last->next = p;
        else
            queue.first = p;
        queue.last = p;
        fread(&book, sizeof(book), 1, fp);
    }
}

int main()
{
    setlocale(0,"");
    char buffer[SIZE_buff]; // буферная строка
    List queue; // список записей
    int ch; // переменная выбора

    queue.first = queue.last = NULL; // инициализация списка

    for (;;) { // меню
        fflush(stdin);//Очистка буфера клавиатуры
        printf("1. Создание списка\n");
        printf("2. Просмотр телефонной книги \n");
        printf("3. Сохранить\n");
        printf("4. Загрузить из файла\n");
        printf("5. Вывести список\n");
        printf("0. Выйти\n");
        printf("Введите команду: ");

        fgets(buffer, SIZE_buff, stdin); sscanf(buffer, "%d", &ch);
        switch (ch) {
        case 1:
            add(queue); // добавить в список
            break;
        case 2:
            Vivod(queue); // вывод списка на экран
            break;
        case 3:
            save(queue); // сохранить в файл
            break;
        case 4:
            load(queue); // загрузить из файла
            break;
        case 5: VivodList(queue); // вывод списка
            break;
        case 0:
            delList(queue); // удалить список
            return 0;
        }
    }
}



