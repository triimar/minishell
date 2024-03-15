# minishell - imitating bash
Project realized in co-operation with [Eunsol Kim](https://github.com/euns-kim).
### Overview
Minishell is about creating a simple shell. It displays a prompt when waiting a new command, has a working history and launches the right executable based on the PATH variable using a relative or an absolute path.
It does not interpret unclosed quotes or special characters like backslash or semicolon.\
<br>
Implemented are:
- `<` input redirection
- `>` output redirection
- `<<` heredoc
- `>>` output redirection in append mode
- `|` pipes
- `$` followed by a sequence of characters - expands to the value of the requested environmental variable
- `?$` exit status of the most recently executed foreground pipeline
- `ctrl-C`, `ctrl-D` and `ctrl-\` behavour like bash  
<br>

Also implemented are the following builtins:
- `echo -n`
- `cd` with only a relative or absolute path
- `pwd`
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no arguments
<br>

### Running the Program(s)
Just lauch it and have fun. `Ctrl-D` to exit.
