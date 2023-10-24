/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:52:49 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/24 12:52:52 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"

typedef struct s_mini_vec{
	double	dx;
	double	dy;
}	t_mini_vec;

typedef struct s_line{
	int		line_height;
	int		start;
	int		end;
	uint8_t	*color;
	int		pixel;
	double	step;
	double	wallx;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	int		i;
}	t_line;

typedef struct s_wall{
	int				line_height;
	int				start;
	int				end;
	uint8_t			*color;
	int				pixel;
	double			step;
	double			wallx;
	int				tex_x;
	int				tex_y;
	double			tex_pos;
	int				i;
}	t_wall;

typedef struct s_vector{
	double	length;
	double	angle;
	double	end_x;
	double	end_y;
	double	start_x;
	double	start_y;
	double	dx;
	double	dy;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		side;
	int		step_x;
	int		step_y;
}	t_vector;

typedef struct s_player{
	double	x;
	double	y;
	double	cam;
	int		rotation;
	int		direction;
	double	dx;
	double	dy;
}	t_player;

typedef struct s_textures{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_image_t		*background;
	mlx_image_t		*render;
}	t_textures;

typedef struct s_load_info{
	char		*no_path;
	char		*so_path;
	char		*ea_path;
	char		*we_path;
	char		*floor_str;
	char		*sky_str;
	uint32_t	f_c;
	int			s_c;
}	t_load_info;

typedef struct s_game{
	t_player	player;
	t_textures	texture;
	char		**map;
	int			minimap_elsize_x;
	int			minimap_elsize_y;
	t_load_info	load_info;
	double		plane_x;
	double		plane_y;
	bool		cursor;
	mlx_t		*mlx;
}	t_game;

# define MINIMAP_HEIGHT 180
# define MINIMAP_WIDTH 300
# define NBR_MINIRAY 80

enum e_side
{
	NONE,
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING
};

enum e_direction
{
	STILL = 1 << 0,
	FORWARD = 1 << 1,
	BACKWARD = 1 << 2,
	RIGHT = 1 << 3,
	LEFT = 1 << 4,
};

# define RAY_SPEED 0.25
# define WALL_HEIGHT 0.666
# define HEIGHT 1000
# define WIDTH 1000
# define SPEED 0.05
# define ROTATION_SPEED 3
# define SENSITIVITY 0.05

//game core aspext
void		key_loop(mlx_key_data_t keydata, void *ptr);
void		game_loop(void *ptr);
void		init_game(t_game *game);
void		free_game(t_game *game, bool exiting, bool is_mlx_started);
void		load_texture(t_game *game);
void		run_game(t_game *game);

//player movement
void		change_rotation(t_game *game);
void		move_player(t_game *game);
bool		vector_hits_wall(double x, double y, double map_x, double map_y);
void		rotate_player_vector(t_game *game, double angle);

//utility function
double		angle_to_rad(double angle);
int			rgba(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a);
void		safe_free(char *str);
void		close_game(void *game);

//raycasting
void		raycast(t_game *game);
void		draw_wall(t_game *game, t_vector *v, int x, mlx_texture_t *tex);
void		render_ray(t_game *game, t_vector *v, int x);
void		raycast(t_game *game);
t_vector	create_ray(t_game *game, int i);
void		dda(t_game *game, t_vector *v);
void		calc_wall_height(t_wall	*w, t_vector *vector, mlx_texture_t *tex);

//parsing
void		load_map(t_game *game, char *path);
void		perror_exit(char *msg);
int			get_nb_of_player(char **str);
void		flood_fill(t_game *game);
void		load_map(t_game *game, char *path);
bool		load_map_error(char *str, char *map, bool is_reading_map, char *m);
bool		is_valid_info(t_game *game, char *str, char **map, bool *r);
void		check_extension(char *path);
int			count_char(char *str, char c);
char		*remove_white_space(char *str, bool flag);

#endif
