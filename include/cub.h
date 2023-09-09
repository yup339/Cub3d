
#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"

typedef struct s_vector{
	double	length;
	double	angle;
	double	end_x;
	double	end_y;
	double	start_x;
	double	start_y;
	double	dx;
	double	dy;
}	t_vector;

typedef struct s_collision_math{
	double	x1;
	double	x2;
	double	x3;
	double	x4;
	double	y1;
	double	y2;
	double	y3;
	double	y4;
	double	den;
	double	t;
	double	u;
}	t_collision_math;

typedef struct s_player{
	double	x;
	double	y;
	double	cam;
	int		rotation;
	int		direction;
}	t_player;

typedef struct s_textures{
	mlx_image_t	*north;
	mlx_image_t	*south;
	mlx_image_t	*west;
	mlx_image_t	*east;
	mlx_image_t	*background;
	mlx_image_t	*minimap;
	mlx_image_t	*render;
}	t_textures;

typedef struct s_game{
	t_player	player;
	t_textures	texture;
	char		**map;
	int			width;
	int			height;
	int			minimap_elsize_x;
	int			minimap_elsize_y;
	mlx_t		*mlx;
}	t_game;

enum e_map_color
{
	CLEAR = 0 ,
	WALL = (126 << 24 | 126 << 16 | 126 << 8 | 255),
	FLOOR = (168 << 24 | 254 << 16 | 171 << 8 | 255),
	PLAYER = (255 << 24 | 0 << 16 | 0 << 8 | 255),
	MAP_FOV_COLOR = (255 << 24 | 252 << 16 | 100 << 8 | 255)
};
# define MINIMAP_HEIGHT 180
# define MINIMAP_WIDTH 300
# define NBR_MINIRAY 20

enum e_direction
{
	STILL = 1 << 0,
	FORWARD = 1 << 1,
	BACKWARD = 1 << 2,
	RIGHT = 1 << 3,
	LEFT = 1 << 4,
};

# define RAY_SPEED 0.1
# define WALL_HEIGHT 250
# define HEIGHT 1000
# define WIDTH 1000
# define FOV 90
# define SPEED 0.05
# define ROTATION_SPEED 3
# define SENSITIVITY 0.05

//game core aspext
void	key_loop(mlx_key_data_t keydata, void *ptr);
void	game_loop(void *ptr);
void	init_game(t_game *game);
void	free_game(t_game *game);

//minimap
void	draw_minimap(t_game	*game);
void	draw_x_vector(t_game *game, t_vector vector, int x, int y);
void	draw_y_vector(t_game *game, t_vector vector, int x, int y);

//player movement
void	change_rotation(t_game *game);
void	move_player(t_game *game);
bool	vector_collision(t_game *game, t_vector *vector, double x, double y);
bool	vector_hits_wall(double x, double y, double map_x, double map_y);

//utility function
double	angle_to_rad(double angle);

//raycasting
void	raycast(t_game *game);

#endif
