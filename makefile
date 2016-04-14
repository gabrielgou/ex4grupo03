# Autoversion makefile v.20160125.231301
# (C) 2015-2016, Ruben Carlo Benante <rcb@beco.cc>

#Usage:
# * From linux prompt:
#    - Normal C program (ex1.c)
#        $ make ex1.x
#    - Aspipo program (ex1.c)
#        $ make ex1.x obj=libaspipo-ux64.o
# * From vim command:
#    - Normal C program (ex1.c)
#        :make
#    - Aspipo program (ex1.c)
#        :make obj=libaspipo-ux64.o
#
# Define DEBUG:
# 	$ make ex1.x DBG=1
# 	-B force update

.PHONY: clean wipe
.PRECIOUS: %.o
SHELL=/bin/bash -o pipefail

DBG ?= 0
MAJOR = 0
MINOR = 1
BUILD = $(shell date +"%g%m%d.%H%M%S")
DEFSYM = $(subst .,_,$(BUILD))
VERSION = "\"$(MAJOR).$(MINOR).$(BUILD)\""
CC = gcc
BF = bf
PT = gpt
PL = swipl-ld
CFLAGS = -Wall -Wextra -g -O0
#-Werror
#-pedantic-errors
#-ansi
#-fPIC
CPPFLAGS = -DVERSION=$(VERSION) -DBUILD="\"$(BUILD)\"" -DDEBUG=$(DBG) 
LDLIBS = -Wl,--defsym,BUILD_$(DEFSYM)=0 -lm -lpthread -lncurses

# Programa em C (incluindo bibliotecas como allegro ou libaspipo).
# Inclui VERSION, data de BUILD e DEBUG (opcional).
%.x : %.c $(obj)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDLIBS) $^ -o $@ 2>&1 | tee errors.err

# Shared library
%.so : %.c $(obj)
	echo "Biblioteca compartilhada. Desculpe, ainda nao implementado."

# Programa BrainForce.
%.bf.x : %.bf
	$(BF) $^ -o $@ -i on -p both -r on -w on 2>&1 | tee errors.err

# Algoritmo em PORTUGOL.
%.gpt.x : %.gpt
	$(PT) $^ -o $@ 2>&1 | tee errors.err

# file.pl: regras de PROLOG que podem ser chamada por um programa em C.
%.cpl.x : %.c %.pl
	$(PL) $^ -o $@ 2>&1 | tee errors.err

# file.c: modulo C com funcoes que podem ser chamadas pelo PROLOG.
%.plc.so : %.c
	$(PL) -shared $^ -o $@ 2>&1 | tee errors.err

%.pl.x : %.pl
	echo "Binario compilado de PROLOG. Desculpe, ainda nao implementado."

# CUIDADO! Apaga tudo que o makefile pode criar.
wipe:
	rm -f *.x *.so *.o errors.err

# Apaga temporarios desnecessarios.
clean:
	rm -f *.o errors.err

