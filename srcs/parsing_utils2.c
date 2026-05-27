/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:11:20 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/27 17:13:46 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	colors_infos(t_game *game, int fd, char *line, char *idx, char *num, int count)
{
	int			n;
	t_parse_error	err;

	n = ft_atoi(num);
	if (n < 0 || n > 255)
	{
		err.fd = fd;
		err.line = line;
		err.grid_copy = NULL;
		parse_error(game, "Error: RGB value out of range [0-255]", err);
	}
	if (idx[0] == 'F')
		game->floor_color[count] = n;
	else if (idx[0] == 'C')
		game->ceil_color[count] = n;
}

static int	read_num_token(char *line, int i, char *num, t_game *game, int fd)
{
	int				j;
	t_parse_error	err;

	j = 0;
	while (line[i] && ft_isdigit(line[i]) && j < 3)
		num[j++] = line[i++];
	num[j] = '\0';
	if (line[i] && line[i] != '\n' && line[i] != ',' && line[i] != ' ')
	{
		err.fd = fd;
		err.line = line;
		err.grid_copy = NULL;
		parse_error(game, "Error: invalid character in RGB value", err);
	}
	return (i);
}

void	take_numbers(t_game *game, char *line, char *idx, int fd)
{
	int			i;
	int			count;
	char		num[4];
	t_parse_error	err;

	i = 0;
	count = 0;
	while (line[i] && line[i] != '\n' && line[i] != ' ' && line[i] != idx[0])
		i++;
	if (line[i] == idx[0])
		i++;
	while (line[i] && line[i] != '\n' && count < 3)
	{
		while (line[i] == ' ' || line[i] == ',')
			i++;
		if (!line[i] || line[i] == '\n')
			break ;
		if (!ft_isdigit(line[i]))
		{
			err.fd = fd;
			err.line = line;
			err.grid_copy = NULL;
			parse_error(game, "Error: invalid character in RGB value", err);
		}
		i = read_num_token(line, i, num, game, fd);
		if (num[0])
			colors_infos(game, fd, line, idx, num, count++);
	}
}
