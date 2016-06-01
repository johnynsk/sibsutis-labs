/**
 * Лабораторная работа №1
 * Задача №1
 *
 * Выполнил: студент СибГУТИ группы ЗП-51
 * @author Evgeniy Vasilev <info@evgeniyvasilev.ru>
 */
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <string>

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

struct array {
    char* items;
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
    bool found;

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
    printf("array(%d) [\n", data->length);
    for (int i = 0; i < data->length; i++) {
        printf("\t'%c', \n", data->items[i]);
    }
    printf("]\n");
}

void outputCommented(struct array* data, const char *comment)
{
    printf("%s\n", comment);
    output(data);
}


/**
 * Симметрическая разность
 */
struct array *getSymmetrySub(struct array *A, struct array *B)
{
    return getResidual(getUnion(A, B), getIntersection(A, B));
}

bool iterator(struct array *A, struct array *B, int operation)
{
    struct array *result;
    const char *comment;

    switch(operation) {
        case OPERATION_COMPARE:
            outputCommented(A, "A=");
            outputCommented(B, "B=");

            if (checkSubset(A, B)) {
                printf("A subset B\n");
            } else {
                printf("A !subset B\n");
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
                printf("B subset A\n");
            } else {
                printf("B !subset A\n");
            }

            return true;

        case OPERATION_INPUT_A:
            printf("Ввод множества A. по окончанию - ESC\n");
            replaceItems(A, readItems());

            return true;

        case OPERATION_INPUT_B:
            printf("Ввод множества B. по окончанию - ESC\n");
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

int main()
{
    struct array *A, *B;
    int command;

    printf("Ввод множества A. по окончанию - ESC\n");
    A = readItems();
    printf("Ввод множества B. по окончанию - ESC\n");
    B = readItems();

    do {
        printf("Введите требуемую операцию: \n");
        printf("1 - сравнение A subset B\n");
        printf("2 - объединение A&B\n");
        printf("3 - пересечение A|B\n");
        printf("4 - разность A\\B\n");
        printf("5 - симметрическая разность A delta B\n");
        printf("6 - разность B\\A\n");
        printf("7 - сравнение B subset A\n");
        printf("8 - задать множество A\n");
        printf("9 - задать множество B\n");
        printf("0 - выход\n> ");

        scanf("%d", &command);

        if (command == OPERATION_HALT) {
            break;
        }

        if (!iterator(A, B, command)) {
            printf("Неизвестная команда!\n");
        }
    } while (true);

    return 0;
}

