#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
  clock_t start, end;
  double cpu_time_used;
  int size = sizeof(all_tests)/sizeof(test_data);
  if (argc >= 2 && argc <= size) {
    size = argc - 1;
  }

  printf("Running %d tests:\n", size);
  printf("=====================\n\n");
  int pass_count = 0;
  for (int i = 0; i < size; i++) {
    start = clock();
    if (all_tests[i].function() >= 0) {
      printf("%s: [PASS]", all_tests[i].name);
      pass_count++;
    };
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("(%fs)\n", cpu_time_used);
  }

  printf("\n\n=====================\n");
  printf("%d/%d tests passed\n", pass_count, size);
  return 0;
}
