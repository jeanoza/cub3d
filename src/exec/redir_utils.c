/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:28:58 by mabriel           #+#    #+#             */
/*   Updated: 2022/06/02 19:29:02 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* return -1 if no input else return index of input redirs*/
int	get_last_in(t_cmd *cmd)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = -1;
	if (!cmd)
		return (-1);
	while (cmd->redirs && cmd->redirs[i])
	{
		if (cmd->redirs[i]->op == IN || cmd->redirs[i]->op == HEREDOC)
			tmp = i;
		i++;
	}
	return (tmp);
}

/* return -1 if no output else return index of output redirs*/
int	get_last_out(t_cmd *cmd)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = -1;
	if (!cmd)
		return (-1);
	while (cmd->redirs && cmd->redirs[i])
	{
		if (cmd->redirs[i]->op == OUT || cmd->redirs[i]->op == APPEND)
			tmp = i;
		i++;
	}
	return (tmp);
}

void	close_all_prev_fd(t_cmd *cmd)
{
	int	last_in;
	int	last_out;
	int	i;

	if (!cmd)
		return ;
	last_in = get_last_in(cmd);
	last_out = get_last_out(cmd);
	i = 0;
	while (cmd->redirs && cmd->redirs[i])
	{
		if (i != last_in && (cmd->redirs[i]->op == IN
				|| cmd->redirs[i]->op == HEREDOC))
			close(cmd->redirs[i]->fdin);
		if (i != last_out && (cmd->redirs[i]->op == OUT
				|| cmd->redirs[i]->op == APPEND))
			close(cmd->redirs[i]->fdout);
		i++;
	}
}
