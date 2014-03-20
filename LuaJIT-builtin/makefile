SIZES           ?= 10 100 1000 10000 100000 1000000
REQUESTS        ?= 1000000
MEASUREMENTS    ?= 20
HITPROBABILITY	?= 0

.PHONY: all run clean

all:

run:
	@$(foreach i, $(SIZES), /bin/echo -n "$i: "; luajit ./benchmark.lua $i $(REQUESTS) $(MEASUREMENTS) $(HITPROBABILITY);)

clean:
	rm -rf *~
