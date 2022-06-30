/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:51:49 by kychoi            #+#    #+#             */
/*   Updated: 2022/06/16 15:18:27 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	is_d_to_manage(char current, char next)
{
	if (current == 0 || next == 0)
		return (0);
	if (current == '$' && (ft_isalnum(next) || next == '_' || next == '?'))
		return (1);
	return (0);
}

static	void	manage_dollar(int *dollar_idx, char **strp, char **envp)
{
	int		i;
	char	*_key;
	char	*_value;
	char	*tmp[3];

	i = (*dollar_idx) + 1;
	if ((*strp)[i] == '?')
	{
		_value = ft_itoa(g_exit_status);
		++i;
	}
	else
	{
		while (*strp && (*strp)[i] && (*strp)[i] > 0
			&& (ft_isalnum((*strp)[i]) || (*strp)[i] == '_'))
			++i;
		_key = ft_substr(*strp, (*dollar_idx) + 1, i - (*dollar_idx) - 1);
		_value = ft_strdup(spec_get_env(envp, _key));
		free(_key);
	}
	tmp[0] = ft_substr(*strp, 0, *dollar_idx);
	*dollar_idx += (int) ft_strlen(_value) - 1;
	tmp[1] = ft_strjoin_free_all(tmp[0], _value);
	tmp[2] = ft_substr(*strp, i, ft_strlen(*strp) - i);
	merci_encore_norm(strp, tmp[1], tmp[2]);
}

static	void	manage_quote(char *quote, int *i_ptr, char **strp, char **envp)
{
	int	i;

	i = *i_ptr;
	*quote = (*strp)[i];
	++i;
	while ((*strp)[i] && (*strp)[i] != *quote)
	{
		if ((*quote == M_QUOTE_D && (*strp)[i] == M_QUOTE_S)
			|| (*quote == M_QUOTE_S && (*strp)[i] == M_QUOTE_D))
			(*strp)[i] *= -1;
		if (*quote == M_QUOTE_D && is_d_to_manage((*strp)[i], (*strp)[i + 1]))
			manage_dollar(&i, strp, envp);
		if ((*strp)[i])
			++i;
	}
	*quote = 0;
	*i_ptr = i;
}

static	void	make_quotes_non_printable(char **strp)
{
	int	i;

	i = 0;
	while (*strp && (*strp)[i])
	{
		if ((*strp)[i] == '\'' || (*strp)[i] == '"')
			(*strp)[i] *= -1;
		++i;
	}
}

/*
 * Function:  manage_quote_dollar
 * --------------------------------------------------------------------------
 * Manage quote(single and double) and dollar
 * Replace all quote by it's minus value
 * Replace env variable to its value
 *
 * str:	string
 */
char	*manage_quote_dollar(char *str, char **envp, char ***strsp, int idx)
{
	int		i;
	char	_quote;
	char	*tmp;

	tmp = str;
	make_quotes_non_printable(&str);
	_quote = 0;
	i = 0;
	while (str && str[i])
	{
		if (!_quote && (str[i] == M_QUOTE_D || str[i] == M_QUOTE_S))
			manage_quote(&_quote, &i, &str, envp);
		else if (isspace(str[i]))
			str[i] *= -1;
		else if (is_d_to_manage(str[i], str[i + 1]))
			manage_dollar(&i, &str, envp);
		if (str[i])
			++i;
	}
	if (tmp != str)
		(*strsp)[idx] = str;
	return (str);
}
