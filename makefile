THIS_FILE := $(lastword $(MAKEFILE_LIST))

clone-all:
	@[ -d ./thirdparty ] || mkdir ./thirdparty
	@./tool/cloneProject.sh regulator
	@./tool/cloneProject.sh token-parser

test: 
	@echo $@
	./test/index.sh

.PHONY: test
