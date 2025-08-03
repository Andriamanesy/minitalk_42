# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: briandri <briandri@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/02 23:01:21 by briandri          #+#    #+#              #
#    Updated: 2025/08/03 09:30:55 by briandri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

CLIENT_SRC = client.c utils.c
SERVER_SRC = server.c utils.c

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

CC = cc -Wall -Wextra -Werror
MAKE = make

FT_PRINTF_SRC = printf
FT_PRINTF = $(FT_PRINTF_SRC)/libftprintf.a

COLOR_BoldCyan = \033[1;36m
COLOR_Reset = \033[0m
COLOR_Red = \033[31m

all: client server

client: $(CLIENT_OBJ) $(FT_PRINTF)
	@$(CC) -o client $(CLIENT_OBJ) $(FT_PRINTF)
	@echo "$(COLOR_BoldCyan)Client built successfully.$(COLOR_Reset)"

server: $(SERVER_OBJ) $(FT_PRINTF)
	@$(CC) -o server $(SERVER_OBJ) $(FT_PRINTF)
	@echo "$(COLOR_BoldCyan)Server built successfully.$(COLOR_Reset)"

%.o: %.c
	@$(CC) -c $< -o $@

$(FT_PRINTF):
	@$(MAKE) -C $(FT_PRINTF_SRC)

clean:
	@rm -f *.o
	@$(MAKE) -C $(FT_PRINTF_SRC) clean
	@echo "$(COLOR_Red)Object files cleaned.$(COLOR_Reset)"

fclean: clean
	@rm -f client server
	@echo "$(COLOR_Red)Executables cleaned.$(COLOR_Reset)"

re: fclean all

.PHONY: all clean fclean re client server
