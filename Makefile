##
## EPITECH PROJECT, 2019
## NWP_mychap_2018
## File description:
## Makefile
##

SRC		= 	src/mychap.c\
			src/createSocket.c\
			src/createMessage.c\
			src/receiveChallenge.c\
			src/receiveSecret.c\
			src/send.c\

OBJ		= $(SRC:.c=.o)

CC		= gcc

NAME	= client

CFLAGS	= -I./include -Wall -Wextra -Werror -lssl -lcrypto

LDFLAGS	= -L/usr/lib -lssl -lcrypto

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJ_SERVER)
	rm -f src/*.o 

fclean: clean
	$(RM) $(NAME_SERVER)
	rm -f client


re: fclean all

