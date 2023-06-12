/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:04:12 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/06/02 14:29:13 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_pipe(t_token *token)
{
	if (token->type == PIPE)
		return (1);
	return (0);
}

int	redir(t_token *token)
{
	if (token->type == INPUT_REDIR || token->type == OUTPUT_REDIR
		|| token->type == APPEND || token->type == HEREDOC)
		return (1);
	return (0);
}

int	redir_error(t_token *token)
{
	if (token->type == INPUT_REDIR
		|| token->type == APPEND || token->type == HEREDOC)
		return (1);
	return (0);
}

int	errors_in_tkn(t_list *copy)
{
	t_token	*t;
	t_list	*tokens;
	t_token	*n_tok;

	tokens = copy;
	if (!tokens)
		return (0);
	t = (t_token *)tokens->content;
	if ((ft_lstsize(tokens) == 1 && redir(t))
		|| (is_pipe(ft_lstlast(tokens)->content) || is_pipe(t)))
		return (1);
	while (tokens->next)
	{
		t = (t_token *)tokens->content;
		n_tok = (t_token *)tokens->next->content;
		if ((is_pipe(t) && is_pipe(n_tok)) || (redir(t) && redir(n_tok))
			|| (redir_error(t) && is_pipe(n_tok)) || (redir(t) && n_tok->exp
				&& (t->type == OUTPUT_REDIR || t->type == APPEND))
			|| (redir(t) && n_tok->type == SUB_EXPR)
			|| (t->type == SUB_EXPR && redir(n_tok))
			|| (t->type == PIPE && n_tok->type == SUB_EXPR))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

void	convert_str_to_arr(void *step_ptr)
{
	t_list	*arg_list;
	size_t	i;
	size_t	list_size;
	t_exec	*step;

	step = step_ptr;
	if (step->cmd == NULL)
		return ;
	arg_list = step->cmd->args;
	list_size = ft_lstsize(arg_list);
	step->cmd->arg_arr = ft_calloc(list_size + 1, sizeof(char *));
	if (step->cmd->arg_arr == NULL)
		exit(1);
	i = 0;
	while (arg_list != NULL)
	{
		if (arg_list->content == NULL)
			step->cmd->arg_arr[i] = NULL;
		else
			step->cmd->arg_arr[i] = ft_strdup(arg_list->content);
		arg_list = arg_list->next;
		i++;
	}
	ft_lstclear(&step->cmd->args, free);
	step->cmd->arg_arr[i] = NULL;
}
