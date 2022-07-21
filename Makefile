export PROJNAME := users
export RESULT := users

.PHONY: all

all: $(RESULT)
	@

%: force
	@$(MAKE) -f $(STRIFE_HELPER)/Makefile $@ --no-print-directory
force: ;
