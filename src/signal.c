/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:14:43 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/06/12 15:05:57 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if ctrl + '\'
static void	signal_on_quit(int signum, pid_t pid)
{
	if (signum == SIGQUIT)
	{
		if (pid == -1)
		{
			printf("\33[2K\r");
			rl_on_new_line();
			rl_redisplay();
		}
		else
		{
			write(STDOUT_FILENO, "Quit: 3\n", 8);
			g_exit_status = 131;
		}
	}
}

//if ctrl + c
//pid == -1 ? main : child process
static void	intercept_signal(int signum)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	if (signum == SIGINT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			write(STDOUT_FILENO, "\r", 1);
			write(STDOUT_FILENO, "  \n", 3);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_exit_status = 130;
		}
		else
		{
			write(STDOUT_FILENO, "  \n", 3);
			g_exit_status = 130;
		}
	}
	signal_on_quit(signum, pid);
}

//ctrl + 'c' = SIGINT
//ctrl + '\' = SIGQUIT
void	add_signal_listener(void)
{
	signal(SIGINT, intercept_signal);
	signal(SIGQUIT, intercept_signal);
}

//FIXME(line 46 - 52): en mac add next line is better
// (but linux to verify with bash)

// pid = waitpid(-1, &status, WNOHANG);
//FIXME: if use WNOHANG, listener is superpose between process
//ex: ./minishell in ./minishell in ./minishell ....
//but to test in linux 42
