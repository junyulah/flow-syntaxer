THIS_FILE := $(lastword $(MAKEFILE_LIST))

test: 
	@echo $@
	./test/index.sh

.PHONY: test
