/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:02:21 by moel-fat          #+#    #+#             */
/*   Updated: 2024/03/25 19:40:48 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_heredoc(t_data *data, char **av)
{
	char	*line;

	if (ft_strcmp(av[1], "here_doc") != 0)
		return (1);
	data->hd_filename = ft_itoa((int)check_heredoc);
	data->hd_filename = ft_strjoin_nofree("/tmp/.", data->hd_filename);
	data->heredoc_fd = open(data->hd_filename, O_CREAT | O_RDWR, 0777);
	if (data->heredoc_fd == -1)
		(perror("Error"), exit(1));
	while (1)
	{
		write(1, "here>", 5);
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0
			&& (ft_strlen(line) - 1) == ft_strlen(av[2]))
			break ;
		ft_putstr_fd(line, data->heredoc_fd);
		free(line);
	}
	close(data->heredoc_fd);
	if (line != NULL)
		(free(line), line = NULL);
	return (0);
}

void	heredoc_assign(t_data *data, char **av, int ac)
{
	data->fd_i = open(data->hd_filename, O_CREAT | O_RDWR, 0777);
	if (data->fd_i == -1)
		perror("Error");
	data->fd_o = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0777);
	if (data->fd_o == -1)
		(perror("Error"), exit(1));
	data->i = 3;
	data->hd_flag = 1;
}

void	no_heredoc_assign(t_data *data, char **av, int ac)
{
	data->fd_i = open(av[1], O_RDONLY);
	if (data->fd_i == -1)
		perror("Error");
	data->fd_o = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->fd_o == -1)
		(perror("Error"), exit(1));
	data->i = 2;
	data->hd_flag = 0;
}
