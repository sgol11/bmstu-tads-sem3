CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wvla -pedantic

OBJS = ./out/main.o ./out/analysis.o ./out/change_cars_num.o ./out/find.o ./out/get_vars.o \
       ./out/io_file.o ./out/menu.o ./out/sort.o

INCS = $(wildcard ./inc/*.h) 

app.exe: $(OBJS)
	$(CC) -o $@ $^

./out/%.o: ./src/%.c $(INCS)
	cd out && $(CC) $(CFLAGS) -I "../inc" -c ../$<

.PHONY : clean

clean :
	$(RM) ./out/*.o *.exe