NAME = write_memory

OBJ = write_memory.o
SDIR = src

CC = gcc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(addprefix $(SDIR)/, $(OBJ))
	@$(CC) $(FLAGS) $(addprefix $(SDIR)/, $(OBJ)) -o $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@/bin/rm -f $(addprefix $(SDIR)/, $(OBJ))

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
