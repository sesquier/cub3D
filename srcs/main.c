/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:26:40 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/29 17:30:46 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	init_game(&game);
	parse(&game, ac, av);
	init_mlx(&game);
	init_tex(&game);
	init_player_vectors(&game);
	mlx_hook(game.win_ptr, 2, KeyPressMask, (int (*)())handle_keypress, &game);
	mlx_hook(game.win_ptr, 3, KeyReleaseMask,
		(int (*)())handle_keyrelease, &game);
	mlx_hook(game.win_ptr, 17, StructureNotifyMask,
		(int (*)())handle_close, &game);
	mlx_loop_hook(game.mlx_ptr, (int (*)())render, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
