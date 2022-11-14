NAME= containers

CFLAGS= -Wall -Wextra -Werror -std=c++98
CC= c++

SRCS= srcs/main.cpp
OBJS= $(SRCS:.cpp=.o)

all: $(NAME)

%.o:%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

run: re 
	./containers

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re