SRCS=$(wildcard *c)
EXES:=$(patsubst %.c,%,$(SRCS))
CC:=gcc
all:$(EXES)
%:%.c
	$(CC) $^ -o $@ -g -pthread
# debug:$(EXES)
# %:%.c
# 	$(CC) $^ -o $@ -g -O0	
.PHONY: clean
clean:
	$(RM) $(EXES)	
