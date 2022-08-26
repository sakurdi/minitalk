SRC = client.c server.c 
OBJ := $(SRC:.c=.o)
CLIENT_NAME = client
SERVER_NAME = server
CC = gcc
PRINTF_DIR = ft_printf/
PRINTF_LIB = $(addprefix $(PRINTF_DIR), libftprintf.a)
CFLAGS = -Wall -Werror -Wextra

all: printf client server
$(NAME): all
bonus: printf client server
server: server.o 
	$(CC) $(CFLAGS) -o $@ $< $(PRINTF_LIB)
client: client.o 
	$(CC) $(CFLAGS) -o $@ $< $(PRINTF_LIB)
%.o: %.c
		$(CC) $(CFLAGS) -c $^ -o $@
printf:
	make -C $(PRINTF_DIR)
clean:
	rm -f $(OBJ)
	make -C $(PRINTF_DIR) clean
fclean: clean
	rm -f $(CLIENT_NAME) $(SERVER_NAME)
	make -C $(PRINTF_DIR) fclean
re: fclean all
