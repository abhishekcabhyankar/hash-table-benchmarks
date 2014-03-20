#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>

#include <dtype.h>

typedef unsigned long utime_t;

utime_t utime()
{
  struct timeval tv;

  (void) gettimeofday(&tv, NULL);
  return (utime_t) tv.tv_sec * 1000000 + (utime_t) tv.tv_usec;
}

utime_t lookup(dmap_32_t *m, uint32_t *b, int r)
{
  size_t i, position;
  utime_t t1, t2;
  uint64_t sum;

  sum = 0;

  t1 = utime();
  for (i = 0; i < (size_t) r; i ++)
    {
      position = dmap_32_find(m, b[i]);
      if (position != dmap_32_end(m))
	sum += *(uint32_t *) dmap_32_get(m, position);
    }
  t2 = utime();

  return t2 - t1;  
}

void randomize_input(uint32_t *a, int n, uint32_t *b, int r, float p)
{
  int i, hit;

  for (i = 0; i < n; i ++)
    a[i] = (uint32_t) rand() % (UINT32_MAX - 2);
  for (i = 0; i < r; i ++)
    {
      hit = ((float) rand() / (float) RAND_MAX) <= p;
      b[i] = hit ? a[rand() % n] : (uint32_t) rand() % (UINT32_MAX - 2);
    }
}

void usage()
{
  extern char *__progname;

  fprintf(stderr, "usage: %s <size> <requests> <measurements> <hit probability>\n", __progname);
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
  long k, n, r, i, j;
  float p;
  uint32_t *a, *b; 
  dmap_32_t *m;
  utime_t t;

  if (argc != 5)
    usage();
  
  n = strtol(argv[1], NULL, 0);
  r = strtol(argv[2], NULL, 0);
  k = strtol(argv[3], NULL, 0);
  p = strtof(argv[4], NULL);

  a = malloc(n * sizeof *a);
  b = malloc(r * sizeof *b);
  
  t = 0;
  for (j = 0; j < k; j ++)
    {
      m = dmap_32_new(sizeof(uint32_t), UINT32_MAX, UINT32_MAX - 1);
      dmap_32_max_load_factor(m, 0.5);
      randomize_input(a, n, b, r, p);
      
      for (i = 0; i < n; i ++)
	dmap_32_insert(m, a[i], &i);

      t += lookup(m, b, r);
      
      dmap_32_free(m);
    }

  free(a);
  free(b);
  
  (void) fprintf(stdout, "%.2f MOPS\n", (double) r * k / (double) t);

  return EXIT_SUCCESS;
}
