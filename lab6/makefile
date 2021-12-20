CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wvla -pedantic

OBJS = ./out/main.o ./out/menu.o ./out/io.o ./out/binary_search_tree.o \
       ./out/avl_tree.o ./out/hash_table.o ./out/measurements.o

INCS = $(wildcard ./inc/*.h) 

app.exe: $(OBJS)
	$(CC) -o $@ $^

./out/%.o: ./src/%.c $(INCS)
	cd out && $(CC) $(CFLAGS) -I "../inc" -c ../$<

.PHONY : clean

clean :
	$(RM) ./out/*.o *.exe