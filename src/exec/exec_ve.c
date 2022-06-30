/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:59:41 by mabriel           #+#    #+#             */
/*   Updated: 2022/06/11 17:49:40 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_split(char **d)
{
	unsigned int	i;

	i = 0;
	while (d[i])
	{
		free(d[i]);
		i++;
	}
	free(d);
}

static char	*test_path(char *cmd, char *path)
{
	char	*dst;
	char	*tmp;

	if (!cmd || cmd[0] == 0)
		return (NULL);
	tmp = ft_strjoin(path, "/");
	dst = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!access(dst, F_OK))
		return (dst);
	else
		free(dst);
	return (NULL);
}

static char	*find_path(char *cmd, char **envp)
{
	char			**all_paths;
	char			**tmp;
	char			*dest;
	unsigned int	i;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=/", 10))
		i++;
	if (envp[i] == NULL)
		return (NULL);
	tmp = ft_split(envp[i], '=');
	all_paths = ft_split(tmp[1], ':');
	free_split(tmp);
	i = -1;
	while (all_paths[++i])
	{
		dest = test_path(cmd, all_paths[i]);
		if (dest)
		{
			free_split(all_paths);
			return (dest);
		}
	}
	free_split(all_paths);
	return (NULL);
}

static void	err(char *s, t_cmd *cmd)
{
	if (errno == 2)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": command not found\n", 2);
		cmd->exit = 127;
	}
	else if (errno == 13)
	{
		perror(s);
		cmd->exit = 126;
	}
	else
	{
		perror(s);
		cmd->exit = 2;
	}
}

void	exec_ve(char *cmd, char **envp, t_cmd *c)
{
	char	*path;
	int		ret;

	if (!access(cmd, F_OK))
		path = cmd;
	else
		path = find_path(c->args[0], envp);
	ret = 0;
	if (!cmd || !path)
	{
		free(path);
		err(cmd, c);
		return ;
	}
	else
	{
		ret = execve(path, c->args, envp);
		if (!(errno == 13))
			free(path);
	}
	if (ret == -1)
		err(cmd, c);
}
