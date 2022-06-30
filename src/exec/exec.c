/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 22:46:35 by mabriel           #+#    #+#             */
/*   Updated: 2022/05/31 22:46:55 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *s)
{
	if (!s)
		return (0);
	if (!ft_strncmp(s, "env", ft_strlen(s)) && ft_strlen(s) == 3)
		return (1);
	if (!ft_strncmp(s, "cd", ft_strlen(s)) && ft_strlen(s) == 2)
		return (2);
	if (!ft_strncmp(s, "echo", ft_strlen(s)) && ft_strlen(s) == 4)
		return (3);
	if (!ft_strncmp(s, "unset", ft_strlen(s)) && ft_strlen(s) == 5)
		return (4);
	if (!ft_strncmp(s, "pwd", ft_strlen(s)) && ft_strlen(s) == 3)
		return (5);
	if (!ft_strncmp(s, "export", ft_strlen(s)) && ft_strlen(s) == 6)
		return (6);
	if (!ft_strncmp(s, "exit", ft_strlen(s)) && ft_strlen(s) == 4)
		return (7);
	return (0);
}

void	exec_builtins(t_cmd *cmd, t_cmd **all)
{
	redir(cmd);
	if (cmd->exit == 0)
	{
		if (is_builtin(cmd->args[0]) == 1)
			g_exit_status = do_env(cmd);
		if (is_builtin(cmd->args[0]) == 2)
			g_exit_status = do_cd(cmd);
		if (is_builtin(cmd->args[0]) == 3)
			g_exit_status = do_echo(cmd);
		if (is_builtin(cmd->args[0]) == 4)
			g_exit_status = do_unset(cmd);
		if (is_builtin(cmd->args[0]) == 5)
			g_exit_status = do_pwd();
		if (is_builtin(cmd->args[0]) == 6)
			g_exit_status = do_export(cmd);
		if (is_builtin(cmd->args[0]) == 7)
			g_exit_status = do_exit(cmd, all);
		reset_redir(cmd);
	}
}

void	get_exit(t_cmd *cmd, int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (g_exit_status == 0)
		g_exit_status = cmd->exit;
}

void	simple_cmd(t_cmd *cmd, t_cmd **all)
{
	int	status;
	int	pid;

	if (!(cmd->name))
		return ;
	if (cmd->args && is_builtin(cmd->args[0]))
		exec_builtins(cmd, all);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			redir(cmd);
			if (cmd->exit == 0)
			{
				exec_ve(cmd->name, cmd->envp, cmd);
				reset_redir(cmd);
			}
			status = cmd->exit;
			free_all(all);
			exit(status);
		}
		waitpid(pid, &status, 0);
		get_exit(cmd, status);
	}
}

void	exec_command(t_cmd **all_cmds)
{
	int	cmd_nbr;

	if (!all_cmds || all_cmds[0] == NULL)
		return ;
	ask_pipe_heredoc(all_cmds);
	if (all_cmds[1] == NULL && all_cmds[0])
		simple_cmd(all_cmds[0], all_cmds);
	else
	{
		cmd_nbr = 0;
		while (all_cmds[cmd_nbr])
			cmd_nbr++;
		if (cmd_nbr > 0)
			exec_pipe(all_cmds, cmd_nbr);
	}
	close_allcmds_heredoc(all_cmds);
}
