/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:28:03 by moel-fat          #+#    #+#             */
/*   Updated: 2024/03/25 13:29:00 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != NULL)
			return (env[i]);
		else
			i++;
	}
	return (NULL);
}

char	**make_env(char **env)
{
	char	*path;
	char	**s_path;

	if (env == NULL)
		ft_error(0);
	path = find_path(env);
	if (path == NULL)
		ft_error(0);
	path = ft_strtrim(path, "PATH=");
	if (path == NULL)
		ft_error(2);
	s_path = ft_split(path, ':');
	free(path);
	return (s_path);
}

void	ft_fork(t_data data, char **av, char **env)
{
	if (pipe(data.pipefd) == -1)
		perror("Error");
	data.pid1 = fork();
	if (data.pid1 < 0)
		(perror("Error"), exit(1));
	if (data.pid1 == 0)
		cmd1_handle(data, av, env);
	else
	{
		data.pid2 = fork();
		if (data.pid2 < 0)
			(perror("Error"), exit(1));
		if (data.pid2 == 0)
			cmd2_handle(data, av, env);
		close(data.pipefd[0]);
		close(data.pipefd[1]);
		wait(NULL);
		wait(NULL);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 5)
		ft_error(1);
	data.cmd1 = ft_split(av[2], ' ');
	data.cmd2 = ft_split(av[3], ' ');
	ft_fork(data, av, env);
	ft_free(data.s_path);
	ft_free(data.cmd1);
	ft_free(data.cmd2);
	exit(0);
}
