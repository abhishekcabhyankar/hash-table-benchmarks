PROG		= benchmark
CC		= gcc
CFLAGS		= -Wall -Wextra -Wpedantic -O3 -flto -std=c11 
SIZES		?= 10 100 1000 10000 100000 1000000 10000000 100000000
REQUESTS	?= 1000000
MEASUREMENTS    ?= 100

.PHONY: all run clean

all: $(PROG)

run: $(PROG)
	@$(foreach i, $(SIZES), /bin/echo -n "$i: "; ./benchmark $i $(REQUESTS) $(MEASUREMENTS);)

clean:
	rm -rf *.o *~ $(PROG)
