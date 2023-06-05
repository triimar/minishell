
struct s_parser
{
	struct s_ast *root;
	struct s_ast *current;
};

struct s_stdin_redirection
{
	bool	is_heredoc;
	char	*name;
	struct s_stdin_redirection *next;
};

struct s_ast
{
	void			*content;
	struct s_ast	*left;
	struct s_ast	*right;
};

struct s_ast_content
{
	struct s_stdin_redirection	*stdin_redirect;
	struct s_stdout_redirection	*stdout_redirect;
	char **assignment; // linked list of token
	char **cmd;
};

int	parser_complete_command(struct s_parser *parser, struct token_list *tokens)
{
	if (parser_command(parser, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parser_pipe(parser, tokens) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	if (parser_complete_command(parser, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int parse_command(struct s_parser *parser, struct token_list *tokens)
{
	// do something to parser
	// make the parser logic
}