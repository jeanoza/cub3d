/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:56:11 by maxime            #+#    #+#             */
/*   Updated: 2022/05/28 23:18:23 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	redir_stdin(t_cmd *cmd, int index)
{
	if (index != -1)
	{
		cmd->redirs[index]->savein = dup(0);
		dup2(cmd->redirs[index]->fdin, 0);
	}
}

static void	redir_stdout(t_cmd *cmd, int index)
{
	if (index == -1)
		return ;
	cmd->redirs[index]->saveout = dup(1);
	dup2(cmd->redirs[index]->fdout, 1);
}

void	redir(t_cmd *cmd)
{
	if (!open_all_fd(cmd))
	{
		close_all_prev_fd(cmd);
		redir_stdin(cmd, get_last_in(cmd));
		redir_stdout(cmd, get_last_out(cmd));
	}
}
