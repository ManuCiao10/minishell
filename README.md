# `Minishell`
### As beautiful as a shell

This project is about creating a simple shell. Yes, your own little bash. 
You will learn a lot about processes and file descriptors. <br> `Version: 6` <br>
You can read the subject: [`minishell.en.pdf`](subject/minishell.en.pdf)

## Introduction

The existence of shells is linked to the very existence of IT. 
At the time, all developers agreed that communicating with a computer using aligned 1/0 switches was seriously irritating. 
It was only logical that they came up with the idea of creating a software to communicate with a computer using interactive lines of commands in a language somewhat close to the human language. 
Thanks to Minishell, you’ll be able to travel through time and come back to problems people faced when Windows didn’t exist.

## Mandatory part

Program name        | minishell
---------------     | ----------------------------
Turn in files       | Makefile, *.h, *.c
Makefile            | NAME, all, clean, fclean, re
Arguments           | 
External functs.    | • readline, rl_clear_history, rl_on_new_line <br> • rl_replace_line, rl_redisplay, add_history <br> • printf, malloc, free, write, access, open, read <br> • close, fork, wait, waitpid, wait3, wait4, signal <br> • sigaction, sigemptyset, sigaddset, kill, exit <br> • getcwd, chdir, stat, lstat, fstat, unlink, execve <br> • dup, dup2, pipe, opendir, readdir, closedir <br> • strerror, perror, isatty, ttyname, ttyslot, ioctl <br> • getenv, tcsetattr, tcgetattr, tgetent, tgetflag <br> • tgetnum, tgetstr, tgoto, tputs
Libft authorized    | Yes
Description         | Write a shell

Your shell should:

* Display a __prompt__ when waiting for a new command.
* Have a working __history__.
* Search and launch the right executable (based on the __PATH__ variable or using a relative or an absolute path).
* Not use more than __one global variable__. Think about it. You will have to explain its purpose.
* Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
* Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
* Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).

* Implement __redirections__:
◦ < should redirect input.
◦ > should redirect output.
◦ << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
◦ >> should redirect output in append mode.

* Implement __pipes__ (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.

* Handle __environment variables__ ($ followed by a sequence of characters) which should expand to their values.
* Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
* Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.

* In interactive mode:
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.

* Your shell must implement the following __builtins__:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
The readline() function can cause memory leaks. You don’t have to fix them. But that __doesn’t mean your own code, yes the code you wrote, can have memory leaks__.

```
You should limit yourself to the subject description. Anything that is not asked is not required.
If you have any doubt about a requirement, take __bash__ as a reference.
```

## Bonus Part 

Your program has to implement:
* && and || with parenthesis for priorities.
* Wildcards * should work for the current working directory.

```
The bonus part will only be assessed if the mandatory part is PERFECT. 
Perfect means the mandatory part has been integrally done and works without malfunctioning.
If you have not passed ALL the mandatory requirements, your bonus part will not be evaluated at all.
```
