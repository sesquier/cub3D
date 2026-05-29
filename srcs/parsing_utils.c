/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 17:50:31 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/29 16:17:45 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**get_texture_slot(t_game *game, char *idx)
{
	if (ft_strncmp(idx, "NO", 2) == 0)
		return (&game->north.path);
	if (ft_strncmp(idx, "SO", 2) == 0)
		return (&game->south.path);
	if (ft_strncmp(idx, "WE", 2) == 0)
		return (&game->west.path);
	if (ft_strncmp(idx, "EA", 2) == 0)
		return (&game->east.path);
	return (NULL);
}

void	put_infos(t_game *game, char *idx, char *infos, t_parse_error err)
{
	char		**slot;

	slot = get_texture_slot(game, idx);
	if (!slot)
	{
		free(infos);
		return ;
	}
	if (*slot)
	{
		free(infos);
		parse_error(game, "Error: duplicate texture path", err);
	}
	*slot = infos;
}

void	take_infos(t_game *game, char *line, char *idx, int fd)
{
	int				i;
	int				j;
	char			infos[1000];
	char			*dup;
	t_parse_error	err;

	i = 0;
	j = 0;
	while (line[i] && (line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
		i++;
	i += ft_strlen(idx);
	while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
		i++;
	while (line[i] && !ft_iswhitespace(line[i]))
		infos[j++] = line[i++];
	infos[j] = '\0';
	err.fd = fd;
	err.line = line;
	err.grid_copy = NULL;
	dup = ft_strdup(infos);
	if (!dup)
	{
		parse_error(game, "Error: malloc failed", err);
	}
	put_infos(game, idx, dup, err);
}

void	file_name_checker(char *file, t_game *game)
{
	int	i;
	int	dot_count;
	int	dot_pos;

	i = 0;
	dot_count = 0;
	dot_pos = -1;
	while (file[i])
	{
		if (file[i] == '.')
		{
			dot_count++;
			dot_pos = i;
		}
		i++;
	}
	if (dot_count != 1 || ft_strncmp(&file[dot_pos], ".cub", 4) != 0
		|| file[dot_pos + 4] != '\0')
	{
		ft_putendl_fd("Error: usage is <config_file.cub>", 2);
		free_game(game);
		exit(EXIT_FAILURE);
	}
}

bool	is_map_line(char *line)
{
	int	i;
	int	has_content;

	i = 0;
	has_content = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr("01NSEW ", line[i]))
			return (false);
		if (ft_strchr("01NSEW", line[i]))
			has_content = 1;
		i++;
	}
	return (has_content == 1);
}
