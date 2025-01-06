# Project "Minishell - As beautiful as a shell"

Summary:
This project involves creating a simple shell in C, similar to a mini bash. You will learn a lot about processes and file descriptors, while implementing core functionalities for an interactive shell. It’s a hands-on exercise in managing commands, redirections, pipes, and environment variables.

Mandatory Part:

    Objective: Build a functional shell capable of executing commands, managing history, and handling redirections and pipes.
    Requirements:
        The shell should display a prompt and manage user input for commands.
        Support for redirections (<, >, <<, >>).
        Management of environment variables and expansion of $?.
        Handling of single and double quotes, with specific behaviors for each type.
        Implementation of built-in commands such as echo, cd, pwd, export, unset, env, and exit.
        Signal handling for ctrl-C, ctrl-D, and ctrl-\.
        Use of standard functions like fork, execve, pipe, and proper error handling.
        No excessive use of global variables, and signal handling should not interfere with main shell data structures.

Bonus Part (Optional):

    Objective: Add advanced features such as logical operators && and || with parenthesis for priority, and wildcard (*) expansion for the current working directory.
    Requirements: The bonus part will only be evaluated if the mandatory part is perfect, functioning without any issues.

This project provides a deep understanding of process management and interaction with the operating system through a custom shell, while adhering to specific design and performance rules.
