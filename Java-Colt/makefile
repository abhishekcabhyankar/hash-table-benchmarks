PROG		= Benchmark.class
SIZES		?= 10 18 32 56 100 178 316 562 1000 1778 3162 5623 10000 17783 31623 56234 100000 177828 316228 562341 1000000 1778279 3162278 5623413 10000000 17782794 31622777 56234133 100000000
REQUESTS	?= 1000000
MEASUREMENTS	?= 10

.SUFFIXES: .java .class
.PHONY:	all run clean

.java.class:
	javac -cp /opt/colt/lib/colt.jar -Xlint $<

all: $(PROG)

run: $(PROG)
	@$(foreach i, $(SIZES), /bin/echo -n "$i: "; java -cp /opt/colt/lib/colt.jar:. Benchmark $i $(REQUESTS) $(MEASUREMENTS);)

clean:
	rm -rf $(PROG) *~
