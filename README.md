*This project has been created as part of the 42 curriculum by lukrodri, alexfuen.*

# minishell

# Description

*minishell* is a small computer shell developed for the 42 `minishell` project.
It allows the user to interact with the computer by typing commands into the terminal.
For example :
```bash
echo "Hello world" >> file.txt
cat file.txt
```
Will output :
```bash
Hello world
```

### Key concepts

- Strict parsing and tokenization of input
- Memory management
- Signals and system calls
- Built-in functions
- Pipes and status codes

### External functions

* `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`.
* `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`.
* `fork`, `wait`, `waitpid`.
* `signal`.
* `exit`, `getcwd`, `chdir`, `stat`, `execve`.
* `dup`, `dup2`, `pipe`.
* `ioctl`.

### Libraries

* `libc`
* `libreadline`

## Team Information

| Member | 42 login | Role | Main responsibilities |
| --- | --- | --- | --- |
| Alexandre | `alexfuen` | Developer | built-in functions, lexer,  parser, signals
| Lukas | `lukrodri` | Developer | pipes, execution, redirections, heredocs

## Algorithm

```text
                            User
                             │
                             ▼
                    ┌─────────────────┐
                    │      Prompt     │ ◀───────────────────┐◀────────────────┐
                    └────────┬────────┘                     │                 │
                             │                              │                 │
                    ┌────────┴────────┐                     │                 │
                    │      Parser     │            ┌────────┴────────┐        │
                    └────────┬────────┘            │  Error message  |        │
                             │                     └────────┬────────┘        │        
                 ┌───────────┴───────────┐                  │                 │
                 │                       │                  │                 │
                 ▼                       ▼                  │                 │
       ┌─────────────────┐       ┌─────────────────┐        │                 │
       │      Valid      │       │     Invalid     │────────┘                 │
       └────────┬────────┘       └─────────────────┘                          │
                │                                                             │
                ▼                                                             │
       ┌─────────────────┐                                                    │
       │    While pipe:  │                                                    │
       │      exec       │◀──────┐                                            │
       └────────┬────────┘   ┌───┴──┐                                         │
                │            | Fork |                                         │
                │            └───┬──┘                                         │
                └────────────────┘                                            │
                │                                                             │
                │                                                             │
                ▼                                                             │          
       ┌─────────────────┐                                           ┌────────┴────────┐                                     
       |    Wait PID     |──────────────────────────────────────────▶|      Output     |
       └─────────────────┘                                           └─────────────────┘
```

---

# Instructions

## Requirements

The project requires:

- Make
- Clang Compiler

---

## Configuration

Clone the repository:

```bash
git clone <repository-url>
cd minishell
```

---

## Start the Application

Build with:

```bash
make
```
Then launch with:
```bash
./minishell
```

---

# Resources

Main documentation and references used during development:

- Main functions documentation — https://www.man7.org/linux/man-pages
- A tutorial to understand forking and pipes management — https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY
- An exhaustive tester made by a student from our campus — https://gitlab.com/nda-cunh/minishell_tester

## AI Usage

AI tools were used as a supplementary resource during the project, mainly for technical research, troubleshooting, reviewing edge cases, checking project requirements and assisting with documentation.
The team remained responsible for the technical decisions, implementation and final validation of the project.