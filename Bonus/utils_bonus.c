/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:05:59 by moel-fat          #+#    #+#             */
/*   Updated: 2024/03/25 19:39:37 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	s_path = ft_split(path, ':');
	free(path);
	return (s_path);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_nofree(char *s1, char *s2)
{
	size_t	tlen;
	char	*s;

	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	tlen = ft_strlen(s1) + ft_strlen(s2) +1;
	s = (char *) malloc (tlen);
	if (s == NULL)
		return (NULL);
	ft_strlcpy(s, s1, tlen);
	ft_strlcpy(s + ft_strlen(s1), s2, tlen);
	free(s2);
	return (s);
}
