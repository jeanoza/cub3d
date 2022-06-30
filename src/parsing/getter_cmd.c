/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:39:30 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/06/09 12:32:49 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function:  get_op
 * --------------------------------------------------------------------------
 * Get redirection operator from string given.
 *
 * If cmd->redirs is NULL,
 * 	Mallocate a [t_redir *, NULL]; 
 * Else
 *	Re-allocate cmd->redirs to add like [t_redir *r1, t_redir *r2 ..., NULL];
 * 
 * cmd: t_cmd pointer
 * str: string
 */

void	get_op(t_cmd *cmd, char *str)
{
	int	_len;
	int	i;

	_len = count_el((void **) cmd->redirs);
	if (_len == 0)
		cmd->redirs = ft_calloc(2, sizeof(t_redir *));
	else
		cmd->redirs = ft_realloc(cmd->redirs,
				(_len + 1) * P_SIZE, (_len + 2) * P_SIZE);
	cmd->redirs[_len] = ft_calloc(1, sizeof(t_redir));
	if (ft_strncmp(str, ">>", 2) == 0)
		cmd->redirs[_len]->op = APPEND;
	else if (ft_strncmp(str, "<<", 2) == 0)
		cmd->redirs[_len]->op = HEREDOC;
	else if (str[0] == '>')
		cmd->redirs[_len]->op = OUT;
	else
		cmd->redirs[_len]->op = IN;
	i = 1;
	if (cmd->redirs[_len]->op == APPEND || cmd->redirs[_len]->op == HEREDOC)
		++i;
	cmd->redirs[_len]->file = ft_strdup(str + i);
}

/*
 * Function:  get_name
 * --------------------------------------------------------------------------
 * Get name of command and put it on cmd->name
 * 
 * cmd: t_cmd pointer
 * str: string
 */
void	get_name(t_cmd *cmd, char *str)
{
	int	i;

	if (!cmd->name)
		cmd->name = ft_strdup(str);
	if (!cmd->args)
	{
		cmd->args = ft_calloc(2, sizeof(char *));
		cmd->args[0] = ft_strdup(str);
	}
	else
	{
		i = count_el((void **) cmd->args);
		cmd->args = ft_realloc(cmd->args, (i + 1) * P_SIZE, (i + 2) * P_SIZE);
		cmd->args[i] = ft_strdup(str);
	}
}
