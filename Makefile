NAME 		= freq

SRCS		= main.cpp

OBJS		= $(SRCS:.cpp=.o)

CC			= g++

FLAGS		= -std=c++11 -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(SRCS) $(HEADER)
			$(CC) $(FLAGS) $(INC) $(SRCS) -o $(NAME)

%.o:		%.cpp
			$(CC) $(FLAGS) -c $< -o $@

clean:
			rm -rf $(OBJS)
			rm -rf *.txt

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re