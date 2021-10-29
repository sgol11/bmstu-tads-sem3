CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wvla -pedantic

OBJS = ./out/main.o ./out/menu.o ./out/stack_array.o ./out/stack_list.o \
       ./out/analysis.o

INCS = $(wildcard ./inc/*.h) 

app.exe: $(OBJS)
	$(CC) -o $@ $^

./out/%.o: ./src/%.c $(INCS)
	cd out && $(CC) $(CFLAGS) -I "../inc" -c ../$<

.PHONY : clean

clean :
	$(RM) ./out/*.o *.exe