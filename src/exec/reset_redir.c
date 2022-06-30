/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 23:04:55 by mabriel           #+#    #+#             */
/*   Updated: 2022/05/28 23:05:05 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	reset_stdin(t_cmd *cmd, int index)
{
	dup2(cmd->redirs[index]->savein, 0);
	close(cmd->redirs[index]->fdin);
	close(cmd->redirs[index]->savein);
}

static void	reset_stdout(t_cmd *cmd, int index)
{
	dup2(cmd->redirs[index]->saveout, 1);
	close(cmd->redirs[index]->fdout);
	close(cmd->redirs[index]->saveout);
}

void	reset_redir(t_cmd *cmd)
{
	if (get_last_out(cmd) != -1)
		reset_stdout(cmd, get_last_out(cmd));
	if (get_last_in(cmd) != -1)
		reset_stdin(cmd, get_last_in(cmd));
}
