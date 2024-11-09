# Nome do Executável:
TARGET = race

#Compilador e Flags:
CC = gcc
CFLAGS = -Wall -pthread

# Arquivos-fonte e objeto
SRCS = main.c race.c
OBJS = $(SRCS:.c=.o)

# Regra para compilar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar arquivos .o a partir de .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa os arquivos de objeto e o executável
clean:
	rm -f $(OBJS) $(TARGET)

# Executa o programa
run: $(TARGET)
	./$(TARGET)