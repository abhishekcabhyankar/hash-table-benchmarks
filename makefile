LANG	= C++-unordered_map C++-google_dense_hash C-dtype C-khash Java-Colt Java-HashMap Java-Trove LuaJIT-builtin
CLEAN 	= $(LANG:%=clean-%)
RUN	= $(LANG:%=run-%)

SIZES		?= 10 100 1000 10000 100000 1000000 100000000
REQUESTS	?= 1000000
MEASUREMENTS	?= 100

export SIZES REQUESTS MEASUREMENTS

.PHONY: all run clean $(LANG) $(RUN) $(CLEAN)

all: $(LANG)

run: all $(RUN)

clean: $(CLEAN)

$(LANG):
	@$(MAKE) -s --no-print-directory -C $@

$(RUN):
	@echo "[$(@:run-%=%)]"
	@$(MAKE) -s --no-print-directory -C $(@:run-%=%) run

$(CLEAN):
	@$(MAKE) -s --no-print-directory -C $(@:clean-%=%) clean


