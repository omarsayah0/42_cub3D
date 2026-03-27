NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR		= minilibx-linux
MLX_REPO	= https://github.com/42paris/minilibx-linux.git
MLX_LIB		= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= $(MLX_LIB) -lXext -lX11 -lm

INC_DIR		= includes
SRC_DIR		= src
PARSE_DIR	= src/parsing
INIT_DIR	= src/init
RAYCAST_DIR	= src/raycasting
RENDER_DIR	= src/rendering
EVENTS_DIR	= src/events

INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

SRC			= $(SRC_DIR)/main.c \
			  $(PARSE_DIR)/cleanup_config.c \
			  $(PARSE_DIR)/parse_file.c \
			  $(PARSE_DIR)/parse_utils.c \
			  $(PARSE_DIR)/parse_textures.c \
			  $(PARSE_DIR)/parse_colors.c \
			  $(PARSE_DIR)/gnl_clean.c \
			  $(PARSE_DIR)/parse_config.c \
			  $(PARSE_DIR)/file_validation.c \
			  $(PARSE_DIR)/flood_fill.c \
			  $(PARSE_DIR)/map_builder.c \
			  $(PARSE_DIR)/map_validation.c \
			  $(PARSE_DIR)/config_validation.c \
			  $(INIT_DIR)/init_game.c \
			  $(INIT_DIR)/init_game_utils.c \
			  $(INIT_DIR)/init_player.c \
			  $(INIT_DIR)/init_mlx.c \
			  $(INIT_DIR)/init_textures.c \
			  $(INIT_DIR)/init_cleanup.c \
			  $(RAYCAST_DIR)/cast_rays.c \
			  $(RAYCAST_DIR)/ray_init.c \
			  $(RAYCAST_DIR)/ray_step.c \
			  $(RAYCAST_DIR)/dda.c \
			  $(RAYCAST_DIR)/ray_projection.c \
			  $(RENDER_DIR)/get_tex_pixel.c \
			  $(RENDER_DIR)/draw_background.c \
			  $(RENDER_DIR)/draw_wall.c \
			  $(RENDER_DIR)/render_frame.c \
			  $(EVENTS_DIR)/key_handler.c \
			  $(EVENTS_DIR)/player_move.c \
			  $(EVENTS_DIR)/player_rotate.c \
			  $(EVENTS_DIR)/events.c

SRC_BONUS	= $(SRC_DIR)/main.c \
			  $(PARSE_DIR)/cleanup_config.c \
			  $(PARSE_DIR)/parse_file.c \
			  $(PARSE_DIR)/parse_utils_bonus.c \
			  $(PARSE_DIR)/parse_textures.c \
			  $(PARSE_DIR)/parse_colors.c \
			  $(PARSE_DIR)/gnl_clean.c \
			  $(PARSE_DIR)/parse_config.c \
			  $(PARSE_DIR)/file_validation.c \
			  $(PARSE_DIR)/flood_fill.c \
			  $(PARSE_DIR)/map_builder.c \
			  $(PARSE_DIR)/map_validation_bonus.c \
			  $(PARSE_DIR)/config_validation.c \
			  $(INIT_DIR)/init_game.c \
			  $(INIT_DIR)/init_game_utils.c \
			  $(INIT_DIR)/init_player.c \
			  $(INIT_DIR)/init_mlx.c \
			  $(INIT_DIR)/init_textures.c \
			  $(INIT_DIR)/init_textures_bonus.c \
			  $(INIT_DIR)/init_coins_bonus.c \
			  $(INIT_DIR)/init_cleanup.c \
			  $(RAYCAST_DIR)/cast_rays.c \
			  $(RAYCAST_DIR)/ray_init.c \
			  $(RAYCAST_DIR)/ray_step.c \
			  $(RAYCAST_DIR)/dda.c \
			  $(RAYCAST_DIR)/dda_bonus.c \
			  $(RAYCAST_DIR)/ray_projection.c \
			  $(RENDER_DIR)/get_tex_pixel.c \
			  $(RENDER_DIR)/draw_background.c \
			  $(RENDER_DIR)/draw_wall.c \
			  $(RENDER_DIR)/draw_wall_bonus.c \
			  $(RENDER_DIR)/draw_minimap_bonus.c \
			  $(RENDER_DIR)/render_sprites_bonus.c \
			  $(RENDER_DIR)/render_frame_bonus.c \
			  $(EVENTS_DIR)/key_handler.c \
			  $(EVENTS_DIR)/key_handler_bonus.c \
			  $(EVENTS_DIR)/player_move_bonus.c \
			  $(EVENTS_DIR)/player_rotate.c \
			  $(EVENTS_DIR)/doors_bonus.c \
			  $(EVENTS_DIR)/update_doors_bonus.c \
			  $(EVENTS_DIR)/update_coins_bonus.c \
			  $(EVENTS_DIR)/mouse_rotate_bonus.c \
			  $(EVENTS_DIR)/events_bonus.c

OBJ			= $(SRC:.c=.o)
OBJ_BONUS	= $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

bonus: $(MLX_LIB) $(OBJ_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_DIR):
	git clone $(MLX_REPO) $(MLX_DIR)

$(MLX_LIB): $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)

%.o: %.c $(INC_DIR)/cub3d.h $(INC_DIR)/cub3d_bonus.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR) clean; fi

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re