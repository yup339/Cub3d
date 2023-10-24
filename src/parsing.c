/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:46 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/24 14:10:55 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


/* checker to see if its a .cub extension*/
void	check_extension(char *path)
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

/* error handler when we are loading the map*/
bool	load_map_error(char *str, char *map, bool is_reading_map, char *msg)
{
	write_error(msg);
	if (str)
		free(str);
	if (is_reading_map)
		free(map);
	return (false);
}

/* checks if we are starting now starting the map we still checks for the player
	just so we get the right error messages even thought there shouldn't
	be a player on the first line*/
bool	is_start_map(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (!(str[i] == ' ' || str[i] == '1' || str[i] == '0'
				|| str[i] != 'N' || str[i] != 'W'
				|| str[i] != 'E' || str[i] != 'S'))
		{
			return (false);
		}
		i++;
	}
	return (true);
}

/* function to add the path into the main struct to load a texture or a color
use the skippables to skip the ID ex: NO or C*/
bool	add_texture(char *str, char **path, int skippable)
{
	char	*fix_path;

	if (*path)
	{
		write_error("duplicate Identifier");
		return (false);
	}
	fix_path = ft_calloc(1, ft_strlen(str) - skippable);
	if (!fix_path)
	{
		write_error("malloc failed");
		return (false);
	}
	ft_strlcpy(fix_path, str + skippable, ft_strlen(str) - skippable);
	free (str);
	*path = fix_path;
	return (true);
}


/* checks if an identifier is a valid one or not if its not it then checks
	if its the start of the map if it is it starts the map with the line*/
bool	is_valid_info(t_game *game, char *str, char **map, char *str2)
{
	if (!ft_strncmp("NO", str, 2))
		return (add_texture(str, &game->load_info.no_path, 2));
	else if (!ft_strncmp("SO", str, 2))
		return (add_texture(str, &game->load_info.so_path, 2));
	else if (!ft_strncmp("WE", str, 2))
		return (add_texture(str, &game->load_info.we_path, 2));
	else if (!ft_strncmp("EA", str, 2))
		return (add_texture(str, &game->load_info.ea_path, 2));
	else if (!ft_strncmp("F", str, 1))
		return (add_texture(str, &game->load_info.floor_str, 1));
	else if (!ft_strncmp("C", str, 1))
		return (add_texture(str, &game->load_info.sky_str, 1));
	else if (is_start_map(str))
	{
		free(str);
		*map = str2;
		return (true);
	}
	write_error("Invalid Identifier");
	return (false);
}
