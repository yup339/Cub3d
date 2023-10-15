/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:46 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/14 20:02:01 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	check_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	path += len - 4;
	if (ft_strncmp(".cub", path, 4))
	{
		write_error("not a .cub extension");
		exit (EXIT_FAILURE);
	}
}

bool	load_map_error(char *str, char *map, bool is_reading_map, char *msg)
{
	write_error(msg);
	free(str);
	if (is_reading_map)
		free(map);
	return (false);
}

bool	is_start_map(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (!(str[i] == ' ' || str[i] == '1' || str[i] == '0'))
		{
			return (false);
		}
		i++;
	}
	return (true);
}

bool	add_texture(char *str, char **path, int skippable, t_game *game)
{
	char	*fix_path;

	if (*path)
	{
		write_error("duplicate Identifier");
		free_game(game, false);
		return (false);
	}
	fix_path = ft_calloc(1, ft_strlen(str) - skippable);
	if (!fix_path)
	{
		write_error("malloc failed");
		free_game(game, false);
		return (false);
	}
	ft_strlcpy(fix_path, str + skippable, ft_strlen(str) - skippable);
	printf("%s\n", fix_path);
	free (str);
	*path = fix_path;
	return (true);
}

bool	is_valid_info(t_game *game, char *str, char **map, bool *reading_map)
{
	if (!ft_strncmp("NO ", str, 3))
		return (add_texture(str, &game->load_info.no_path, 3, game));
	else if (!ft_strncmp("SO ", str, 3))
		return (add_texture(str, &game->load_info.so_path, 3, game));
	else if (!ft_strncmp("WE ", str, 3))
		return (add_texture(str, &game->load_info.we_path, 3, game));
	else if (!ft_strncmp("EA ", str, 3))
		return (add_texture(str, &game->load_info.ea_path, 3, game));
	else if (!ft_strncmp("F ", str, 2))
		return (add_texture(str, &game->load_info.floor_str, 2, game));
	else if (!ft_strncmp("C ", str, 2))
		return (add_texture(str, &game->load_info.sky_str, 2, game));
	else if (is_start_map(str))
	{
		*map = str;
		*reading_map = true;
		return (true);
	}
	return (false);
}

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
			if (str[0] == '\n')
				return (load_map_error(str, *map, is_reading_map, "split map"));
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

	fd = open(path, O_RDONLY);
	if (fd == -1)
		perror_exit(path);
	str = get_next_line(fd);
	if (!str)
		perror_exit(path);
	if (!load_map_info(fd, str, &map, game))
	{
		close(fd);
		exit (EXIT_FAILURE);
	}
	close(fd);
	return (map);
}

void	load_map(t_game *game, char *path)
{
	char	*map;

	check_extension(path);
	map = read_map_file(path, game);
	game->map = ft_split(map, '\n');
	free(map);
}
