CC = gcc
CFLAGS = -Wall -Wextra -g

# List of source files
SRCS = main.c functions.c

# List of object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = Battleship

# Default target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(EXEC)
