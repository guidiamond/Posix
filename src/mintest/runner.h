#include <string.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

volatile sig_atomic_t is_called = 0;

void  intHandler(int sig)
{
  char  c;

  printf("Do you really want to quit? [y/n] ");
  c = getchar();
  if (c == 'y' || c == 'Y')
  {
    printf("[STOP]\n");
    exit(0);
  }
  else if (c == 'n'|| c=='N') {
    signal(sig, SIG_IGN);
  }
  else
    signal(sig, intHandler);
}

void alarmHandler(int sig){
  if (is_called == 0){
    is_called = 1;
    printf("[TIME]");
  }
  exit(0);
}

int main(int argc, char *argv[]) {

  // Vars
  clock_t start, end;
  double cpu_time_used;
  int size = sizeof(all_tests)/sizeof(test_data);
  // Param exception handler
  if (argc > size || argv[1] == NULL) {
    argc = 1;
    argv[1] = "";
  }

  printf("Running %d tests:\n", size);
  printf("=====================\n\n");

  pid_t child_pid, wpid;
  int status = 0;
  int pass_count = 0;

      signal(SIGALRM, alarmHandler);
  for (int i = 0; i < size; i++) {
    if ((child_pid = fork()) == 0) {
      alarm(2);
      if ((strcmp(all_tests[i].name,argv[1]) == 0 ) || (argc == 1)) {
        start = clock();
        if (all_tests[i].function() >= 0) {
          printf("%s: [PASS]", all_tests[i].name);
          end = clock();
          cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
          printf(" (%fs)\n", cpu_time_used);
          exit(1);
        };
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf(" (%fs)\n", cpu_time_used);
      }
      exit(0);
    }
  }

  while ((wpid = wait(&status)) > 0) {
    signal(SIGINT, intHandler);
    if (WEXITSTATUS(status) == 1) {
      pass_count++;
    }
  };

  printf("\n\n=====================\n");
  if (argc == 1) {
    printf("%d/%d tests passed\n", pass_count, size);
  }
  else {
    printf("%d/%d tests passed\n", pass_count, argc-1);
  }
  return 0;
}
