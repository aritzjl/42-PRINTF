# Variables
NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

# Directorios
SRCS_DIR = ./
OBJS_DIR = ./objs/
INCLUDES = -I./

# Archivos fuente
SRCS = $(SRCS_DIR)ft_printf.c \
	   $(SRCS_DIR)aux/ft_hex.c \
	   $(SRCS_DIR)aux/ft_numbers.c \
	   $(SRCS_DIR)aux/ft_ptr.c \
	   $(SRCS_DIR)aux/ft_str.c

# Generar archivos .o a partir de los .c
OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

# Reglas
all: $(NAME)

# Crear el archivo de biblioteca estática
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

# Compilar archivos objeto
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)aux
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Limpiar archivos objeto
clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJS_DIR)

# Limpiar todo, incluyendo la librería
fclean: clean
	$(RM) $(NAME)

# Recompilar todo
re: fclean all

# Reglas adicionales
.PHONY: all clean fclean re