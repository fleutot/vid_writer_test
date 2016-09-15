# Template for programs  ----------------------------------------------------
CC = g++
CFLAGS = -Wall -Wextra -Werror -I/usr/include/opencv -lopencv_highgui -lopencv_core
TARGETS = test_no_thread

all: $(TARGETS)

$(TARGETS): % : %.o
	$(CC) $^ -o $@ $(CFLAGS)

.cpp.o:
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	$(RM) *.o $(TARGETS)
