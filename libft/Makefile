NAME = libft.a

SRCS = ft_isalpha.c \
		  ft_isdigit.c \
		  ft_isalnum.c \
		  ft_isascii.c \
		  ft_isprint.c \
		  ft_strlen.c \
		  ft_memset.c \
		  ft_bzero.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_strlcpy.c \
		  ft_strncmp.c \
		  ft_strlcat.c \
		  ft_toupper.c \
		  ft_tolower.c \
		  ft_strchr.c \
		  ft_strrchr.c \
		  ft_strncmp.c \
          ft_strcmp.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_strnstr.c \
		  ft_atoi.c \
		  ft_calloc.c \
		  ft_strdup.c \
		  ft_substr.c \
		  ft_strjoin.c \
		  ft_strtrim.c \
		  ft_split.c \
		  ft_itoa.c \
		  ft_strmapi.c \
		  ft_striteri.c \
		  ft_putchar_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  get_next_line.c \
		  get_next_line_utils.c \
		  get_next_line_bonus.c \
		  get_next_line_utils_bonus.c \
		  ft_printf.c \
		  ft_print_char.c \
		  ft_print_ptr.c \
		  ft_print_s.c \
		  ft_print_nbr.c \
		  ft_print_unsig.c \
		  ft_print_hex.c \

BONUS_SRCS = ft_lstnew_bonus.c \
			   ft_lstadd_front_bonus.c \
			   ft_lstsize_bonus.c \
			   ft_lstlast_bonus.c \
			   ft_lstadd_back_bonus.c \
			   ft_lstdelone_bonus.c \
			   ft_lstclear_bonus.c \
			   ft_lstiter_bonus.c \
			   ft_lstmap_bonus.c \

OBJECTS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

INCLUDES = libft.h

all: $(NAME)

$(NAME): $(OBJECTS) $(INCLUDES)
	ar rcs $(NAME) $(OBJECTS)

%.o : %.c
	cc $(CFLAGS) -c $< -o $@


bonus: .bonus

.bonus: $(NAME) $(BONUS_OBJS) $(INCLUDES)
	ar rcs $(NAME) $(BONUS_OBJS)
	@touch .bonus

clean:
	rm -f $(OBJECTS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f .bonus

re: fclean all

.PHONY: all clean fclean re bonus
