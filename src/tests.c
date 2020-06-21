#include "mintest/macros.h"
#include <unistd.h>

int test1() {
  while (1) {
  }
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

int test4() {
  int pow = 1;
  for (int i = 0; i < 10; i++) {
    pow *= 2;
  }
  // for loop with pow

  test_assert(pow > 512, "For test");
  return 0;
}

int test5() {
  double pow = 1 / 0;
  // loop infinito
  test_assert(pow > 512, "Divisão por zero");

  return 0;
}

int test6() {
  // Teste lento
  sleep(10);
  test_assert(513 > 512, "Alarm test");

  return 0;
}

int test7() {
  char *a = NULL;
  *a = 'a';
  // cause erro e termine com falha de segmentação
  test_assert(1 == 1, "Segmentation test");

  return 0;
}

int test8() {
  // tenha testes que façam muitos prints
  for (int i = 1; i <= 10; i++) {
    test_printf("Print %d de 100\n", i);
  }
  return 0;
}

int test9() {
  // assert passa
  test_assert(1 == 1, "Sleep Pass");
  sleep(10);
  // assert falha
  test_assert(1 == 0, "Sleep Fail");

  return 0;
}

int test10() {
  // tenha testes que sejam rápidos
  test_printf("Quick Pass\n");
  return 0;
}

int test11() {
  test_assert(0 == 1, "Quick Fail");
  return 0;
}

int test12() {
  // faça muito trabalho, mas eventualmente acabe (sem usar sleep )
  int sum = 0;
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      for (int k = 0; k < 1000; k++) {
        sum++;
      }
    }
  }
  test_assert(100 * 100 * 100 == sum, "Heavy Work");
  return 0;
}
test_list = {TEST(test1), TEST(test2),  TEST(test3),  TEST(test4),
             TEST(test5), TEST(test6),  TEST(test7),  TEST(test8),
             TEST(test9), TEST(test10), TEST(test11), TEST(test12)};

#include "mintest/runner.h"
