/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:51:41 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/23 16:23:14 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	read_line_info(t_game *game, char *str, char **map, bool *reading_map)
{
	if (*str == '\n')
	{
		free(str);
		return (true);
	}
	if (!is_valid_info(game, str, map, reading_map))
	{
		free(str);
		return (false);
	}
	return (true);
}

bool	load_map_info(int fd, char *str, char **map, t_game *game)
{
	bool	is_reading_map;

	is_reading_map = false;
	while (str)
	{
		str = remove_white_space(str, is_reading_map);
		if (!str)
			return (false);
		if (!is_reading_map)
		{
			if (!read_line_info(game, str, map, &is_reading_map))
				return (false);
		}
		else if (is_reading_map)
		{
			*map = ft_strjoin(*map, str, 1, 1);
			if (!*map)
				return (load_map_error(str, *map, is_reading_map, "malloc"));
		}
		str = get_next_line(fd);
		if (str && str[0] == '\n' && is_reading_map)
			return (load_map_error(str, *map, is_reading_map, "empty line"));
	}
	return (true);
}

char	*read_map_file(char *path, t_game *game)
{
	int		fd;
	char	*str;
	char	*map;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		perror_exit(path);
	str = get_next_line(fd);
	if (!str)
		perror_exit(path);
	if (!load_map_info(fd, str, &map, game))
	{
		close(fd);
		free_game(game, true, false);
	}
	close(fd);
	return (map);
}

void	load_map(t_game *game, char *path)
{
	char	*map;

	check_extension(path);
	map = read_map_file(path, game);
	if (get_nb_of_player(map) != 1)
	{
		free(map);
		write_error("wrong number of player");
		exit(EXIT_FAILURE);
	}
	game->map = ft_split(map, '\n');
	free(map);
}
