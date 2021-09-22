# Pipex

Rank: Rank 2
Topic: Unix logic

Summary :

This project is the discovery in detail and by programming of a UNIX mechanism that you already know.

Warnings :

- [ ]  Norm
- [ ]  The functions shouldn't quit unexpectedly
- [ ]  Memory leaks
- [x]  Makefile and compilation flags
- [x]  Rules $(NAME), all, clean, fclean re
- [ ]  Rule bonus if the bonus are done
- [x]  Use libft
- [x]  The executable name must be pipex

Objectives :

- Your objective is to code the Pipex program. It should be executed in this way : 
(file1 and file2 are file names, cmd1 and cmd2 are shell commands with their parameters)

```bash
./pipex file1 cmd1 cmd2 file2
```

- The execution of the pipex program should do the same as the next shell command :

```bash
< file1 cmd1 | cmd2 > file2
```

- You have to handle errors sensitively. In no way can your program quit unexpectedly (Segmentation fault, bus error, double free, etc). If you are unsure, handle the errors like the shell **command < file1 cmd1 | cmd2 > file2**.

Examples :

Allowed functions :

- access : Check user's permissions for a file

```c
int access(const char *pathname, int mode);
```

- open : Open and possibly create a file

```c
int open(const char *pathname, int flags);
```

- unlink : Delete  a name from the filesystem.  If that name was the last link to a file and no processes have the file open, the file is deleted and the space it was using is made available for reuse.

```c
int unlink(const char *pathname);
```

- close : Close a file descriptor

```c
int close(int fd);
```

- read : Read from a file descriptor

```c
ssize_t read(int fd, void *buf, size_t count);
```

- write: Write to a file descriptor

```c
ssize_t write(int fd, const void *buf, size_t count);
```

- malloc : Allocate dynamic memory

```c
void *malloc(size_t size);
```

- waitpid : Wait for process to change state

```c
pid_t waitpid(pid_t pid, int *wstatus, int options);
```

- wait : suspends execution of the calling thread until one of its children terminates.

```c
pid_t wait(int *wstatus);
```

- free : Free dynamic memory

```c
void free(void *ptr);
```

- pipe : Create pipe

```c
int pipe(int pipefd[2]);
```

- dup : Duplicate a file descriptor, using the lowest-numbered unused fd

```c
int dup(int oldfd);
```

- dup2 : The dup2() system call performs the same task as dup(), but instead of using the lowest-numbered  unused  file descriptor, it uses the file descriptor number specified in newfd.

```c
int dup2(int oldfd, int newfd);
```

- execve : Execute program

```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

- fork : create a child process

```c
pid_t fork(void);q
```

- perror : Print a system error message

```c
void perror(const char *s);
```

- strerror : Return string describing error number

```c
char *strerror(int errnum);
```

- exit : cause normal process termination

```c
void exit(int status);
```

Ressource utile : [Conference Redirection et Pipe 42SH](https://www.youtube.com/watch?v=ceNaZzEoUhk)

[https://www.youtube.com/watch?v=ceNaZzEoUhk](https://www.youtube.com/watch?v=ceNaZzEoUhk)

We can open a file with the function open(), it returns a file descriptor.

dup() is a function who can duplicates a file descriptor.

dup2() makes a copy of a file descriptor on the specified file descriptor.

We can close a file descriptor with the function close().

 

FD 0 : Standard input

FD 1 : Standard output

FD 2 : Standard error

Functions on the file descriptors :

At the begining we can open the file test and save the file descriptor into an int variable.

```c
int fd;

fd = open("test", O_RDONLY);
```

The file descriptor will be the smallest fd available, so fd = 3. 

We can duplicate the link with the dup() function, dup_fd = 4.

We will not use the fd 3 anymore, so we can close it. Now the dup_fd always link to the same file.

```c
int fd;
int dup_fd;

fd = open("test", O_RDONLY);
dup_fd = dup(fd);
close(fd);
```

dup2() creates a copy of a file descriptor and we can specify a value to the file descriptor.

```c
dup2(fd, 1);
```

The file descriptor 1 will be a copy of the file descriptor fd.

If the file descriptor we want to use as a new fd is already used, it's closed. It's the same as :

```c
close(destination)
dup2(source, destination)
```

The redirection we want to do :

```bash
#On veut executer echo a et rediriger le resultat dans le fichier test. 
echo a > test
```

Redirection simply means capturing output from a file, command, program, script, or even code block within a script and sending it as input to another file, command, program, or script.

echo is a shell command and a its parameter. It's an argv. When this command is execute, the output will be print on the fd 1, the standard output.

>  test is the redirection.

Usualy, the output of the buidin echo a will be displayed in the standard output, FD 1. 

If we create a redirection, we need to destroy it after the use. 

We want to execute the command echo a and put the output into the test file.

We also want that the fd of the standard output redirect to the test file. 

We need to restore the fd 1, so we need to do a copy. 

```c
int stdout_bckp;

stdout_bckp = dup(1);
```

We need to open the test file.

```c
int stdout_bckp;
int fd;

stdout_bckp = dup(1);
fd = open("test", O_RDONLY);
```

The dup2() function helps us to redirect the fd to the standard output. We can also close the fd.

```c
int stdout_bckp;
int fd;

stdout_bckp = dup(1);
fd = open("test", O_RDONLY);
dup2(fd, 1);
close(fd);
//Execute the command here
```

After that we want to restore the stdout.

```c
int stdout_bckp;
int fd;

stdout_bckp = dup(1);
fd = open("test", O_RDONLY);
dup2(fd, 1);
close(fd);
ft_putstr_fd("Hello World !\n", 1);
dup2(stdout_bckp, 1);
close(stdout_bckp);
```