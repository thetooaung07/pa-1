#include <stdio.h>
#include <stdlib.h>

typedef struct domino
{
    char id;
    int *number;
    int items;
    char *duplicates;
    int count;
    int duplicated;
} domino;

domino *push_array(domino *array, int *size, int *capacity, char id)
{
    if (*size >= *capacity)
    {
        if (*capacity == 0)
            *capacity = 1;
        *capacity = (*capacity) * 2;
        array = (domino *)realloc(array, (*capacity * sizeof(domino)));
    }
    array[*size].items = 0;
    array[*size].id = id;
    array[*size].number = NULL;
    array[*size].duplicates = NULL;
    array[*size].count = 0;
    array[*size].duplicated = 0;
    (*size)++;
    return array;
}

domino *push_number(domino *array, int *size, int *capacity, int array_size, int x)
{
    if (*size >= *capacity)
    {
        if (*capacity == 0)
            *capacity = 1;
        *capacity = (*capacity) * 2;
        array[array_size].number = (int *)realloc(array[array_size].number, (*capacity) * sizeof(int));
    }
    array[array_size].number[*size] = x;
    array[array_size].items++;
    (*size)++;
    return array;
}

int compare(int *a, int a_size, int *b, int b_size)
{
    if (a_size != b_size)
    {
        return 0;
    }
    int start = -1;
    for (int i = 0; i < a_size; i++)
    {
        if (a[i] == b[0])
        {
            start = i;
        }
    }
    if (start == -1)
    {
        return 0;
    }
    // printf("a_size: %d\n",a_size);
    for (int i = start, j = 0; j < b_size; j++, i++)
    {
        if (i >= a_size)
        {
            i = 0;
        }
        printf("start:%d\n", start);
        printf("i : %d , j: %d \n", i, j);
        if (a[i] != b[j])
        {
            // printf("not equal\n");
            return 0;
        }
    }
    return 1;
}

domino *push_duplicate(domino *array, int first, int second)
{
    array[first].duplicated = array[second].duplicated = 1;
    array[first].count++;
    array[first].duplicates = (char *)realloc(array[first].duplicates, array[first].count);
    array[first].duplicates[array[first].count - 1] = array[second].id;
    return array;
}

int main()
{
    domino *list = NULL;
    int size = 0, capacity = 0;
    char id, start;
    char check = 'a';
    while (scanf(" %c %c", &id, &start) == 2 && start == '[')
    {
        if (id != check)
        {
            for (int i = 0; i < size; i++)
            {
                free(list[i].number);
                free(list[i].duplicates);
            }

            free(list);
            printf("Invalid input1\n");
            return EXIT_FAILURE;
        }

        check++;
        list = push_array(list, &size, &capacity, id);
        // printf("CHECK: %c \n",check);
        int temp;
        char end;
        int number_size = 0, number_capacity = 0;
        while (1)
        {
            if (scanf(" %d %c", &temp, &end) != 2 || (end != ',' && end != ']'))
            {
                for (int i = 0; i < size; i++)
                {
                    free(list[i].number);
                    free(list[i].duplicates);
                }

                free(list);
                printf("Invalid input.\n");
                return EXIT_FAILURE;
            }
            if (temp < 0)
            {
                for (int i = 0; i < size; i++)
                {
                    free(list[i].number);
                    free(list[i].duplicates);
                }

                free(list);
                printf("Invalid input.\n");
                return EXIT_FAILURE;
            }

            list = push_number(list, &number_size, &number_capacity, size - 1, temp);
            if (end == ']')
            {
                break;
            }
        }
    }
    if (!feof(stdin))
    {
        for (int i = 0; i < size; i++)
        {
            free(list[i].number);
            free(list[i].duplicates);
        }

        free(list);
        printf("Invalid input2\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (!list[j].duplicated && compare(list[i].number, list[i].items, list[j].number, list[j].items))
            {
                printf("%c=%c\n", list[i].id, list[j].id);
                list = push_duplicate(list, i, j);
            }
        }
    }

    // for(int i = 0 ; i < size ; i++){
    //     printf("%c: %d \n",list[i].id,list[i].items);
    //     for(int j = 0 ; j < list[i].items ; j++){
    //         printf("%d",list[i].number[j]);
    //     }
    //     printf("\n");
    // }

    int max = 0;
    for (int i = 0; i < size; i++)
    {
        if (list[i].count > max)
        {
            printf("list[i].count %d", list[i].count);
            max = list[i].count;
        }
    }

    printf("%d\n", max + 1);

    for (int k = 0; k < size; k++)
    {
        if (list[k].count == 0)
        {
            continue;
        }
        printf("%c", list[k].id);
        for (int i = 0; i < list[k].count; i++)
        {
            printf(" = %c", list[k].duplicates[i]);
        }
        printf("\n");
    }
    for (int i = 0; i < size; i++)
    {
        free(list[i].number);
        free(list[i].duplicates);
    }

    free(list);

    return 0;
}

//
