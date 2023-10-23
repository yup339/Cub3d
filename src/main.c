/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:38 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/23 15:10:35 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_game(t_game *game, bool exiting, bool is_mlx_started)
{
	if (game->map)
		free_double_array((void **)game->map);
	if (game->load_info.ea_path)
		free(game->load_info.ea_path);
	if (game->load_info.we_path)
		free(game->load_info.we_path);
	if (game->load_info.so_path)
		free(game->load_info.so_path);
	if (game->load_info.no_path)
		free(game->load_info.no_path);
	if (game->load_info.sky_str)
		free(game->load_info.sky_str);
	if (game->load_info.floor_str)
		free(game->load_info.floor_str);
	if (is_mlx_started)
		mlx_terminate(game->mlx);
	if (exiting)
		exit(EXIT_SUCCESS);
}

void	color_error(t_game *game, char **ptr, char *msg)
{
	write_error(msg);
	free_double_array((void **)ptr);
	free_game(game, true, false);
}

u_int32_t	load_color(t_game *game, char *str)
{
	int			i;
	int			color[3];
	char		**color_str;

	color_str = ft_split(str, ',');
	if (!color_str)
	{
		perror ("malloc");
		free_game(game, true, false);
	}
	i = 0;
	if (count_char(str, ',') != 2)
		color_error(game, color_str, "background colors need 3 components");
	while (color_str[i])
	{
		if (!is_str_int(color_str[i]))
			color_error(game, color_str, "color arg not right");
		color[i] = ft_atoi(color_str[i]);
		if ((color[i] > 255 || color[i] < 0))
			color_error(game, color_str, "rgb value need to be between 0-255");
		i++;
	}
	free_double_array((void **)color_str);
	return (rgba(color[0], color[1], color[2], 255));
}

void	init_map(t_game *game, char *path)
{
	load_map(game, path);
	if (!game->load_info.floor_str || !game->load_info.sky_str
		|| !game->load_info.we_path || !game->load_info.ea_path
		|| !game->load_info.no_path || !game->load_info.so_path)
	{
		write_error("missing identifier before start of map");
		free_game(game, true, false);
	}
	game->load_info.f_c = load_color(game, game->load_info.floor_str);
	game->load_info.s_c = load_color(game, game->load_info.sky_str);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc != 2)
		return (write_error("wrong number of argument"));
	init_map(&game, argv[1]);
	init_game(&game);
	load_texture(&game);
	flood_fill(&game);
	run_game(&game);
}
