/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:20:36 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/06/16 15:07:35 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function:  parse_error
 * --------------------------------------------------------------------------
 * Except all error posssible before initialize cmds
 *
 * line: command line sent from prompt
 * returns: if error 1 else 0
 */
static int	parse_error(char *line)
{
	char	e;
	int		i;

	i = -1;
	e = 0;
	if (err_forbidden_char(line, &e) || err_end_by_op(line, &e)
		|| err_multiple_op(line, &e) || err_space_btw_op(line, &e, i)
		|| err_mix_op(line, &e)
		|| err_pipe(line, &e))
	{
		ft_putstr_fd("unexpected token ", STDERR_FILENO);
		ft_putstr_fd("`", STDERR_FILENO);
		if (e == -42)
			write(STDERR_FILENO, "newline", 8);
		else
			write(STDERR_FILENO, &e, 1);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (1);
	}
	else if (err_quote(line))
		return (1);
	return (0);
}

/*
 * Function:  parse
 * --------------------------------------------------------------------------
 * Verify line is validate or not by parse_error function.
 * Then initialize t_cmd*[] by calling init_cmd_array.
 * Returns this array of t_cmd *
 *
 * line: command line sent from prompt
 * envp: char ** composed by environment variable which is char *
 * returns:	NULL | [t_cmd *c1, t_cmd *c2..., NULL]
 */
t_cmd	**parse(char *line, char **envp)
{
	if (parse_error(line))
		return (NULL);
	return (init_cmd_array(line, envp));
}
