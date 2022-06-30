/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:21:08 by kychoi            #+#    #+#             */
/*   Updated: 2022/06/12 15:31:30 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

static int	is_empty_line(char *str)
{
	int	i;

	if (str == NULL)
	{
		printf("\x1b[1F");
		printf("\x1b[2K");
		printf("$> exit\n");
		exit(g_exit_status);
	}
	if (ft_strlen(str) == 0)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		++i;
	}
	return (1);
}

static void	init_env(char ***envp)
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
	*envp = tmp;
}

//for reduce line...
static void	exec_free_cmds(t_cmd **cmds, char ***save_envp)
{
	if (cmds)
	{
		exec_command(cmds);
		if (*save_envp != cmds[0]->envp)
			*save_envp = cmds[0]->envp;
		free_all_cmd(cmds);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_cmd	**cmds;
	char	**save_envp;

	(void)ac;
	(void)av;
	put_header();
	init_env(&envp);
	save_envp = envp;
	add_signal_listener();
	while (42)
	{
		line = readline("$> ");
		if (!is_empty_line(line))
		{
			add_history(line);
			cmds = parse(line, save_envp);
			exec_free_cmds(cmds, &save_envp);
		}
		free(line);
	}
	free_2d_array((void **)save_envp);
	return (g_exit_status);
}
