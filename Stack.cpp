#include <stdio.h>
#include <TXLib.h>

typedef double StackElem;

struct Stack
{
    StackElem *data;
    size_t size;
    size_t capacity;
};

enum Errors
{
    Efault = 14,
    Enomem = 12,
};

int StackConstructor(Stack *stk, size_t capacity);
int StackDestructor(Stack *stk);

void StackDump(Stack *stk);
int StackCheck(Stack *stk);
int Verificator(Stack *stk);

int StackPush(Stack *stk, StackElem value);
int StackPop(Stack *stk);


int main()
{
    Stack stk = {};


    StackConstructor(&stk, 10);
    StackDump(&stk);

    StackPush(&stk, 100);
    StackDump(&stk);

    StackPush(&stk, 200);
    StackDump(&stk);

    StackPush(&stk, 300);
    StackDump(&stk);

    StackPop(&stk);
    StackDump(&stk);

    StackPop(&stk);
    StackDump(&stk);

    StackPop(&stk);
    StackDump(&stk);

    StackPop(&stk);
    StackDump(&stk);

    for (size_t i = 0; i < stk.size; i++)
    {
        printf("%lg ", stk.data[i]);
    }

    StackDestructor(&stk);
    StackDump(&stk);

    return 0;

}

int StackConstructor(Stack *stk, size_t capacity)
{
    stk->data = (StackElem*) calloc(capacity, sizeof(StackElem));

    if (stk->data == NULL)
    {
        return Efault;
    }

    stk->size = 0;
    stk->capacity = capacity;

    return 0;

}


int StackDestructor(Stack *stk)
{
    free(stk->data);

    //stk = NULL;
    stk->data = NULL;

    stk->size = -1;
    stk->capacity = -1;

    return 0;

}

void StackDump(Stack *stk)
{
    FILE *fp;

    if ((fp = fopen("dump.txt", "a+")) == NULL)
    {
        fprintf(stdout, "�� ������� ������� ���� \"dump.txt\".\n") ;
        exit(EXIT_FAILURE);
    }

    if (stk->data != NULL)
    {
        for (size_t i = 0; i < stk->size; i++)
        {
            fprintf(fp, "stk->data[%d] = %lg\n", i, stk->data[i]);
        }
    }
    else
    {
        fprintf(fp, "������� ���������\n");
    }


    fprintf(fp, "size = %d\n", stk->size);

    fprintf(fp, "capacity = %d\n\n", stk->capacity);

    if (fclose(fp) != 0)
    {
        fprintf (stderr, "������ ��� �������� �����\n");
    }

    fprintf(fp, "\n\n");

}

int StackCheck(Stack *stk)
{
    if (stk == NULL)
    {
        return Efault;
    }

    if (stk->data == NULL)
    {
        return Efault;
    }

    if (stk->capacity < stk->size || stk->size < 0 || stk->capacity < 0)
    {
        return Enomem;
    }

    return 0;
}

int Verificator(Stack *stk)
{
    if (StackCheck(stk)!= 0)
    {
        StackDump(stk);
        return -1;
    }

    return 0;
}


int StackPush(Stack *stk, StackElem value)
{
    Verificator(stk);

    if (stk->size > stk->capacity)
    {
        stk->capacity = stk->size;

        stk->data = (StackElem*) realloc(stk->data, stk->capacity);

    }

    stk->data[stk->size] = value;

    stk->size++;

    Verificator(stk);

    return 0;

}

int StackPop(Stack *stk)
{
    Verificator(stk);

    if (stk->size <= 0)
    {
        return Enomem;
    }

    stk->size--;

    stk->data[stk->size + 1] = 0;

    Verificator(stk);

    return stk->data[stk->size + 1];
}

