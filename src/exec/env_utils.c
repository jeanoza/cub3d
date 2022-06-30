/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 03:05:15 by maxime            #+#    #+#             */
/*   Updated: 2022/06/07 03:05:17 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_env(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		printf("%s\n", s[i]);
		i++;
	}
}

void	realloc_env(char ***envp)
{
	char	**tmp;
	int		index;

	tmp = ft_calloc(1, P_SIZE);
	index = 0;
	while ((*envp)[index])
	{
		tmp = ft_realloc(tmp, (index + 1) * P_SIZE, (index + 2) * P_SIZE);
		tmp[index] = ft_strdup((*envp)[index]);
		++index;
	}
	tmp = ft_realloc(tmp, (index + 1) * P_SIZE, (index + 2) * P_SIZE);
	tmp[index + 1] = NULL;
	free_2d_array((void **)*envp);
	*envp = tmp;
}

int	get_env_index(char **envp, char *s)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], s, ft_strlen(s)))
			return (i);
		i++;
	}
	return (i);
}

char	*get_env(char **envp, char *s)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], s, ft_strlen(s)))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*spec_get_env(char **envp, char *s)
{
	int		i;
	int		j;
	char	*join;

	i = 0;
	j = 0;
	join = ft_strjoin(s, "=");
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], join, ft_strlen(join)))
		{
			while (envp[i][j] != '=')
				j++;
			free(join);
			return (envp[i] + ++j);
		}
		i++;
	}
	free(join);
	return (NULL);
}
