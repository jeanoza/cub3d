/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 23:49:42 by maxime            #+#    #+#             */
/*   Updated: 2022/06/03 23:50:06 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	do_env(t_cmd *cmd)
{
	if (cmd->args && cmd->args[1] != NULL)
	{
		ft_putstr_fd("env: arguments and options are not available\n", 2);
		return (1);
	}
	print_env(cmd->envp);
	return (0);
}
