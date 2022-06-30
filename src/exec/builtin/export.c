/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:14:47 by maxime            #+#    #+#             */
/*   Updated: 2022/06/05 23:14:49 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	special_print(char **s)
{
	int	i;
	int	j;

	i = 0;
	while (s && s[i])
	{
		j = 0;
		printf("declare -x ");
		while (s[i][j] != '=')
			printf("%c", s[i][j++]);
		printf("%c\"", s[i][j]);
		while (s[i][++j])
			printf("%c", s[i][j]);
		printf("\"\n");
		i++;
	}
	return (0);
}

static int	check_equal(char *s, char **left, char **right)
{
	int	i;
	int	err;
	int	j;

	i = -1;
	err = 0;
	while (s && s[++i] && s[i] != '=')
	{
		if (s[0] == '=')
			err = 1;
		if (!ft_isalnum(s[i]) && s[i] != '=')
			err = 1;
	}
	if (err || (i + 1 && s[0] == '=') || s[0] == 0)
		return (printf("export: '%s': not a valid identifier\n", s));
	else
	{
		*left = ft_substr(s, 0, i);
		j = i;
		while (s[i])
			i++;
		*right = ft_substr(s, j + 1, i - j);
		return (0);
	}
}	

void	add_env_var(t_cmd *cmd, char *left, char *right)
{
	int		index;
	char	*tmp;

	index = 0;
	while (cmd->envp && cmd->envp[index])
		index++;
	realloc_env(&(cmd->envp));
	tmp = ft_strjoin(left, "=");
	cmd->envp[index] = ft_strjoin(tmp, right);
	free(tmp);
	free(right);
	free(left);
}

static int	update(t_cmd *cmd, char *left, char *right)
{
	char	*tmp;
	int		i;
	char	*join;

	join = ft_strjoin(left, "=");
	tmp = get_env(cmd->envp, join);
	free(join);
	if (tmp == NULL)
		return (1);
	i = get_env_index(cmd->envp, left);
	free(cmd->envp[i]);
	tmp = ft_strjoin(left, "=");
	cmd->envp[i] = ft_strjoin(tmp, right);
	free(tmp);
	free(right);
	free(left);
	return (0);
}

int	do_export(t_cmd *cmd)
{
	int		i;
	char	*left;
	char	*right;
	int		err;

	i = 1;
	err = 0;
	if (cmd->args[1] == NULL)
		return (special_print(cmd->envp));
	while (cmd->args && cmd->args[i])
	{
		left = NULL;
		right = NULL;
		if (!check_equal(cmd->args[i], &left, &right))
		{
			if (update(cmd, left, right))
				add_env_var(cmd, left, right);
		}
		else
			err = 1;
		i++;
	}
	return (err);
}
