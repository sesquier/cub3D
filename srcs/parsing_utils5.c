/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 16:18:29 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/29 16:18:50 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
