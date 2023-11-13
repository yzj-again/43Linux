SRCS:=$(wildcard *.c)
OUT:=main
#OBJS:=main.o add.o sub.o
OBJS:=$(patsubst %.c,%.o,$(SRCS))
CC:=gcc
.PHONY: clean
.PHONY: rebuild
.PHONY: all
$(OUT):$(OBJS)
	$(CC) $^ -o $@
%.o:%.c
	$(CC) -c $^ -o $@
clean:
	$(RM)  $(OUT) $(OBJS)
rebuild:clean	main
all:
	echo $(OBJS)