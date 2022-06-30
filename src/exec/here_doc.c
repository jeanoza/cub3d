/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:05:33 by mabriel           #+#    #+#             */
/*   Updated: 2022/06/03 14:05:36 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	help(t_cmd *cmd, int i, char **tmp, int fd)
{
	char	*join;

	while (1)
	{
		join = readline("> ");
		if (join)
			*tmp = ft_strjoin(join, "\n");
		else
		{
			*tmp = NULL;
			break ;
		}
		free(join);
		if (!*tmp || ft_strnstr(*tmp, cmd->redirs[i]->file, ft_strlen(*tmp)))
			break ;
		ft_putstr_fd(*tmp, fd);
		if (*tmp)
			free(*tmp);
		*tmp = NULL;
	}	
}

void	ask_here_doc(t_cmd *cmd, int i)
{
	int		fd[2];
	char	*tmp;

	if (pipe(fd) == -1)
		cmd->exit = 1;
	help(cmd, i, &tmp, fd[1]);
	if (tmp)
		free(tmp);
	else
		printf("\n");
	close(fd[1]);
	cmd->redirs[i]->fdin = fd[0];
}

void	ask_all_heredoc(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd->redirs && cmd->redirs[i])
	{
		if (cmd->redirs[i]->op == HEREDOC)
			ask_here_doc(cmd, i);
		i++;
	}
}

void	close_allcmds_heredoc(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
		close_all_heredoc(cmd[i++]);
}

void	ask_pipe_heredoc(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		ask_all_heredoc(cmd[i]);
		i++;
	}
}
