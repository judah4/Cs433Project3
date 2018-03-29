###################################
# OS COURSE - 2018
# 
###################################
CC = gcc 	# use g++ for compiling c++ code or gcc for c code
CFLAGS = -std=c++11 -g # compilation flags: -g for debugging. Change to -O or -O2 for optimized code.
LIB = -lm			# linked libraries	
LDFLAGS = -L.			# link flags
PROG = project3			# target executable (output)
HDRS = random.h Event.h FcfsSched.h Process.h Scheduler.h SjfSched.h
SRC = random.cpp Event.cpp FcfsSched.cpp Process.cpp Scheduler.cpp SjfSched.cpp main.cpp # .c or .cpp source files.
OBJ = $(SRC:.cpp=.o) 	# object files for the target. Add more to this and next lines if there are more than one source files.

all : $(PROG)

$(PROG): $(OBJ) 
	$(CC) -o $(PROG) $(OBJ) $(LDFLAGS) $(LIB)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

# cleanup
clean:
	/bin/rm -f *.o $(PROG)

# DO NOT DELETE
