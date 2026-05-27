/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 17:50:31 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/27 12:24:49 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	put_infos(t_game *game, char *idx, char *infos)
{
	if (ft_strncmp(idx, "NO", 2) == 0)
		game->north.path = infos;
	else if (ft_strncmp(idx, "SO", 2) == 0)
		game->south.path = infos;
	else if (ft_strncmp(idx, "WE", 2) == 0)
		game->west.path = infos;
	else if (ft_strncmp(idx, "EA", 2) == 0)
		game->east.path = infos;
	else
		free(infos);
}

void	take_infos(t_game *game, char *line, char *idx)
{
	int		i;
	int		j;
	char	infos[1000];

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
	put_infos(game, idx, ft_strdup(infos));
}

void	check_config_complete(t_game *game)
{
	if (!game->north.path || !game->south.path
		|| !game->west.path || !game->east.path)
	{
		ft_putendl_fd("Error: missing texture path", 2);
		free_game(game);
		exit(EXIT_FAILURE);
	}
	if (game->floor_color[0] == -1 || game->floor_color[1] == -1
		|| game->floor_color[2] == -1)
	{
		ft_putendl_fd("Error: missing or invalid floor color", 2);
		free_game(game);
		exit(EXIT_FAILURE);
	}
	if (game->ceil_color[0] == -1 || game->ceil_color[1] == -1
		|| game->ceil_color[2] == -1)
	{
		ft_putendl_fd("Error: missing or invalid ceiling color", 2);
		free_game(game);
		exit(EXIT_FAILURE);
	}
}
