/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:32:08 by moel-fat          #+#    #+#             */
/*   Updated: 2024/03/23 15:12:14 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(int i)
{
	if (i == 1)
		ft_putstr_fd("Error\nnumber of arg must be 4\n", 2);
	else if (i == 2)
		ft_putstr_fd("command not found:\n", 2);
	else if (i == 3)
		ft_putstr_fd("no such file or directory:\n", 2);
	else if (i == 0)
		exit(1);
	exit(1);
}

void	ft_free(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
	str = NULL;
}
