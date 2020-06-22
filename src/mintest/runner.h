#include <string.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include "../colors.h"

const char *test_name = NULL;

void  intHandler(int sig)
{
  char  c;

  printf(ANSI_COLOR_MESSAGE"Do you really want to quit? [y/n] ");
  c = getchar();
  if (c == 'y' || c == 'Y')
  {
    printf(ANSI_COLOR_PROCESS_CALL"[STOP]\n");
    exit(0);
  }
  else if (c == 'n'|| c=='N') {
    signal(sig, SIG_IGN);
  }
  else
    signal(sig, intHandler);
}


void alarmHandler(int sig){
  printf(ANSI_COLOR_PROCESS_CALL"%s [TIME]\n", test_name);
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

  printf(ANSI_COLOR_MESSAGE"Running %d tests:\n", size);
  printf("=====================\n\n");

  pid_t child_pid, wpid;
  int status = 0;
  int pass_count = 0;

  signal(SIGALRM, alarmHandler);
  for (int i = 0; i < size; i++) {
    if ((child_pid = fork()) == 0) {
      alarm(2);
      if ((strcmp(all_tests[i].name,argv[1]) == 0 ) || (argc == 1)) {
        test_name = argv[1];
        start = clock();
        if (all_tests[i].function() >= 0) {
          printf(ANSI_COLOR_RESET"%s: ", all_tests[i].name);
          printf(ANSI_COLOR_SUCCESS"[PASS]\n");
          end = clock();
          cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
          printf(ANSI_COLOR_RESET" (%fs)\n", cpu_time_used);
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
    printf(ANSI_COLOR_RESET"%d/%d tests passed\n", pass_count, size);
  }
  else {
    printf(ANSI_COLOR_RESET"%d/%d tests passed\n", pass_count, argc-1);
  }
  return 0;
}
