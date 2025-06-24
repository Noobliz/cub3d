
NAME = guardian

# Dossiers
SRCDIR = parsing
OBJDIR = obj
LIBFTDIR = libft


SRC = $(SRCDIR)/get_infile/infile_to_tab.c \
      $(SRCDIR)/map_to_rectangle.c \
      $(SRCDIR)/utils/free_stuff.c \
      main_test.c \
      $(SRCDIR)/utils/map_utils.c \
	  $(SRCDIR)/extract_map.c \
      $(SRCDIR)/valid_chars.c \
      $(SRCDIR)/get_params/extract_params.c \
	  $(SRCDIR)/check_params/check_colors.c \
	  $(SRCDIR)/get_params/params_utils.c

# Objets : transforme chaque .c en obj/chemin/vers/fichier.o
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)


CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFTDIR)


LIBFT = $(LIBFTDIR)/libft.a


all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

# Compilation des .o avec création auto des dossiers
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
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
