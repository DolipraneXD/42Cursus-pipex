.PHONY: all clean fclean re

CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = pipex
B_NAME = pipex_bonus

CFILES = Mandatory/pipex.c\
		 Mandatory/Error_handle.c\
		 Mandatory/exvcmd.c

BFILES = Bonus/pipex_bonus.c\
		 Bonus/Error_handle_bonus.c\
		 Bonus/get_next_line.c\
		 Bonus/get_next_line_utils.c\
		 Bonus/exvcmd_bonus.c\
		 Bonus/heredoc_bonus.c\
		 Bonus/utils_bonus.c

OBJ = $(patsubst %.c, %.o, $(CFILES))
B_OBJ = $(patsubst %.c, %.o, $(BFILES))

all: lib $(NAME)

lib:
	@make -C libft

$(OBJ) : %.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME) : libft/libft.a $(OBJ) Mandatory/pipex.h
	@$(CC) $(FLAGS) $(OBJ) libft/libft.a -o $(NAME)
	@echo Making ... Done.

bonus: lib $(B_NAME)

$(B_OBJ) : %.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

$(B_NAME) : libft/libft.a $(B_OBJ) Bonus/pipex_bonus.h
	@$(CC) $(FLAGS) $(B_OBJ) libft/libft.a -o $(B_NAME)
	@echo Making Bonus ... Done.


clean:
	@$(RM) $(OBJ) $(B_OBJ)
	@make -C libft clean
	@echo cleaning ... Done.

fclean: clean
	@$(RM) $(NAME) $(B_NAME)
	@make -C libft fclean

re: fclean all