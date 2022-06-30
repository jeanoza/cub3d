/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 22:52:28 by mabriel           #+#    #+#             */
/*   Updated: 2022/06/11 19:13:25 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_all_num(char *s)
{
	int	i;

	i = 0;
	if (s && s[0] == '-')
		i++;
	while (s && s[i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (0);
}

void	exit_msg(char *s, int mode, t_cmd **all)
{
	printf("exit\n");
	if (mode == 1)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
	}
	if (mode == 2)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_all(all);
		exit(2);
	}
}

void	exit_last(t_cmd **cmd)
{
	free_all(cmd);
	exit(g_exit_status);
}

int	do_exit(t_cmd *cmd, t_cmd **all)
{
	char	*arg;
	int		n;

	n = 0;
	arg = cmd->args[1];
	while (cmd->args && cmd->args[n])
		n++;
	if (n > 2 && is_all_num(arg))
		exit_msg(arg, 2, all);
	else if (n > 2 && !is_all_num(arg))
		exit_msg(NULL, 1, all);
	else if (n == 2 && is_all_num(arg))
		exit_msg(arg, 2, all);
	else if (n == 2 && !is_all_num(arg))
	{
		n = ft_atoi(arg);
		free_all(all);
		exit(n);
	}
	else if (n == 1)
		exit_last(all);
	return (0);
}
