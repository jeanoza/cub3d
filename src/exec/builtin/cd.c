/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 23:03:16 by mabriel           #+#    #+#             */
/*   Updated: 2022/05/31 23:03:39 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	check_cd(t_cmd *cmd)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (cmd->args && cmd->args[i])
		i++;
	if (i > 2 && ++ret)
		ft_putstr_fd("cd: too many arguments\n", 2);
	if (i < 2 && ++ret)
		ft_putstr_fd("cd: one argument needed\n", 2);
	return (ret);
}

static void	help_oldpwd(t_cmd *cmd, int i, int src_len)
{
	char	*tmp;

	tmp = get_env(cmd->envp, "PWD=");
	if (tmp)
	{
		cmd->envp[i] = malloc(sizeof(char) * src_len + 4);
		cmd->envp[i][0] = 0;
		ft_memcpy(cmd->envp[i] + 3, tmp, src_len + 1);
		cmd->envp[i][0] = 'O';
		cmd->envp[i][1] = 'L';
		cmd->envp[i][2] = 'D';
	}
}

static void	old_pwd(t_cmd *cmd)
{
	char	*tmp;
	int		i;
	int		src_len;

	tmp = get_env(cmd->envp, "OLDPWD=");
	i = get_env_index(cmd->envp, "OLDPWD=");
	src_len = ft_strlen(get_env(cmd->envp, "PWD="));
	if (tmp)
	{
		help_oldpwd(cmd, i, src_len);
		free(tmp);
	}
	else
	{
		realloc_env(&(cmd->envp));
		help_oldpwd(cmd, i, src_len);
	}
}

static void	current_pwd(t_cmd *cmd)
{
	char	*s;
	int		i;
	int		size;

	size = 4096;
	s = getcwd(NULL, size);
	if (s)
	{
		i = get_env_index(cmd->envp, "PWD=");
		if (get_env(cmd->envp, "PWD=") && cmd->envp[i])
		{
			free(cmd->envp[i]);
			cmd->envp[i] = ft_strjoin("PWD=", s);
		}
		else
		{
			realloc_env(&(cmd->envp));
			cmd->envp[i] = ft_strjoin("PWD=", s);
		}
		free(s);
	}
	else
		perror(cmd->args[0]);
}

int	do_cd(t_cmd *cmd)
{
	int	ret;

	if (check_cd(cmd))
		return (1);
	current_pwd(cmd);
	ret = chdir(cmd->args[1]);
	if (ret == 0)
	{
		old_pwd(cmd);
		current_pwd(cmd);
		return (0);
	}
	else if (ret == -1)
	{
		perror(cmd->args[0]);
		return (1);
	}
	return (1);
}
