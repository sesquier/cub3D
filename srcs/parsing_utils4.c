/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:39:44 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/27 12:24:49 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	alloc_map(t_game *game)
{
	int	i;

	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
	{
		ft_putendl_fd("Error: malloc failed", 2);
		free_game(game);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = malloc(sizeof(char) * (game->map.width + 1));
		if (!game->map.grid[i])
		{
			ft_putendl_fd("Error: malloc failed", 2);
			free_game(game);
			exit(EXIT_FAILURE);
		}
		ft_memset(game->map.grid[i], ' ', game->map.width);
		game->map.grid[i][game->map.width] = '\0';
		i++;
	}
	game->map.grid[game->map.height] = NULL;
}

char	**alloc_grid_copy(t_game *game)
{
	char	**grid_copy;
	int		i;

	grid_copy = malloc(sizeof(char *) * (game->map.height + 1));
	if (!grid_copy)
	{
		ft_putendl_fd("Error: malloc failed", 2);
		free_game(game);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < game->map.height)
	{
		grid_copy[i] = ft_strdup(game->map.grid[i]);
		i++;
	}
	grid_copy[game->map.height] = NULL;
	return (grid_copy);
}
