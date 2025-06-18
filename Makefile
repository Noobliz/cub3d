NAME = guard


SRCDIR = parsing
OBJDIR = obj
LIBFTDIR = libft


SRC = $(SRCDIR)/map_to_tab.c \
		$(SRCDIR)/map_to_rectangle.c \
		$(SRCDIR)/free_stuff.c \
		$(SRCDIR)/valid_chars.c
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)


CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFTDIR)

LIBFT = $(LIBFTDIR)/libft.a



all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)/$(SRCDIR)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)


$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(MAKE) clean -C $(LIBFTDIR)
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
