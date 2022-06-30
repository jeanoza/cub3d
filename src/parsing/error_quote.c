/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 22:41:09 by kychoi            #+#    #+#             */
/*   Updated: 2022/06/16 15:11:47 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function:  print_quote_err
 * --------------------------------------------------------------------------
 * Print quote error which is a little bit different with other cases.
 *
 * line: command line sent from prompt
 * e_char: character that cause error
 * returns: 1 if true else 0
 */
static int	print_quote_err(char quote)
{
	ft_putstr_fd("bash: syntax error: not closed quote(", STDERR_FILENO);
	ft_putstr_fd("`", STDERR_FILENO);
	write(STDERR_FILENO, &quote, 1);
	ft_putstr_fd("')\n", STDERR_FILENO);
	return (1);
}

/*
 * Function:  err_quote
 * --------------------------------------------------------------------------
 * Verify if quotes are not closed correctly
 * In general, the thing that cause multi-line event in shell
 * cf: `quote>` | `dquote>` in zsh, `>` in bash
 * But, if there is quote not-closed between other quote,
 * It doesn't throw error beacause it will be treated like a simple character.
 * 
 * line: command line sent from prompt
 * e_char: character that cause error
 * returns: 1 if true else 0
 */
int	err_quote(char *line)
{
	int		i;
	char	_quote;

	i = 0;
	while (line && line[i])
	{
		if (contains("'\"", line[i]))
		{
			_quote = line[i];
			++i;
			if (line[i] == '\0')
				return (print_quote_err(_quote));
			while (line[i])
			{
				if (line[i] == _quote)
					break ;
				if (line[i + 1] == '\0')
					return (print_quote_err(_quote));
				++i;
			}
		}
		if (line[i])
			++i;
	}
	return (0);
}

int	err_pipe(char *line, char *e_char)
{
	int		i;
	int		alnum_exist;
	int		has_quote;

	i = 0;
	alnum_exist = 0;
	has_quote = 0;
	while (line && line[i])
	{
		if (line[i] && ft_isalnum(line[i]))
			alnum_exist = 1;
		if (line[i] && (line[i] == '\'' || line[i] == '"'))
			has_quote = 1;
		if (!alnum_exist && !has_quote && line[i] == '|')
		{
			ft_putstr_fd("bash: syntax error near ", STDERR_FILENO);
			*e_char = line[i];
			return (1);
		}
		++i;
	}
	return (0);
}
