/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:11:20 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/27 12:24:49 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	colors_infos(t_game *game, char *idx, char *num, int count)
{
	int	n;

	n = ft_atoi(num);
	if (n < 0 || n > 255)
	{
		ft_putendl_fd("Error: RGB value out of range [0-255]", 2);
		free_game(game);
		exit(EXIT_FAILURE);
	}
	if (idx[0] == 'F')
		game->floor_color[count] = n;
	else if (idx[0] == 'C')
		game->ceil_color[count] = n;
}

static int	read_num_token(char *line, int i, char *num, t_game *game)
{
	int	j;

	j = 0;
	while (line[i] && ft_isdigit(line[i]) && j < 3)
		num[j++] = line[i++];
	num[j] = '\0';
	if (line[i] && line[i] != '\n' && line[i] != ',' && line[i] != ' ')
	{
		ft_putendl_fd("Error: invalid character in RGB value", 2);
		free_game(game);
		exit(EXIT_FAILURE);
	}
	return (i);
}

void	take_numbers(t_game *game, char *line, char *idx)
{
	int		i;
	int		count;
	char	num[4];

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
			ft_putendl_fd("Error: invalid character in RGB value", 2);
			free_game(game);
			exit(EXIT_FAILURE);
		}
		i = read_num_token(line, i, num, game);
		if (num[0])
			colors_infos(game, idx, num, count++);
	}
}

void	check_player(t_game *game)
{
	if (game->player.dir == 0)
	{
		ft_putendl_fd("Error: no player found in map", 2);
		free_game(game);
		exit(EXIT_FAILURE);
	}
}
