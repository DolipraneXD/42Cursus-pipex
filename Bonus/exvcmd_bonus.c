/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exvcmd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:58:53 by moel-fat          #+#    #+#             */
/*   Updated: 2024/03/23 12:12:07 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_slash(char **cmd)
{
	if (cmd == NULL || *cmd == NULL)
		ft_error(2);
	if (ft_strchr(cmd[0], '/') != NULL)
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
				(perror("Error"), free(joined), joined = NULL, exit (1));
			data.flag = 1;
			(free(joined), joined = NULL);
			break ;
		}
		else
			(free(joined), joined = NULL);
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
			ft_error(3);
	}
	else
	{
		data.s_path = make_env(env);
		access_exev(data, env, cmd);
	}
	return (0);
}

void	execut_cmd(char *cmd, t_data *data, char **env)
{
	data->s_cmd = ft_split(cmd, ' ');
	if (pipe(data->pipefd) == -1)
		(perror("Error"), exit(1));
	data->pid = fork();
	if (data->pid == -1)
		(perror("Error"), exit(1));
	if (data->pid == 0)
	{
		close(data->pipefd[0]);
		if (dup2(data->pipefd[1], 1) == -1)
			(perror("Error"), exit(1));
		close(data->pipefd[1]);
		exv_cmd(*data, env, data->s_cmd);
	}
	else
	{
		close(data->pipefd[1]);
		if (dup2(data->pipefd[0], 0) == -1)
			(perror("Error"), exit(1));
		close(data->pipefd[0]);
		ft_free(data->s_cmd);
	}
}

void	exv_lastcmd(t_data *data, char **av, int ac, char **env)
{
	data->lastcmd = ft_split(av[ac -2], ' ');
	data->pid = fork();
	if (data->pid == -1)
		(perror("Error"), exit(0));
	if (data->pid == 0)
		exv_cmd(*data, env, data->lastcmd);
	else
	{
		if (dup2(data->old_fd, 0) == -1)
			(perror("Error"), exit(1));
		close(data->old_fd);
		while (1)
		{
			if (waitpid(-1, NULL, 0) == -1)
				break ;
		}
		ft_free(data->lastcmd);
		data->lastcmd = NULL;
		ft_free(data->s_path);
		data->s_cmd = NULL;
		free(data->hd_filename);
		data->hd_filename = NULL;
	}
}
