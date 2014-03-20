LANG	= C-khash C++-google_dense_hash C++-unordered_map Java-HashMap LuaJIT-builtin
CLEAN 	= $(LANG:%=clean-%)
RUN	= $(LANG:%=run-%)

SIZES		?= 10 100 1000 10000 100000 1000000 10000000
REQUESTS	?= 1000000
MEASUREMENTS	?= 10
HITPROBABILITY	?= 0.5

export SIZES REQUESTS MEASUREMENTS HITPROBABILITY

.PHONY: all run clean $(LANG) $(RUN) $(CLEAN) benchmark%

all: $(LANG)

run: $(RUN)

clean: $(CLEAN)

$(LANG):
	@$(MAKE) -s --no-print-directory -C $@

$(RUN): $(LANG)
	@echo "[$(@:run-%=%)]"
	@$(MAKE) -s --no-print-directory -C $(@:run-%=%) run

$(CLEAN):
	@$(MAKE) -s --no-print-directory -C $(@:clean-%=%) clean

benchmark1-p%: $(LANG)
	@echo "#benchmark1 probability $(@:benchmark1-p%=%)"
	@$(foreach i, $(LANG), \
		/bin/echo -n "['$i',"; \
		HITPROBABILITY="$(@:benchmark1-p%=%)" $(MAKE) -s --no-print-directory -C $i run | awk '{printf "%f,", $$2}' | sed 's/,$$/\],/g'; \
	)

benchmark1: benchmark1-p0 benchmark1-p0.05 benchmark1-p0.5 benchmark1-p0.95 benchmark1-p1

