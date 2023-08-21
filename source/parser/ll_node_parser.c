/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_node_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 11:17:04 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/08/21 18:34:15 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pn	*make_node_parser(t_node *token)
{
	t_pn	*node;

	node = (t_pn *)malloc(sizeof(t_pn));
	if (node == NULL)
		exit(1);
	if (token == NULL)
		node->str = NULL;
	else
		node->str = token->str;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_pn	*ft_lastlist_parser(t_pn *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_back_list_parser(t_pn **lst, t_pn *new)
{
	t_pn	*current;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	current = ft_lastlist_parser(*lst);
	current->next = new;
	current->next->next = NULL;
}

int	ft_sizelist_parser(t_pn **lst)
{
	int		count;
	t_pn	*node;

	count = 0;
	if (!lst || !*lst)
		return (0);
	node = *lst;
	while (node != NULL)
	{
		node = node->next;
		count++;
	}
	return (count);
}

void	free_list(t_pn *lst)
{
	t_pn	*temp;

	if (!lst)
		return ;
	printf("1\n");
	while (lst)
	{
		temp = lst;
		lst = lst->next;
		free(temp);
	}
}

void	print_list_parser(t_pn *lst)
{
	if (!lst)
		return ;
	while (lst->next != NULL)
	{
		printf("str= %s, ", lst->str);
		lst = lst->next;
	}
	printf("str= %s\n", lst->str);
}
