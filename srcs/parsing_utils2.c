/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:11:20 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/27 19:57:26 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rgb_error(t_rgb_ctx rgb, char *msg)
{
	parse_error(rgb.game, msg, rgb.err);
}

static int	skip_rgb_prefix(char *line, char *idx)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n' && line[i] != ' ' && line[i] != idx[0])
		i++;
	if (line[i] == idx[0])
		i++;
	return (i);
}

static void	rgb_init(t_rgb_ctx *rgb, t_game *game, t_parse_error err, char *idx)
{
	rgb->game = game;
	rgb->err = err;
	rgb->idx = idx;
	rgb->count = 0;
}

static int	read_num_token(char *line, int i, char *num, t_rgb_ctx rgb)
{
	int				j;

	j = 0;
	while (line[i] && ft_isdigit(line[i]) && j < 3)
		num[j++] = line[i++];
	num[j] = '\0';
	if (line[i] && line[i] != '\n' && line[i] != ',' && line[i] != ' ')
		rgb_error(rgb, "Error: invalid character in RGB value");
	return (i);
}

void	take_numbers(t_game *game, char *line, char *idx, int fd)
{
	int				i;
	char			num[4];
	t_rgb_ctx		rgb;
	t_parse_error	err;

	err.fd = fd;
	err.line = line;
	err.grid_copy = NULL;
	rgb_init(&rgb, game, err, idx);
	i = skip_rgb_prefix(line, idx);
	while (line[i] && line[i] != '\n' && rgb.count < 3)
	{
		while (line[i] == ' ' || line[i] == ',')
			i++;
		if (!line[i] || line[i] == '\n')
			break ;
		if (!ft_isdigit(line[i]))
			rgb_error(rgb, "Error: invalid character in RGB value");
		i = read_num_token(line, i, num, rgb);
		if (num[0])
		{
			colors_infos(num, rgb);
			rgb.count++;
		}
	}
}
