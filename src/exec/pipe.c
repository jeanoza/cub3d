/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:56:06 by mabriel           #+#    #+#             */
/*   Updated: 2022/06/10 11:58:42 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ex_cmd(t_cmd **cmd, int i, int *ret)
{
	redir(cmd[i]);
	if (cmd[i]->name && cmd[i]->exit == 0)
	{
		if (is_builtin(cmd[i]->args[0]))
			exec_builtins(cmd[i], cmd);
		else
			exec_ve(cmd[i]->name, cmd[i]->envp, cmd[i]);
		reset_redir(cmd[i]);
	}
	*ret = cmd[i]->exit;
	free_all(cmd);
}

static int	first_cmd(t_cmd **cmd, int i)
{
	int	fd[2];
	int	ret;

	if (pipe(fd) == -1)
		exit_error();
	cmd[i]->pid = fork();
	if (cmd[i]->pid == -1)
		exit_error();
	if (cmd[i]->pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		ex_cmd(cmd, i, &ret);
		close(fd[1]);
		exit(ret);
	}
	close(fd[1]);
	return (fd[0]);
}

static int	mid_cmd(t_cmd **cmd, int read_fd, int i)
{
	int	fd[2];
	int	ret;

	if (pipe(fd) == -1)
		exit_error();
	cmd[i]->pid = fork();
	if (cmd[i]->pid == 0)
	{
		dup2(read_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		ex_cmd(cmd, i, &ret);
		close(read_fd);
		close(fd[1]);
		exit(ret);
	}
	close(fd[1]);
	close(read_fd);
	return (fd[0]);
}

static int	last_cmd(t_cmd **cmd, int last_pipe, int i)
{
	int	ret;

	cmd[i]->pid = fork();
	if (cmd[i]->pid == -1)
		exit_error();
	if (cmd[i]->pid == 0)
	{
		if (!(cmd[i]->redirs && cmd[i]->redirs[0]->op == HEREDOC))
			dup2(last_pipe, STDIN_FILENO);
		ex_cmd(cmd, i, &ret);
		close(last_pipe);
		exit(ret);
	}
	close(last_pipe);
	return (cmd[i]->exit);
}

int	exec_pipe(t_cmd **cmd, int cmd_nbr)
{
	int	fd;
	int	i;
	int	status;

	i = 0;
	if (!cmd || !*cmd)
		return (-1);
	fd = first_cmd(cmd, i);
	while (++i < cmd_nbr - 1)
		fd = mid_cmd(cmd, fd, i);
	last_cmd(cmd, fd, i);
	i = 0;
	while (cmd[i])
		waitpid(cmd[i++]->pid, &status, 0);
	cmd[0]->exit = WEXITSTATUS(status);
	return (WEXITSTATUS(status));
}
