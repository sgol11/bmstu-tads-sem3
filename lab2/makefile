CC = gcc
INC = ./inc/
OUT = ./out/
SRC = ./src/
UNIT = ./unit_tests/
CMP = ./cmp/

OBJS = $(OUT)filter.o $(OUT)input.o $(OUT)output.o $(OUT)sort.o
OBJS_UNIT = $(OUT)check_fill_array.o $(OUT)check_filter.o \
$(OUT)check_number_of_elements.o $(OUT)check_sort.o $(OUT)check_output.o 

ALL_APP_INCS = $(INC)main.h $(INC)filter.h $(INC)input.h $(INC)output.h $(INC)sort.h
ALL_UNIT_INCS = $(INC)check_main.h $(INC)check_fill_array.h $(INC)check_filter.h \
$(INC)check_number_of_elements.h $(INC)check_sort.h

CFLAGS = -std=c99 -Wall -Werror -Wvla -pedantic

.PHONY : clean debug release

release : CFLAGS += -DNDEBUG -g0
release : app.exe

debug : CFLAGS += -g3
debug : app.exe

unit : unit_tests.exe
	./unit_tests.exe

func :
	cd func_tests && ./run_tests.bat 

time : measure_time.exe
	./measure_time.exe

clean :
	$(RM) $(OUT)*.o *.exe

app.exe: $(OUT)main.o $(OBJS)
	$(CC) -o $@ $^
unit_tests.exe: $(OUT)check_main.o $(OBJS) $(OBJS_UNIT) 
	$(CC) -o $@ $^ -lcheck
measure_time.exe : $(OUT)cmp_main.o $(OUT)sort.o
	$(CC) -o $@ $^

# app

$(OUT)main.o: $(SRC)main.c $(ALL_APP_INCS)
	cd out && $(CC) $(CFLAGS) -c ../$<

$(OUT)filter.o: $(SRC)filter.c $(INC)filter.h $(INC)main.h
	cd out && $(CC) $(CFLAGS) -c ../$<

$(OUT)input.o: $(SRC)input.c $(INC)input.h $(INC)main.h 
	cd out && $(CC) $(CFLAGS) -c ../$<

$(OUT)output.o: $(SRC)output.c $(INC)output.h $(INC)main.h
	cd out && $(CC) $(CFLAGS) -c ../$<

$(OUT)sort.o: $(SRC)sort.c $(INC)sort.h $(INC)main.h
	cd out && $(CC) $(CFLAGS) -c ../$<

# unit tests

$(OUT)check_main.o: $(UNIT)check_main.c $(ALL_UNIT_INCS)
	cd out && $(CC) $(CFLAGS) -c ../$<

$(OUT)check_fill_array.o: $(UNIT)check_fill_array.c $(INC)check_fill_array.h $(INC)check_main.h
	cd out && $(CC) $(CFLAGS) -c ../$<

$(OUT)check_filter.o: $(UNIT)check_filter.c $(INC)check_filter.h $(INC)check_main.h
	cd out && $(CC) $(CFLAGS) -c ../$< 

$(OUT)check_number_of_elements.o: $(UNIT)check_number_of_elements.c $(INC)check_number_of_elements.h $(INC)check_main.h
	cd out && $(CC) $(CFLAGS) -c ../$<

$(OUT)check_sort.o: $(UNIT)check_sort.c $(INC)check_sort.h $(INC)check_main.h
	cd out && $(CC) $(CFLAGS) -c ../$<

$(OUT)check_output.o: $(UNIT)check_output.c $(INC)check_output.h $(INC)check_main.h
	cd out && $(CC) $(CFLAGS) -c ../$<

# measurement of sorting time

$(OUT)cmp_main.o: $(CMP)cmp_main.c
	cd out && $(CC) $(CFLAGS) -c ../$<