NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

SRCS_DIR = ./
OBJS_DIR = ./objs/
INCLUDES = -I./

SRCS = $(SRCS_DIR)ft_printf.c \
	   $(SRCS_DIR)aux/ft_hex.c \
	   $(SRCS_DIR)aux/ft_numbers.c \
	   $(SRCS_DIR)aux/ft_ptr.c \
	   $(SRCS_DIR)aux/ft_str.c

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)aux
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re