SRCS=$(wildcard *c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
CC:=gcc
server:$(OBJS)
	$(CC) $^ -o $@ -pthread -g 
%.o:%.c
	$(CC) -c $^ -o $@ -g
# debug:$(EXES)
# %:%.c
# 	$(CC) $^ -o $@ -g -O0	
.PHONY: clean
clean:
	$(RM) $(OBJS)	server
rebuild:clean server clean