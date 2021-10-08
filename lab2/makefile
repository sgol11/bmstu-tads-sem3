CC = gcc

INC = ./inc/
OUT = ./out/
SRC = ./src/

PROG_INC = -I "../inc"

OBJS = $(OUT)analysis.o $(OUT)change_cars_num.o $(OUT)find.o $(OUT)get_vars.o $(OUT)io_file.o \
       $(OUT)menu.o $(OUT)sort.o

ALL_APP_INCS = $(INC)general.h $(INC)menu.h $(INC)structs.h $(INC)io_file.h $(INC)change_cars_num.h \
               $(INC)find.h $(INC)sort.h $(INC)analysis.h $(INC)get_vars.h

INC_FLAGS := $(addprefix -I, $(INC))

CFLAGS = -std=c99 -Wall -Werror -Wvla -pedantic

app.exe: $(OUT)main.o $(OBJS)
	$(CC) -o $@ $^

$(OUT)%.o: $(SRC)%.c $(ALL_APP_INCS)
	cd out && $(CC) $(CFLAGS) $(PROG_INC) -c ../$<

.PHONY : clean

clean :
	$(RM) $(OUT)*.o *.exe