#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define UNUSED(x) ((void)(x))

int main(int argc, char *argv[]) {
  UNUSED(argc);
  UNUSED(argv);
  pid_t pid = fork();
  const double LIFETIME_SECS = 10.0;
  if (pid < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    printf("Running fibonacci ... ");
    fflush(stdout);
    execl("./fibonacci", "fibonacci", NULL);
    perror("execl");
    exit(EXIT_FAILURE);
  } else {
    struct timespec start, now;
    double dt_secs;
    clock_gettime(CLOCK_MONOTONIC, &start);
    do {
      clock_gettime(CLOCK_MONOTONIC, &now);
      dt_secs = (now.tv_sec - start.tv_sec) +
                (now.tv_nsec - start.tv_nsec) / 1000000000.0;
      usleep(1000);
    } while (dt_secs < LIFETIME_SECS);
    kill(pid, SIGTERM);
    printf("\nelapsed time: %lf seconds\n", dt_secs);
    printf("\ncorrection factor: %lf\n", dt_secs / LIFETIME_SECS);
    wait(NULL);
  }
  return EXIT_SUCCESS;
}
