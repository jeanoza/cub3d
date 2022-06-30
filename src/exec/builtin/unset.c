/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 02:52:46 by maxime            #+#    #+#             */
/*   Updated: 2022/06/06 02:52:48 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	strcmp_before_equal(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '=')
		i++;
	if ((size_t)i != ft_strlen(s2))
		return (1);
	i = 0;
	while (s1[i] && s1[i] == s2[i] && s1[i] != '=')
		++i;
	if (s1[i] == '=')
		i--;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

static int	count_match(t_cmd *cmd)
{
	int	i;
	int	j;
	int	count;

	i = 1;
	count = 0;
	while (cmd->args && cmd->args[i])
	{
		j = 0;
		while (cmd->envp[j])
		{
			if (!strcmp_before_equal(cmd->envp[j], cmd->args[i]))
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static int	check_match(t_cmd *cmd, char *full)
{
	int	i;

	i = 1;
	while (cmd->args && cmd->args[i])
	{
		if (!strcmp_before_equal(full, cmd->args[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	remalloc(t_cmd *cmd, char ***en)
{
	int		match;
	int		total;
	int		i;
	char	**new;

	match = count_match(cmd);
	total = 0;
	while (cmd->envp && cmd->envp[total])
		total++;
	new = malloc(sizeof(char *) * total - match + 100);
	if (!new)
		return (ret_error("malloc error\n"));
	total = 0;
	i = 0;
	while (cmd->envp && cmd->envp[i])
	{
		if (!check_match(cmd, cmd->envp[i]))
			new[total++] = cmd->envp[i];
		else
			free(cmd->envp[i]);
		i++;
	}
	new[total] = NULL;
	*en = new;
	return (0);
}

int	do_unset(t_cmd *cmd)
{
	char	**new;

	if (!count_match(cmd))
		return (0);
	if (remalloc(cmd, &(new)))
		return (1);
	free(cmd->envp);
	cmd->envp = new;
	return (0);
}
