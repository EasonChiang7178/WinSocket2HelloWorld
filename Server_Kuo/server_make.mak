CC = gcc
CPP = g++
CFLAGS = -Wall -ansi -O0 -lwsock32
INCPATH = -I.
LIBPATH = -L.
DEFS = -DDEBUG
LIBS = 
MAIN_FILE = server
OBJ_FILES = tcp-server.o tcp-exception.o

COMPILER = $(CPP)
PARAMETER = $(CFLAGS) $(DEFS) $(INCPATH) $(LIBPATH)


ifeq ($(OS), Windows_NT)

all: clean $(OBJ_FILES) $(MAIN_FILE).o
	$(COMPILER) $(OBJ_FILES) $(MAIN_FILE).o -o $(MAIN_FILE).exe $(PARAMETER)
%.o:
	@echo $*.o
	@if exist $*.cpp (\
		$(CPP) -c $*.cpp $(PARAMETER)\
	) else if exist $*.c (\
		$(CC) -c $*.c $(PARAMETER)\
	) else if exist $*.s (\
		$(CC) -c $*.s $(PARAMETER)\
	)
clean:
	@echo rm *.o
	@if exist *.o del *.o
exec:
	@$(MAIN_FILE).exe

else

all: clean $(OBJ_FILES) $(MAIN_FILE).o
	$(COMPILER) $(OBJ_FILES) $(MAIN_FILE).o -o $(MAIN_FILE) $(PARAMETER)
%.o:
	@echo $*.o
	@if [ -f $*.cpp ]; then\
		$(CPP) -c $*.cpp $(PARAMETER)\
	elif [ -f $*.c ]; then \
		$(CC) -c $*.c $(PARAMETER)\
	elif [ -f $*.s ]; then \
		$(CC) -c $*.s $(PARAMETER)\
	fi
clean:
	@echo rm *.o
	@if [ -f *.o ]; then rm -f *.o; fi
exec:
	@$(MAIN_FILE)

endif
