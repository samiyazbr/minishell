# minishell

A Unix shell clone written in C, implementing many core features of bash. This project was developed as part of the 42 school curriculum.

## Features
- Custom interactive prompt (`minishell😃$`)
- Command parsing and execution
- Built-in commands: `echo`, `cd`, `pwd`, `env`, `export`, `unset`, `exit`
- Environment variable management
- Input/output redirection (`>`, `<`, `>>`, `<<`)
- Pipes (`|`)
- Heredoc support
- Signal handling (Ctrl+C, Ctrl+D, etc.)
- Command history (via readline)

## Directory Structure
- `src/`        – Core shell logic
- `builtin/`    – Built-in command implementations
- `execution/`  – Command execution, redirection, and piping
- `parse/`      – Parsing logic
- `tokens/`     – Tokenization and variable expansion
- `libft/`      – Custom standard library functions
- `include/`    – Header files

## Build Instructions
Requires `gcc` and the `readline` library.

```sh
make
```

## Usage
After building, run:

```sh
./minishell
```

Type commands at the `minishell😃$` prompt. Use built-in commands or any executable available in your `$PATH`.

## Authors
- bpla-rub
- szubair

---
This project is for educational purposes and mimics basic shell behavior. Contributions and suggestions are welcome!
    