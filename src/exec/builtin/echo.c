/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 23:01:06 by mabriel           #+#    #+#             */
/*   Updated: 2022/05/31 23:01:08 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	check(char *s)
{
	int	i;

	i = 1;
	if (s && s[0] == '-')
	{
		if (ft_strlen(s) == 1)
			return (0);
		while (s[i])
			if (s[i++] != 'n')
				return (0);
		return (1);
	}
	else
		return (0);
}

static int	check_options(t_cmd *cmd)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (cmd->args && cmd->args[i])
	{
		if (check(cmd->args[i]))
			ret++;
		else
			break ;
		i++;
	}
	return (ret);
}

int	do_echo(t_cmd *cmd)
{
	int	n_options;
	int	i;

	n_options = check_options(cmd);
	if (n_options >= 1)
		i = n_options + 1;
	else
		i = 1;
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i++]);
		if (cmd->args[i])
			printf(" ");
	}
	if (!n_options)
		printf("\n");
	return (0);
}
/*
int main(int argc, char **argv)
{
	t_cmd *cmd = malloc(sizeof(t_cmd));

	cmd->name = argv[1];
	cmd->args = ft_split(cmd->name, ' ');
	do_echo(cmd);
}*/