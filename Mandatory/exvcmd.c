/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exvcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:42:22 by moel-fat          #+#    #+#             */
/*   Updated: 2024/03/22 17:59:20 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_slash(char **cmd)
{
	if (cmd == NULL || *cmd == NULL)
		ft_error(2);
	if (ft_strchr (cmd[0], '/') != NULL)
		return (1);
	return (0);
}

int	access_exev(t_data data, char **env, char **cmd)
{
	char	*joined;

	data.i = 0;
	data.flag = 0;
	joined = NULL;
	while (data.s_path[data.i])
	{
		joined = ft_strjoin(data.s_path[data.i], "/");
		joined = ft_strjoin(joined, cmd[0]);
		if (access(joined, F_OK | X_OK) == 0)
		{
			if (execve(joined, cmd, env) == -1)
				(perror("Error"), free(joined), exit (1));
			data.flag = 1;
			free(joined);
			break ;
		}
		else
			free(joined);
		data.i++;
	}
	if (data.flag == 0)
		(ft_error(2));
	return (0);
}

int	exv_cmd(t_data data, char **env, char **cmd)
{
	if (check_slash(cmd) == 1)
	{
		if (execve(cmd[0], cmd, env) == -1)
			(ft_error(3));
	}
	else
	{
		data.s_path = make_env(env);
		access_exev(data, env, cmd);
	}
	return (0);
}

void	cmd1_handle(t_data data, char **av, char **env)
{
	data.fd_i = open(av[1], O_RDWR);
	if (data.fd_i < 0)
		(perror("Error"), exit(1));
	close(data.pipefd[0]);
	dup2(data.fd_i, 0);
	dup2(data.pipefd[1], 1);
	close(data.pipefd[1]);
	close(data.fd_i);
	exv_cmd(data, env, data.cmd1);
}

void	cmd2_handle(t_data data, char **av, char **env)
{
	close(data.pipefd[1]);
	dup2(data.pipefd[0], 0);
	close(data.pipefd[0]);
	data.fd_o = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (data.fd_o < 0)
		(perror("Error"), exit(1));
	dup2(data.fd_o, 1);
	close(data.fd_o);
	exv_cmd(data, env, data.cmd2);
}
