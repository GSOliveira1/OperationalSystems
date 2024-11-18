CC = gcc
CFLAGS = -Wall -g -pthread
OBJDIR = obj
SRCDIR = src
BINDIR = bin

TARGET = $(BINDIR)/race_program

SRCS = $(SRCDIR)/main.c $(SRCDIR)/race.c
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

run: all
	./$(TARGET)
