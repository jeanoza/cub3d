/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:31:11 by mabriel           #+#    #+#             */
/*   Updated: 2022/06/02 16:32:17 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_all_fd(t_cmd *cmd, int i)
{
	int	index;

	index = i - 1;
	while (index >= 0)
	{
		if (cmd->redirs[index]->op == IN)
			close(cmd->redirs[index]->fdin);
		if (cmd->redirs[index]->op == OUT)
			close(cmd->redirs[index]->fdout);
		if (cmd->redirs[index]->op == APPEND)
			close(cmd->redirs[index]->fdout);
		index--;
	}
}

void	close_all_heredoc(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd->redirs && cmd->redirs[i])
	{
		if (cmd->redirs[i]->op == HEREDOC)
			close(cmd->redirs[i]->fdin);
		i++;
	}
}

int	error_opening(t_cmd *cmd, int i)
{
	close_all_fd(cmd, i);
	close_all_heredoc(cmd);
	perror(cmd->redirs[i]->file);
	cmd->exit = 1;
	return (1);
}

int	check_fd(t_cmd *cmd, int i)
{
	if (cmd->redirs[i]->op == IN && cmd->redirs[i]->fdin == -1)
		return (1);
	else if (cmd->redirs[i]->op == OUT && cmd->redirs[i]->fdout == -1)
		return (1);
	else if (cmd->redirs[i]->op == APPEND && cmd->redirs[i]->fdout == -1)
		return (1);
	else
		return (0);
}

int	open_all_fd(t_cmd *cmd)
{
	int		i;
	char	*path;

	i = 0;
	if (!cmd)
		return (1);
	while (cmd->redirs && cmd->redirs[i] && cmd->exit == 0)
	{
		path = cmd->redirs[i]->file;
		if (cmd->redirs[i]->op == IN)
			cmd->redirs[i]->fdin = open(path, O_RDONLY);
		if (cmd->redirs[i]->op == APPEND)
			cmd->redirs[i]->fdout = open(path, 02101, 0664);
		if (cmd->redirs[i]->op == OUT)
			cmd->redirs[i]->fdout = open(path, 01101, 0664);
		if (check_fd(cmd, i))
			return (error_opening(cmd, i));
		i++;
	}
	return (0);
}
