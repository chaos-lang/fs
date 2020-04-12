SHELL=/bin/bash

.ONESHELL:

UNAME_S := $(shell uname -s)

default:
	export CHAOS_COMPILER=gcc
	${MAKE} build

clang:
	export CHAOS_COMPILER=clang
	${MAKE} build

build:
ifeq ($(UNAME_S), Darwin)
	${MAKE} build-macos
else
	${MAKE} build-linux
endif

build-linux:
	${CHAOS_COMPILER} -shared -fPIC template.c -o template.so

build-macos:
	${CHAOS_COMPILER} -shared -fPIC -undefined dynamic_lookup template.c -o template.dylib

spell:
	mkdir -p spells/template
	export GLOBIGNORE='*.c'
	cp template.* spells/template/

test: spell
	./test.sh

requirements:
	git clone https://github.com/chaos-lang/chaos.git .chaos/ && \
	cd .chaos/ && \
	make requirements-dev
