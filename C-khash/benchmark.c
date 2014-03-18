#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>

#include "khash.h"

KHASH_MAP_INIT_INT(khint_t, khint_t)
#define hash_eq(a, b) ((a).key == (b).key)
#define hash_func(a)  ((a).key)

typedef unsigned long utime_t;

utime_t utime()
{
  struct timeval tv;

  (void) gettimeofday(&tv, NULL);
  return (utime_t) tv.tv_sec * 1000000 + (utime_t) tv.tv_usec;
}

utime_t lookup(khash_t(khint_t) *m, khint_t *b, int r)
{
  int i;
  unsigned int position;
  utime_t t1, t2;
  unsigned long long sum;
  
  sum = 0;

  t1 = utime();
  for (i = 0; i < r; i ++)
    {
      position = kh_get(khint_t, m, b[i]);
      if (position != kh_end(m))
	sum += kh_value(m, position);
    }
  t2 = utime();

  return t2 - t1;
}

void randomize_input(khint_t *a, int n, khint_t *b, int r)
{
  int i;

  for (i = 0; i < n; i ++)
    a[i] = rand();
  for (i = 0; i < r; i ++)
    b[i] = i % 2 ? a[rand() % n] : (khint_t) rand();
}

void usage()
{
  extern char *__progname;

  fprintf(stderr, "usage: %s <size> <requests> <measurements>\n", __progname);
  exit(EXIT_FAILURE);
}

void unused()
{
  kh_del_khint_t(0, 0);
  kh_clear_khint_t(NULL);
}

int main(int argc, char **argv)
{
  int n, r, k, i, j;
  int ret;
  khint_t *a, *b;
  khash_t(khint_t) *m;
  unsigned int position;
  utime_t t;

  if (argc != 4)
    usage();
  
  n = strtol(argv[1], NULL, 0);
  r = strtol(argv[2], NULL, 0);
  k = strtol(argv[3], NULL, 0);

  a = malloc(n * sizeof *a);
  b = malloc(r * sizeof *b);

  t = 0;
  for (j = 0; j < k; j ++)
    {
      m = kh_init(khint_t);
      randomize_input(a, n, b, r);
      for (i = 0; i < n; i ++)
	{	  
	  position = kh_put(khint_t, m, a[i], &ret);
	  kh_val(m, position) = i;
	}

      t += lookup(m, b, r);
      kh_destroy(khint_t, m);
    }
  
  (void) fprintf(stdout, "%.2f MOPS\n", (double) r * k / (double) t);

  return EXIT_SUCCESS;
}
