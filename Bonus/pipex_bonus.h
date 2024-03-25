/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:28:45 by moel-fat          #+#    #+#             */
/*   Updated: 2024/03/22 14:46:32 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <libc.h>
# include "../libft/libft.h"
# include "get_next_line.h"
//**struct**//
typedef struct s_data
{
	int		pipefd[2];
	int		old_fd;
	int		fd_o;
	int		fd_i;
	char	*hd_filename;
	int		i;
	int		flag;
	char	**cmd1;
	char	**cmd2;
	char	**s_cmd;
	char	**lastcmd;
	char	**s_path;
	int		pid;
	int		heredoc_fd;
	int		hd_flag;
}			t_data;
//**Free-Error-tools**//
void	ft_error(int i);
void	ft_free(char **str);
//**excute commands**//
void	execut_cmd(char *cmd, t_data *data, char **env);
int		exv_cmd(t_data data, char **env, char **cmd);
int		access_exev(t_data data, char **env, char **cmd);
int		check_slash(char **cmd);
char	**make_env(char **env);
char	*find_path(char **env);
void	exv_lastcmd(t_data *data, char **av, int ac, char **env);
//**here_doc**//
void	no_heredoc_assign(t_data *data, char **av, int ac);
void	heredoc_assign(t_data *data, char **av, int ac);
int		check_heredoc(t_data *data, char **av);
//**ulits**//
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin_nofree(char *s1, char *s2);
#endif