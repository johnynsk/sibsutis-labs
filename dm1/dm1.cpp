/**
 * Лабораторная работа №1
 * Задача №1
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <stdio.h>
#include <cstdlib>
#include <iostream>

#define OPERATION_HALT 0
#define OPERATION_COMPARE 1
#define OPERATION_UNION 2
#define OPERATION_INTERSECTION 3
#define OPERATION_RESIDUAL 4
#define OPERATION_SYMMETRY_RESIDUAL 5
#define OPERATION_OPOSITE_RESIDUAL 6
#define OPERATION_OPOSITE_COMPARE 7
#define OPERATION_INPUT_A 8
#define OPERATION_INPUT_B 9

using namespace std;

struct array {
    char *items;
    int length;
};

/**
 * Проверка на дубликаты в массиве
 */
bool hasDuplicate(struct array *data, char item)
{
    for (int i = 0; i < data->length; i++) {
        if (data->items[i] == item) {
            return true;
        }
    }
    return false;
}

/**
 * Добавить элемент в массив
 */
struct array *pushItem(struct array *result, char item)
{
    result->items = (char*) realloc(result->items, sizeof(char) * (result->length + 1));
    result->items[result->length] = item;
    result->length++;

    return result;
}

/**
 * Замена данных в массиве
 */
struct array *replaceItems(struct array *pointer, struct array *expected)
{
    pointer->items = expected->items;
    pointer->length = expected->length;

    return pointer;
}

/**
 * Ввод элементов массива с stdin
 */
struct array* readItems()
{
    array* result = (struct array*) malloc(sizeof(struct array));
    char item;

    result->length = 0;

    while (true) {
        item = (char) getchar();

        if (item == 27) {
            break;
        }

        if (item < 'a' || item > 'z' || hasDuplicate(result, item)) {
            continue;
        }

        pushItem(result, item);
    }

    return result;
}

/**
 * Проверка на подмножество
 */
bool checkSubset(struct array *A, struct array *B)
{
    bool found;

    if (!A->length) {
        return true;
    }

    for (int i = 0; i < A->length; i++) {
        found = false;

        for (int j = 0; j < B->length; j++) {
            if (B->items[j] == A->items[i]) {
                found = true;
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

/**
 * Объединение множеств
 */
struct array *getUnion(struct array *A, struct array *B)
{
    array *result = (array*) malloc (sizeof(struct array));
    result->length = 0;
    bool found;

    for (int i = 0; i < A->length; i++) {
        pushItem(result, A->items[i]);
    }

    for (int i = 0; i < B->length; i++) {
        found = false;

        for (int j = 0; j < result->length; j++) {
            if (result->items[j] == B->items[i]) {
                found = true;
            }
        }

        if (!found) {
            pushItem(result, B->items[i]);
        }
    }

    return result;
}

/**
 * Пересечение множеств
 */
struct array *getIntersection(struct array *A, struct array *B)
{
    array *result = (array*) malloc (sizeof(struct array));
    result->length = 0;

    for (int i = 0; i < A->length; i++) {
        for (int j = 0; j < B->length; j++) {
            if (A->items[i] == B->items[j]) {
                pushItem(result, A->items[i]);
            }
        }
    }

    return result;
}

/**
 * Разность множеств
 */
struct array *getResidual(struct array *A, struct array *B)
{
    array *result = (array*) malloc (sizeof(struct array));
    result->length = 0;
    bool found;

    for (int i = 0; i < A->length; i++) {
        found = false;

        for (int j = 0; j < B->length; j++) {
            if (A->items[i] == B->items[j]) {
                found = true;
            }
        }

        if (!found) {
            pushItem(result, A->items[i]);
        }
    }

    return result;
}

/**
 * Печать массива на экран
 */
void output(struct array* data)
{
    cout<<"array("<<data->length<<") ["<<endl;
    for (int i = 0; i < data->length; i++) {
        cout<<"\t'"<<data->items[i]<<"'"<<endl;
    }
    cout<<"]"<<endl;
}

void outputCommented(struct array* data, const char *comment)
{
    cout<<comment<<endl;
    output(data);
}


/**
 * Симметрическая разность
 */
struct array *getSymmetrySub(struct array *A, struct array *B)
{
    return getResidual(getUnion(A, B), getIntersection(A, B));
}

bool iteratorLoop(struct array *A, struct array *B, int operation)
{
    struct array *result;
    const char *comment;

    switch(operation) {
        case OPERATION_COMPARE:
            outputCommented(A, "A=");
            outputCommented(B, "B=");

            if (checkSubset(A, B)) {
                cout<<"A subset B"<<endl;
            } else {
                cout<<"A !subset B"<<endl;
            }

            return true;


        case OPERATION_UNION:
            result = getUnion(A, B);
            comment = "A&B = ";
            break;

        case OPERATION_INTERSECTION:
            result = getIntersection(A, B);
            comment = "A|B = ";
            break;

        case OPERATION_RESIDUAL:
            result = getResidual(A, B);
            comment = "A\\B = ";
            break;

        case OPERATION_SYMMETRY_RESIDUAL:
            result = getSymmetrySub(A, B);
            comment = "A delta B = ";
            break;

        case OPERATION_OPOSITE_RESIDUAL:
            result = getResidual(B, A);
            comment = "B\\A = ";
            break;

        case OPERATION_OPOSITE_COMPARE:
            outputCommented(A, "A = ");
            outputCommented(B, "B = ");

            if (checkSubset(B, A)) {
                cout<<"B subset A"<<endl;
            } else {
                cout<<"B !subset A"<<endl;
            }

            return true;

        case OPERATION_INPUT_A:
            cout<<"Ввод множества A. Конец ввода - символ ESC"<<endl;
            replaceItems(A, readItems());

            return true;

        case OPERATION_INPUT_B:
            cout<<"Ввод множества B. Конец ввода - символ ESC"<<endl;
            replaceItems(A, readItems());

            return true;

        default:
            return false;

    }

    outputCommented(A, "A = ");
    outputCommented(B, "B = ");
    outputCommented(result, comment);
    return true;
}

void printUsage()
{
    cout<<"Введите требуемую операцию: "<<endl;
    cout<<"1 - сравнение A subset B"<<endl;
    cout<<"2 - объединение A&B"<<endl;
    cout<<"3 - пересечение A|B"<<endl;
    cout<<"4 - разность A\\B"<<endl;
    cout<<"5 - симметрическая разность A delta B"<<endl;
    cout<<"6 - разность B\\A"<<endl;
    cout<<"7 - сравнение B subset A"<<endl;
    cout<<"8 - задать множество A"<<endl;
    cout<<"9 - задать множество B"<<endl;
    cout<<"0 - выход\n> "<<endl;

}

int main()
{
    struct array *A, *B;
    char command;

    cout<<"Ввод множества A. Конец ввода - символ ESC"<<endl;
    A = readItems();
    cout<<"Ввод множества B. Конец ввода - символ ESC"<<endl;
    B = readItems();

    do {
        printUsage();
        cin>>command;

        if (command - '0' == OPERATION_HALT) {
            break;
        }

        if (!iteratorLoop(A, B, command - '0')) {
            cout<<"Неизвестная команда!"<<endl;
        }
    } while (true);

    return 0;
}

