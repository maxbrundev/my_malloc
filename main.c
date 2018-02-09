//#include <stdio.h>
//#include <my_put_number.h>
//#include <my_put_char.h>
//#include "malloc_perso.h"
//#include "free_perso.h"
//
//int main() {

//    int* i = malloc_perso(sizeof(int));
//
//    *i = 5;
//
//    my_put_number(*i);
//
//    int* a = calloc_perso(4, sizeof(int));
//
//    *a = 10;
//
//    my_put_number(*a);
//
//    free_perso(i);
//
//    my_put_number(*i);
//
//    my_put_char('\n');
//
//    int* j = malloc_perso(sizeof(int));
//
//    *j = 15;
//
//    my_put_number(*j);
//
//    my_put_char('\n');
//
//    char* k = malloc_perso(sizeof(char));
//
//    *k = 'a';
//
//    my_put_char(*k);
//
//    free_perso(k);
//
//    my_put_char(*k);

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "malloc_perso.h"
#include "free_perso.h"

    struct foo {
        u_int32_t l;
        double f;
        short int sd;
        char* ptr;
    };

    int main()
    {
        clock_t start, end;
        double cpu_time_used;

        size_t testSize = aligned_size(40000 * sizeof(struct foo));


        struct foo* arr1 = NULL;
        struct foo* arr2 = NULL;
        struct foo* arr3 = NULL;
        struct foo* arr4 = NULL;
        printf("\n=======Memory Performances=======\n");

        printf("Array testing type : struct foo\n");
        printf("Array testing size : %zu\n", testSize);

        printf("\n-------C STD allocations-------\n");
        {
            start = clock();
            arr3 = (struct foo*)malloc(testSize);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("malloc\t\t:  %lfs cpu_time.\n", cpu_time_used);


            start = clock();
            arr4 = (struct foo*)calloc(testSize,1);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("calloc\t\t:  %lfs cpu_time.\n", cpu_time_used);
        }

        printf("\n-------custom allocations-------\n");
        {
            start = clock();
            arr1 = (struct foo*)malloc_perso(testSize);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("malloc\t\t:  %lfs cpu_time.\n", cpu_time_used);


            start = clock();
            arr2 = (struct foo*)calloc_perso(testSize,1);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("calloc\t\t:  %lfs cpu_time.\n", cpu_time_used);
        }


        printf("\n-------C STD free-------\n");
        {
            start = clock();
            free(arr4);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("free \t\t:  %lfs cpu_time.\n", cpu_time_used);


            start = clock();
            free(arr3);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("free\t\t:  %lfs cpu_time.\n", cpu_time_used);
        }

        printf("\n-------custom free-------\n");
        {
            start = clock();
            free_perso(arr2);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("free \t\t:  %lfs cpu_time.\n", cpu_time_used);


            start = clock();
            free_perso(arr1);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("free\t\t:  %lfs cpu_time.\n", cpu_time_used);
        }

    return 0;
}