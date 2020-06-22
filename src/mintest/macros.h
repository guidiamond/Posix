#include <stdio.h>
#include "../colors.h"

typedef int (*test_func)();

typedef struct {
    char name[50];
    test_func function;
} test_data;

#define test_printf (printf("%s: ", __func__));printf

#define test_assert(expr, str) { if(!(expr)) { printf(ANSI_COLOR_RESET"%s: ", __func__); printf(ANSI_COLOR_ERROR"[FAIL]"); printf(ANSI_COLOR_RESET"%s in %s:%d", str, __FILE__, __LINE__); return -1; } }

#define TEST(f) {.name=#f, .function=f}

#define test_list test_data all_tests[]

