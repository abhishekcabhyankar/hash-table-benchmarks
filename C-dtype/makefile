PROG		= benchmark
CC		= gcc
CFLAGS		= -Wall -Wextra -Wpedantic -O3 -flto -std=c11
LDLIBS		= -ldtype
SIZES		?= 10 100 1000 10000 100000 1000000 10000000 100000000
REQUESTS	?= 1000000
MEASUREMENTS	?= 10
HITPROBABILITY	?= 0.5

.PHONY: all run clean

all: $(PROG)

run: $(PROG)
	@$(foreach i, $(SIZES), /bin/echo -n "$i: "; ./benchmark $i $(REQUESTS) $(MEASUREMENTS) $(HITPROBABILITY);)

clean:
	rm -rf *.o *~ $(PROG)
