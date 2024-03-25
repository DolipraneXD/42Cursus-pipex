/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:28:31 by moel-fat          #+#    #+#             */
/*   Updated: 2024/03/25 13:29:07 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <libc.h>
# include "../libft/libft.h"
//**struct**//
typedef struct s_data
{
	int		pipefd[2];
	int		fd_o;
	int		fd_i;
	int		i;
	int		flag;
	char	**cmd1;
	char	**cmd2;
	char	**s_path;
	int		pid;
	int		pid1;
	int		pid2;
}			t_data;
//**Free-Error-tools**//
void	ft_error(int i);
void	ft_free(char **str);
//**exc cmd**//
void	cmd2_handle(t_data data, char **av, char **env);
void	cmd1_handle(t_data data, char **av, char **env);
int		exv_cmd(t_data data, char **env, char **cmd);
int		access_exev(t_data data, char **env, char **cmd);
int		check_slash(char **cmd);
char	**make_env(char **env);
char	*find_path(char **env);
void	ft_fork(t_data data, char **av, char **env);
#endif