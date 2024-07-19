NAME = fdf
NAME_BONUS = fdf_bonus

HEADER = includes/fdf.h
HEADER_BONUS = includes/fdf_bonus.h
SRC = mandatory/main.c 	mandatory/libft.c	mandatory/split.c	mandatory/get_next_line.c	\
	  mandatory/get_next_line_utils.c	mandatory/draw_points.c	mandatory/free.c	\
	  mandatory/input.c		mandatory/iso.c		mandatory/map.c	mandatory/input_utils.c	

SRCB = bonus/main_bonus.c \


CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

OBJ = $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)
MLX = "./MLX42/build/libmlx42.a"
LDFLAGS = -O3 -Iinclude -lglfw -L"/Users/hanebaro/.brew/Cellar/glfw/3.4/lib"
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LDFLAGS) $(FRAMEWORKS) -o $(NAME) 

bonus: $(OBJB) $(HEADER_BONUS)
	$(CC) $(CFLAGS) $(OBJB) $(MLX) $(LDFLAGS) $(FRAMEWORKS) -o $(NAME_BONUS) 

%.o: %.c
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJB)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all