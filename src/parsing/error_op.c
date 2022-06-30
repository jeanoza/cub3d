/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:51:12 by kychoi            #+#    #+#             */
/*   Updated: 2022/06/16 14:51:14 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function:  err_forbidden_char
 * --------------------------------------------------------------------------
 * Verify if line contains forbidden character(like: ';', '\n')
 *
 * line: command line sent from prompt
 * e_char: character that cause error
 * returns: 1 if true else 0
 */
int	err_forbidden_char(char *line, char *e_char)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (contains(CHAR_FORBIDDEN, line[i]))
		{
			ft_putstr_fd("bash: syntax error near ", STDERR_FILENO);
			*e_char = line[i];
			return (1);
		}
		++i;
	}
	return (0);
}

/*
 * Function:  err_end_by_op
 * --------------------------------------------------------------------------
 * Verify if line ends by operator
 * this function manage the case with space after last operator.
 *
 * line: command line sent from prompt
 * e_char: character that cause error
 * returns: 1 if true else 0
 */
int	err_end_by_op(char *line, char *e_char)
{
	int		i;

	i = 0;
	while (line && line[i])
		++i;
	--i;
	while (line && line[i] == ' ')
		--i;
	if (is_redir_op(line[i]))
	{
		ft_putstr_fd("bash: syntax error near ", STDERR_FILENO);
		*e_char = -42;
		return (1);
	}
	return (0);
}

/*
 * Function:  err_multiple_op
 * --------------------------------------------------------------------------
 * Verify if there are multiple operator without cmd in side.
 * ex: ls >>> test.txt, ls || wc -l, ls <<< text.txt
 *
 * line: command line sent from prompt
 * e_char: character that cause error
 * returns: 1 if true else 0
 */
int	err_multiple_op(char *line, char *e_char)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		if (is_redir_op(line[i]))
		{
			if (line[i + 1] && line[i] == line[i + 1])
			{
				if (line[i + 1] == '|'
					|| (line[i + 2] && line[i + 1] == line[i + 2]))
				{
					ft_putstr_fd("bash: syntax error near ", STDERR_FILENO);
					*e_char = line[i];
					return (1);
				}
			}
		}
		++i;
	}
	return (0);
}

/*
 * Function:  err_space_btw_op
 * --------------------------------------------------------------------------
 * Verify if there is(are) space between redirection operator
 * ex: ls < << ls, ls < | ls, ls | > ls...etc
 *
 * line: command line sent from prompt
 * e_char: character that cause error
 * returns: 1 if true else 0
 */
int	err_space_btw_op(char *line, char *e_char, int i)
{
	char	_op;

	while (line && line[++i])
	{
		if (is_redir_op(line[i]))
		{
			_op = line[i];
			if (line[i + 1] && line[i] == line[i + 1])
				++i;
			++i;
			if (line[i] == ' ')
			{
				while (line[i] == ' ')
					++i;
				if (is_redir_op(line[i]) && _op != '|')
				{
					ft_putstr_fd("bash: syntax error near ", STDERR_FILENO);
					*e_char = line[i];
					return (1);
				}
			}
		}
	}
	return (0);
}

/*
 * Function:  err_mix_op
 * --------------------------------------------------------------------------
 * Verify if there linked redirection operator
 * ex: ls <| ls, ls |> ls.... etc
 *
 * line: command line sent from prompt
 * e_char: character that cause error
 * returns: 1 if true else 0
 */
int	err_mix_op(char *line, char *e_char)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		if (is_redir_op(line[i]))
		{
			if (line[i + 1] && is_redir_op(line[i + 1])
				&& line[i] != line[i + 1])
			{
				ft_putstr_fd("bash: syntax error near ", STDERR_FILENO);
				*e_char = line[i + 1];
				return (1);
			}
		}
		++i;
	}
	return (0);
}
