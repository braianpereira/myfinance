# Name of the project
PROJ_NAME=myfinance

# .c files
C_SOURCE=$(wildcard ./source/*.c)

# .h files
H_SOURCE=$(wildcard ./source/*.h)

# Object files
OBJ=$(subst .c,.o,$(subst source,objects,$(C_SOURCE)))

# Compiler and linker
CC=gcc

# Flags for compiler
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -ansi      \
         -pedantic	\
         -std=c99

# Command used at clean target
# Param used at create folder
ifeq ($(OS),Windows_NT)
   RM = del /f /q objects $(PROJ_NAME).exe
   MKDIR = if not exist objects mkdir objects
   RMDIR = if exist objects rmdir 
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        RM = rm -rf ./objects/*.o $(PROJ_NAME)
        MKDIR = mkdir -p objects
        RMDIR = rndir -rf 
    endif
endif

#
# Compilation and linking
#
all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o $@
	@ echo 'Finished building binary: $@'
	@ echo ' '

./objects/%.o: ./source/%.c ./source/%.h
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./objects/main.o: ./source/main.c $(H_SOURCE)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ $(MKDIR)

clean:
	@ $(RM)  *~
	@ $(RMDIR) objects

.PHONY: all clean