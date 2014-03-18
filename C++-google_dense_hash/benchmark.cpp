#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include <vector>
#include <sparsehash/dense_hash_map>

typedef unsigned long utime_t;

utime_t utime()
{
  struct timeval tv;

  (void) gettimeofday(&tv, NULL);
  return (utime_t) tv.tv_sec * 1000000 + (utime_t) tv.tv_usec;
}

utime_t lookup(google::dense_hash_map<uint32_t, uint32_t> &m, uint32_t *b, int r)
{
  google::dense_hash_map<uint32_t, uint32_t>::const_iterator position;
  utime_t t1, t2;
  int i;
  uint64_t sum;
  
  sum = 0;
 
  t1 = utime();
  for (i = 0; i < r; i ++)
    {
      position = m.find(b[i]);
      if (position != m.end())
	sum += position->second;
    }
  t2 = utime();

  return t2 - t1;
}

void randomize_input(uint32_t *a, int n, uint32_t *b, int r)
{
  int i;

  for (i = 0; i < n; i ++)
    a[i] = rand() % (UINT32_MAX - 1) ;
  for (i = 0; i < r; i ++)
    b[i] = i % 2 ? a[rand() % n] : rand() % (UINT32_MAX - 1);
}

void usage()
{
  extern char *__progname;

  fprintf(stderr, "usage: %s <size> <requests> <measurements>\n", __progname);
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
  int n, r, k, i, j;
  uint32_t *a, *b;
  google::dense_hash_map<uint32_t, uint32_t> m;
  utime_t t;

  if (argc != 4)
    usage();
  
  n = strtol(argv[1], NULL, 0);
  r = strtol(argv[2], NULL, 0);
  k = strtol(argv[3], NULL, 0);
  t = 0;

  a = (uint32_t *) malloc(n * sizeof *a);
  b = (uint32_t *) malloc(r * sizeof *b);

  m.set_empty_key(UINT32_MAX);
  m.max_load_factor(0.5);
  for (j = 0; j < k; j ++)
    {
      randomize_input(a, n, b, r);
      for (i = 0; i < n; i ++)
	m.insert(std::make_pair(a[i], i));
      
      t += lookup(m, b, r);
      m.clear();
    }

  (void) fprintf(stdout, "%.2f MOPS\n", (double) r * k/ (double) t);

  free(a);
  free(b);
  
  return EXIT_SUCCESS;
}
