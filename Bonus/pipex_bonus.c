/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:28:48 by moel-fat          #+#    #+#             */
/*   Updated: 2024/03/23 17:43:00 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac < 5)
		ft_error(1);
	if (check_heredoc(&data, av) == 0)
		heredoc_assign(&data, av, ac);
	else
		no_heredoc_assign(&data, av, ac);
	data.old_fd = dup(STDIN_FILENO);
	if (dup2(data.fd_i, 0) == -1)
		(perror("Error"), exit(1));
	if (close(data.fd_i) == -1)
		(perror("Error"), exit(1));
	while (data.i < ac - 2)
	{
		execut_cmd(av[data.i], &data, env);
		data.i++;
	}
	if (dup2(data.fd_o, 1) == -1)
		(perror("Error"), exit(1));
	close(data.fd_o);
	if (data.hd_flag == 1 && unlink(data.hd_filename) == -1)
		(perror("Error"), exit(1));
	exv_lastcmd(&data, av, ac, env);
	exit(0);
}
