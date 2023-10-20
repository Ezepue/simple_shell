# Simple Shell Project

## Description
This is a simple UNIX command interpreter implemented in C. The shell works like a traditional shell (e.g., bash and sh), where you can type commands and run them to get results.

## Features
- Our shell displays a prompt when waiting for the user to type a command.
- Handles command lines with arguments.
- Handles the `exit` and `env` built-ins commands.
- Custom exit status.

## Installation
Clone this repository to get the source code on your local machine. Here is an example of how you can do this:
```bash
git clone https://github.com/username/simple_shell.git
```

## Compilation
To compile, use the following command:
```
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```
## Usage
After compilation, the shell can be run with:

```
./hsh
```

# Testing
You can test the shell with interactive mode:
```
$ ./hsh
($) /bin/ls
hsh main.h shell_main.c env.c
($)
($) exit
$
```
And also with non-interactive mode:

```
$ echo "/bin/ls" | ./hsh
hsh main.h shell_main.c env.c
$
```
