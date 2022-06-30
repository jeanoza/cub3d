/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 09:44:51 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/06/11 11:00:56 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	add_char_in_str(char **str, int *len, char c)
{
	*str = (char *)ft_realloc(*str, *len + 1, *len + 2);
	if (!*str)
		return ;
	(*str)[*len] = c;
	*len += 1;
}

static void	merci_norminette(char *str, char **res, int i, int len)
{
	while (str && str[i])
	{
		if (str[i] == M_QUOTE_D || str[i] == M_QUOTE_S)
		{
			if (str[i] > 0 && str[i + 1] && str[i] == str[i + 1])
				add_char_in_str(res, &len, str[i]);
			++i;
		}
		else
		{
			if (is_redir_op(str[i]) && len - 1 > 0 && (*res)[len - 1]
				&& ((*res)[len - 1] != M_SPACE
					&& !is_redir_op((*res)[len - 1])))
				add_char_in_str(res, &len, M_SPACE);
			add_char_in_str(res, &len, str[i]);
			if (str[i] && is_redir_op(str[i]))
			{
				++i;
				while (str[i] && str[i] == M_SPACE)
					++i;
			}
			else if (str[i])
				++i;
		}
	}
}

static	char	*generate_newline(char *str)
{
	char	*res;
	int		len;
	int		i;

	res = (char *)ft_calloc(1, sizeof(char));
	i = 0;
	len = 0;
	merci_norminette(str, &res, i, len);
	return (res);
}

/*
 * Function:  init_cmd
 * --------------------------------------------------------------------------
 * Mallocate t_cmd * and replace quote and space by calling manage_quote_dollar
 * Step through the str replaced given by while loop.
 * In loop, call getter functions by need to put elements of t_cmd.
 *
 * str:	string
 * envp: char ** composed by environment variable which is char *
 * returns:	NULL | [t_cmd *c1, t_cmd *c2..., NULL]
 */
static t_cmd	*init_cmd(char **strp, int idx, char **envp)
{
	t_cmd	*_cmd;
	char	*new_line;
	int		i;
	char	**splitted;

	_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (_cmd == NULL)
		return (NULL);
	new_line = generate_newline(
			manage_quote_dollar(strp[idx], envp, &strp, idx));
	splitted = (char **)ft_split(new_line, M_SPACE);
	free(new_line);
	i = 0;
	while (splitted && splitted[i])
	{
		if (splitted[i][0] == M_QUOTE_D || splitted[i][0] == M_QUOTE_S)
			splitted[i][0] = 0;
		if (is_redir_op(splitted[i][0]))
			get_op(_cmd, splitted[i]);
		else
			get_name(_cmd, splitted[i]);
		++i;
	}
	free_2d_array((void **)splitted);
	return (_cmd);
}

/*
 * Function:  init_cmd_array
 * --------------------------------------------------------------------------
 * Split line(char *) by pipe
 * By this char ** splitted malloacted, initialize array of t_cmd *
 * Free that splitted char **
 * Returns this array of t_cmd * terminating by NULL.
 *
 * line: command line sent from prompt
 * envp: char ** composed by environment variable which is char *
 * returns:	NULL | [t_cmd *c1, t_cmd *c2..., NULL]
 */
t_cmd	**init_cmd_array(char *line, char **envp)
{
	t_cmd	**_cmds;
	char	**_strs;
	int		i;

	_strs = ft_split(line, '|');
	if (_strs == NULL)
		return (NULL);
	_cmds = (t_cmd **)ft_calloc(count_el((void **) _strs) + 1, P_SIZE);
	i = 0;
	while (_strs && _strs[i])
	{
		_cmds[i] = init_cmd(_strs, i, envp);
		if (_cmds[i] == NULL)
			break ;
		else
			_cmds[i]->envp = envp;
		++i;
	}
	free_2d_array((void **)_strs);
	return (_cmds);
}
