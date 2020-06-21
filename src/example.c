#include "mintest/macros.h"
#include <pthread.h>

int test1() {
  test_printf("Hello! %d %f\n", 3, 3.14);
  return 0;
}

int test2() {
  test_assert(1 == 0, "This always fails!");
  printf("This never runs!\n");
  test_assert(1 == 1, "Neither this.");
  return 0;
}

int test3() {
  test_printf("<-- Name of the function before the printf!\n");
  test_assert(1 == 1, "This always succeeds");
  return 0;
}

test_list = {TEST(test1), TEST(test2), TEST(test3)};

#include "mintest/runner.h"
