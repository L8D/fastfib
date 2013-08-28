#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double clock_now() {
  struct timeval now;
  gettimeofday(&now, NULL);

  return (double)now.tv_sec + (double)now.tv_usec/1.0e6;
}

typedef unsigned long long big;

big fib(big n, big *c) {
  if(!c[n] && n != 0)
    c[n] = fib(n - 1, c) + fib(n - 2, c);
  return c[n];
}

big fibc(int n) {
  big *c = calloc(n + 1, sizeof *c);
  c[1] = 1;

  big r = fib(n, c);
  free(c);
  return r;
}

int main(int argc, char *argv[]) {
  if(argc == 1) {
    fprintf(stderr, "Usage: %s <number>\n", argv[0]);
    return EXIT_FAILURE;
  }

  big n;
  sscanf(argv[1], "%llu", &n);

  double t;

  t = clock_now();
  big r = fibc(n);
  t = clock_now() - t;

  printf("Got %llu in %g seconds\n", r, t*1000);
  return 0;
}
