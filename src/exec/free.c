/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <mabriel@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 23:42:58 by maxime            #+#    #+#             */
/*   Updated: 2022/05/28 23:42:59 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	cmd->args = NULL;
}

static void	free_redirs(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd->redirs && cmd->redirs[i])
	{
		if (cmd->redirs[i]->file)
			free(cmd->redirs[i]->file);
		free(cmd->redirs[i]);
		i++;
	}
	if (cmd->redirs)
		free(cmd->redirs);
	cmd->redirs = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->name)
		free(cmd->name);
	if (cmd->args)
		free_args(cmd);
	if (cmd->redirs)
		free_redirs(cmd);
	if (cmd)
		free(cmd);
}

void	free_all_cmd(t_cmd **all)
{
	int	i;

	i = 0;
	while (all && all[i])
	{
		free_cmd(all[i]);
		i++;
	}
	if (all)
		free(all);
}

void	free_all(t_cmd **cmd)
{
	if (cmd && cmd[0] && cmd[0]->envp)
		free_2d_array((void **)cmd[0]->envp);
	free_all_cmd(cmd);
}
