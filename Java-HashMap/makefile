PROG		= Benchmark.class
SIZES           ?= 10 100 1000 10000 100000 1000000 10000000 100000000
REQUESTS	?= 1000000
MEASUREMENTS	?= 100

.SUFFIXES: .java .class
.PHONY:	all run clean

.java.class:
	javac -Xlint $<

all: $(PROG)

run: $(PROG)
	@$(foreach i, $(SIZES), /bin/echo -n "$i: "; java Benchmark $i $(REQUESTS) $(MEASUREMENTS);)

clean:
	rm -rf $(PROG) *~
