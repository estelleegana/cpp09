#nom de l'executable
NAME = RPN

#compilateur
CC = c++

#flags
FLAGS = -Wall -Wextra -Werror -std=c++98 -g3

#fichiers sources
SRCS = RPN.cpp \
	main.cpp \

#creation d'objets a partir des fichiers sources
OBJS = $(SRCS:.cpp=.o)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

#compilations
all: $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all