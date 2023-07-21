/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 15:51:49 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/07/21 11:17:12 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_line(char *line, t_node **lst)
{
	int	i;
	int	start;
	char	*new;
	int		size;
	int		dq_start;
	int		sq_start;

	i = 0;
	while(line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			size = 1;
			new = ft_substr(line, i, (size_t)(size));
			printf("this is new string first if= \"%s\" and the char '%c'\n", new, line[i]);
			ft_add_back_list(lst, make_node(new, size, line[i], NORMAL));
			i++;
		}
		start = i;
		while (line[i] != '\0' && !(line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|' || line[i] == '\"' || line[i] == '\''))
		{
			i++;
		}
		if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			size = i - start;
			if (size != 0)
			{
				new = ft_substr(line, start, (size_t)(size));
				printf("this is new string in if= \"%s\" and the char '%c'\n", new, line[i]);
				ft_add_back_list(lst, make_node(new, size, WORD, NORMAL));
			}
			if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
			{
				size = 1;
				new = ft_substr(line, i, (size_t)(size));
				printf("this is new string in the same if= \"%s\" and the char '%c'\n", new, line[i]);
				ft_add_back_list(lst, make_node(new, size, line[i], NORMAL));
			}
		}
		else
		{
			if (line[i] == '\"')
			{
				dq_start = i;
				i++;
				while(line[i] != '\0' && line[i] != '\"')
					i++;
				if (line[i] == '\"')
					i++;
				size = i - dq_start;
				new = ft_substr(line, start, (size_t)(size));
				printf("this is string in double qoute= \"%s\" and the char '%c'\n", new, line[i]);
				ft_add_back_list(lst, make_node(new, size, line[dq_start], IN_DOUBLEQ));
				print_list(*lst);
				if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
				{
					size = 1;
					new = ft_substr(line, i, (size_t)(size));
					printf("this is new string after dq= \"%s\" and the char '%c'\n", new, line[i]);
					ft_add_back_list(lst, make_node(new, size, line[i], NORMAL));
				}
			}
			else if (line[i] == '\'')
			{
				sq_start = i;
				i++;
				while(line[i] != '\0' && line[i] != '\'')
					i++;
				if (line[i] == '\'')
					i++;
				size = i - sq_start;
				new = ft_substr(line, start, (size_t)(size));
				printf("this is string in single qoute= \"%s\" and the char '%c'\n", new, line[i]);
				ft_add_back_list(lst, make_node(new, size, line[sq_start], IN_SINGLEQ));
				print_list(*lst);
				if (line[i] == ' ' || line[i] == '>' || line[i] == '<' || line[i] == '|')
				{
					size = 1;
					new = ft_substr(line, i, (size_t)(size));
					printf("this is new string after sq= \"%s\" and the char '%c'\n", new, line[i]);
					ft_add_back_list(lst, make_node(new, size, line[i], NORMAL));
				}
			}
			//else if (line[i] != '\0')
			//for which case I have added the previous line?
			// it was for this "ls -l >"
			else
			{
				size = i - start;
				if (size == 0 && line[i] == '\0')
				{
					printf("I will get here for %d this\n", line[i]);
					break;
				}
				else
				{
					printf("this is the size in else %d\n", size);
					new = ft_substr(line, start, (size_t)(size));
					printf("this is new string in else = \"%s\" and the char '%d'\n", new, line[i]);
					ft_add_back_list(lst, make_node(new, size, WORD, NORMAL));
				}
			}
		}
		i++;
	}
	if (line[i] == '\0')
	{
		printf("its not it\n");
	}
	printf("this is the last result->");
	print_list(*lst);
	printf("we got out from here\n");
}

t_node	*make_node(char *str, int len, enum e_token type, enum e_situation state)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		exit(1);
	node->str = str;
	node->len = len;
	node->type = type;
	node->state = state;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_node	*ft_lastlist(t_node *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_back_list(t_node **lst, t_node *new)
{
	t_node	*current;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	current = ft_lastlist(*lst);
	current->next = new;
	current->next->next = NULL;
}

int	ft_sizelist(t_node *lst)
{
	int	count;
	t_node	*head;

	count = 0;
	if (!lst)
		return (0);
	head = lst;
	while (head != NULL)
	{
		head = head->next;
		count++;
	}
	return (count);
}

void	print_list(t_node *lst)
{
	if (!lst)
		return ;
	while (lst->next != NULL)
	{
		printf("str= %s, state= %u, ", lst->str, lst->state);
		printf("type= %d ,", lst->type);
		lst = lst->next;
	}
	printf("str= %s, state= %u ", lst->str, lst->state);
	printf("type= %d\n", lst->type);
}

char	*ft_readline(char *prompt)
{
	char	*line;
	t_node	*lst;
	char	*new;
	t_parser_list *p_list;

	p_list = NULL;
	
	lst = NULL;
	while(1)
	{
		printf("each time\n");
		free_llist(&p_list);
		free_tokens(&lst);
		line = readline(prompt);
		new = ft_strtrim(line, " ");
		if (!line || line[0] == '\0')
		{
			line = readline(prompt);
			new = ft_strtrim(line, " ");
		}
		else
		{
			printf("line = \"%s\"\n", line);
			printf("compare new and line = %d\n", strcmp(new, line));
			check_line(new, &lst);
			make_parser(&lst, &p_list);
			add_history(line);
			execution(&p_list);
		}
	}
	return (line);
}

void	free_tokens(t_node **lst)
{
	t_node *temp;

	while (*lst)
	{
		temp = (*lst);
		(*lst) = (*lst)->next;
		free(temp);
	}
}