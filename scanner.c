#include "lexer.h"

void	free_token_list(t_lexer data)
{
	t_token_list	tmp;
	t_token_list	tmp_to_free;

	tmp = data->head;
	tmp_to_free = tmp;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		free(tmp_to_free);
		tmp_to_free = tmp;
	}	  
}

void	update_lexer_data(t_lexer data, t_token_list token_node)
{
	if (data->head == NULL)
	{
		data->head = token_node;
		data->tail = token_node;
	}
	else
		data->tail = token_node;
}

void	add_token_node(t_lexer data, t_token_list token_node)
{
	t_token_list	tmp;

	if (tmp == NULL)
		return ;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = token_node;
	}
}

t_token_list	make_token_node(t_token token)
{
	t_token_list token_node;

	token_node = malloc(sizeof(t_token_list));
	if (token_node == NULL)
		return (NULL);
	token_node.token = token;
	token_node.next = NULL;
	return (token_node);
}

void	init_scanner(t_scanner scanner, const char *source)
{
	scanner.start = source;
	scanner.current = source;
}

void	init_lexer_data(t_lexer data)
{
	data->head = NULL;
	data->tail = NULL;
}
