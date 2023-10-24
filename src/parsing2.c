/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:51:41 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/24 13:55:26 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	read_line_info(t_game *game, char *str, char **map, bool *reading_map)
{
	char	*str2;

	str2 = remove_white_space(str);
	if (!str2)
	{
		free(str);
		return (true);
	}
	if (*str2 == '\n')
	{
		free(str);
		free(str2);
		return (true);
	}
	if (!is_valid_info(game, str2, map, str))
	{
		free(str2);
		free(str);
		return (false);
	}
	if (!*map)
		free(str);
	else
		*reading_map = true;
	return (true);
}

bool	load_map_info(int fd, char *str, char **map, t_game *game)
{
	bool	is_reading_map;

	is_reading_map = false;
	while (str)
	{
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
	}
	return (true);
}

char	*read_map_file(char *path, t_game *game)
{
	int		fd;
	char	*str;
	char	*map;

	map = NULL;
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

bool	is_char_ok(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != ' ' && str[i] != '\n'
			&& str[i] != 'N' && str[i] != 'W' && str[i] != 'E' && str[i] != 'S')
			return (false);
		i++;
	}
	return (true);
}

void	load_map(t_game *game, char *path)
{
	char	*map;

	check_extension(path);
	map = read_map_file(path, game);
	if (!map)
	{
		write_error("malloc failed");
		free_game(game, true, false);
	}
	if (!game->load_info.floor_str || !game->load_info.sky_str
		|| !game->load_info.we_path || !game->load_info.ea_path
		|| !game->load_info.no_path || !game->load_info.so_path)
	{
		write_error("missing identifier before start of map");
		free_game(game, true, false);
	}
	if (!is_char_ok(map))
	{
		write_error("wrong char in map");
		free_game(game, true, false);
	}
	game->map = ft_split(map, '\n');
	free(map);
}
