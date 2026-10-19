*This project has been created as part of the 42 curriculum by lukrodri, alexfuen.*

## Description
Minishell is a project that involves creating a simple shell, functioning like your very own little Bash.

The shell incorporates the following main features:
* Displays a prompt while waiting for new commands.
* Maintains a working history.
* Executes commands by finding the correct executable using the `PATH` variable, absolute paths, or relative paths.
* Handles single quotes (`'`), which prevent the interpretation of meta-characters.
* Handles double quotes (`"`), which prevent the interpretation of meta-characters except for the dollar sign (`$`).
* Implements redirections, including `<` for input , `>` for output , `<<` for heredoc , and `>>` for output in append mode.
* Supports pipes (`|`), which connect the output of one command to the input of the next.
* Expands environment variables to their respective values.
* Expands `$?` to the exit status of the most recently executed foreground pipeline.
* Handles interactive signals appropriately: `ctrl-C` displays a new prompt, `ctrl-D` exits the shell, and `ctrl-\` does nothing.
* Implements the built-in commands: `echo` (with the `-n` option), `cd` (relative or absolute path), `pwd`, `export`, `unset`, `env`, and `exit`.

Memory leaks are properly managed throughout the implementation, except for potential leaks caused internally by the `readline()` function itself.

## Instructions
To compile and run the project, the standard `Makefile` rules apply:
* Run `make` to compile the source code.
* Once compiled, launch the program by executing `./minishell`.
* Other available `Makefile` rules include `clean`, `fclean`, and `re`.

## Resources

Resources for this project were : 

- https://man7.org/linux/man-pages/ - linux official man
- https://linuxize.com/post/bash-heredoc/ - a bief course to understand heredocs

The allowed external functions used to construct this shell include:
* `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`.
* `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`.
* `fork`, `wait`, `waitpid`, `signal`.
* `exit`, `getcwd`, `chdir`, `stat`, `execve`.
* `dup`, `dup2`, `pipe`.
* `perror`, `ioctl`.
