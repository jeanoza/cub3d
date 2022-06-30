# Minishell

## Resume

### Goal : create a shell like bash shell

### Library && Function autorized

```c

# include <stdio.h>
int printf(const char * restrict format, ...);
void perror(const char *s);
char * strerror(int errnum);


# include <stdlib.h>
void * malloc(size_t size);
void free(void *ptr);
void exit(int status);
char *getenv(const char *name);


# include <unistd.h>
// functions used in pipex project
ssize_t read(int fildes, void *buf, size_t nbyte);
ssize_t write(int fildes, const void *buf, size_t nbyte);
int		access(const char *path, int mode); // verify access to file
int		dup(int fildes); // duplicate fd
int		dup2(int fildes, int fildes2);
int		execve(const char *path, char *const argv[], char *const envp[]); // execute file
pid_t	fork(void); // create new process
int		pipe(int fildes[2]);
int		unlink(const char *path); // this is for manage heredoc.

// new functions: chdir, getcwd, isatty, ttyname, ttyslot
int chdir(const char *path);
char *getcwd(char *buf, size_t size);
/* ttyslot() : https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/ttyslot.3.html
 * Legacy function, i don't know when i have to use this...
 * function returns the unit number of the device file if found;
 * otherwise, the value zero is returned.
 */
int ttyslot(void);

# include <string.h>
char *strerror(int errnum);

# include <fcntl.h>
int		open(const char *path, int oflag, ...);

# include <sys/wait.h>
pid_t	wait(int *stat_loc);
pid_t	waitpid(pid_t pid, int *stat_loc, int options);

# include <sys/stat.h>
int stat(const char *path, struct stat *buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *path, struct stat *buf);

# include <signal.h>
//signal, sigaction, sigemptyset, sigdelset, kill

# include <dirent.h>
//opendir, readdir, closedir

# include <sys/ioctl.h>
//ioctl

# include <termios.h>
// tcsetattr, tcgetattr

# include <curses.h>
# include <term.h>
//tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

# include <readline/readline.h>
# include <readline/history.h>
// readline, rl_clear_history, rl_on_new_line, rl_replace_line
// rl_redisplay, add_history



```

### Subject

1.  General :

    > - Show a prompt wating new command
    >
    > - Have history
    >
    > - Find a good executable (based on RELATIVE_PATH | ABSOLUTE_PATH)
    >
    > - ONE global variable!! - TO JUSTIFY in correction
    >
    > - Ignore quotes "incomplete"(ex: \'bla, \"bla) and special character non-requested(ex: \\, ;)

2.  Manage quotes :

    > - Single quote (\') : don't interprete meta-character
    >
    >   ex: echo 'hello $PATH' => hello $PATH
    >
    > - Double quote (\") : only interprete meta-character with \$(dollar)
    >
    > - Back quote(\`, backtick) : don't have to manage (out of subject)
    >
    >   if the tester try to put 0 beacause of this, we have to insist that is 'hors sujet'

3.  Redirection :

    > - `<` : input(STDIN)
    >
    > - `>` : output(STDOUT) - create file(or `OVERRIDE` file if the file exist)
    >
    > - `<<` : receive `LIMITER` and read user input until input which contains this limiter.
    >
    > - `>>` : output(STDOUT) - create file(or `APPEND` file if the file exist)

4.  Pipe(`|`): Each command(STDOUT) of pipeline must be connected to STDIN of next pipeline thanks to PIPE(\|)

5.  Env variable : `\$` + `NAME_OF_VARIABLE`

    - liste of env var: `printenv` ou `env` in shell

    - ex:

      ```bash
      bash-3.2$ $PATH
      bash: /opt/homebrew/bin:/opt/homebrew/sbin:/Library/Frameworks/Python.framework/Versions/3.8/bin:/Library/Frameworks/Python.framework/Versions/3.9/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Library/Apple/usr/bin:/opt/homebrew/bin:/opt/homebrew/sbin:/Library/Frameworks/Python.framework/Versions/3.8/bin:/Library/Frameworks/Python.framework/Versions/3.9/bin: No such file or directory

      bash-3.2$ export HELLO
      bash-3.2$ export HELLO=hello
      bash-3.2$ HELLO
      bash: HELLO: command not found
      bash-3.2$ echo HELLO
      HELLO
      bash-3.2$ echo $HELLO
      hello

      bash-3.2$ printenv
      [...]
      HELLO=hello
      [...]
      ```

6.  Gestion of signal: `$?`

    - status of last pipeline's STDOUT

    - Maybe, I have to use global variable for this status.

    - Because :

      - This variable will be shared between processors.
      - Global variable will be deleted at the last moment in program.

        => To justify this choice in correction.

7.  Gestion of process

    - `ctrl - C` : show new prompt - clear line and put new empty line(with readline()!)
    - `ctrl - D` : quit shell (kill process when `ONLY line is empty`) after show 'exit' in shell
    - `ctrl - \` : do nothing.

8.  Implementation of builtins functionality

    - `echo` : with `-n` flag
    - `cd` : ONLY relative path and absolute path

      - relative path : ../(parent dir) or ./(current dir)
      - absolute path : /<name_of_dir1>/<name_of_dir2>/...

      => Don't have to manage short cut of shell like tilde(`~`)

    - Without any flag:
      - `pwd`
      - `export`
      - `unset`
      - `env`
      - `exit`

:warning:Attention

    - `readline` can cause memory leaks.

    - So, if memory leak comes ONLY from `readline`, it's okay!

### Program

0.  Adaptation of `char **env`(if necessary) && Put it in `struct s_minishell`

1.  Parsing : everytime receive command line by prompt call

    - Read line with `readline()` && save this cmd with `add_history()`

    - Operator to manage : `<`, `>`, `<<`, `>>`, `|`

    1.  Error case: print `error_msg` && update `g_exit_status` which will be sent by `exit()` when quit shell

        1-1. Stupid case : not required in subject

        1-1-1. Forbidden characters : ';' | '\'

        ```bash
        # managed on err_forbidden_char()
        bash-3.2$ ;
        bash: syntax error near unexpected token`;'
        ```

        1-1-2. End by operator

        ```bash
        # managed on err_end_by_op()
        $> |
        bash: syntax error near unexpected token `new line'
        $> <
        bash: syntax error near unexpected token `new line'
        $> >
        bash: syntax error near unexpected token `new line'
        ```

        1-1-3. Multiple chevron or multiple pipe (`<<<` | `>>>` | '||')

        ```bash
        # managed on err_multiple_op()
        $> ls <<< ls
        bash: syntax error near unexpected token `<'

        $> ls >>> ls
        bash: syntax error near unexpected token `>'

        $> ls || ls
        bash: syntax error near unexpected token `>'
        ```

        1-1-4. Space between operator (`OP1 OP2` ex: `< <`, `< |`, ...)

        ```bash
        # bash: syntax error near unexpected token `OP2'
        # managed on err_space_btw_op()
        bash-3.2$ ls < < ls
        bash: syntax error near unexpected token`<'
        ```

        1-1-5. Operator mixed (`OP1OP2` ex: `|<`, `>|`, ...)

        ```bash
        # managed on err_mix_op()
        bash-3.2$ ls <| ls
        bash: syntax error near unexpected token`|'
        ```

    1-2. Quotes not closed

        - To manage multi-line is not required in this subject

        - BUT, if there is(are) quote between other quote, it must be treated like a `simple character`.

    1-2-1 simple cases:

        ```bash
        # managed on err_quote()
        $> ls '-al
        bash: syntax error: Not closed quote(`'')
        $> ls "-al
        bash: syntax error: Not closed quote(`"')
        ```

    1-2-1 quote(s) between other quotes cases:

        ```bash
        #case 1
        bash-3.2$ ls "'-al'"
        ls: '-al': No such file or directory

        #case 2
        bash-3.2$ ls '"-al"'
        ls: "-al": No such file or directory

        #case 3
        bash-3.2$ ls "-al'"
        ls: invalid option -- '
        usage: ls [-@ABCFGHILOPRSTUWabcdefghiklmnopqrstuvwxy1%,] [--color=when] [-D format] [file ...]

        ```

2.  Execute

### Theory

- stdlib

  ```c
  #include <stdlib.h>

  char *getenv(const char *name);

  int main()
  {
    char *s = getenv("PATH");

    printf("%s", s);
  }
  // /opt/homebrew/bin:/opt/homebrew/sbin:/Library/Frameworks/Python.framework/Versions/3.8/bin:/Library/Frameworks/Python.framework/Versions/3.9/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Library/Apple/usr/bin:/opt/homebrew/bin:/opt/homebrew/sbin:/Library/Frameworks/Python.framework/Versions/3.8/bin:/Library/Frameworks/Python.framework/Versions/3.9/bin%

  ```

- unistd.h

  - fork, wait

    ```c
    /*
     * recap of pipex!
     * this code is a example to explain the mecanism simplified
     * in which shell execute programs.
     */
    #include <unistd.h> //fork
    #include <stdio.h> //perror
    #include <stdlib.h>//exit
    #include <sys/wait.h>//wait
    #include <string.h> //strcat

    int main(int ac, char **av, char **env)
    {
      pid_t pid;

      if (ac > 1)
      {
        switch (pid = fork()) {
          case -1:
            perror("fork failed");
            exit (1);
            break;
          case 0:
            printf("** exec (child process)\n");
            char path[100] = "/bin/";
            strcat(path, av[1]); // ex: /bin/ls
            execve(path, av + 1, env);
            perror("exec failed");
            exit (1);
            break;
          default:
            printf("** wait && exit (parent process)\n");
            wait((int *)0);
            printf("cmd(%s) completed\n", av[1]);
            exit (0);
        }
      }
    }

    ```

  - chdir, getcwd

    ```c
    #include <unistd.h>
    #include <stdio.h>

    int chdir(const char *path);
    char * getcwd(char *buf, size_t size);

    int main(int ac, char **av, char **env)
    {
      char S[255];

      chdir("/Users/kyubongchoi");
      getcwd(S,255);
      printf("Repertoire courante = %s\n",S);
      //Repertoire courante = /Users/kyubongchoi
      return (0);
    }

    ```

  - isatty, ttyname, ttyslot

    ```c
    #include <stdio.h> //printf, perror
    #include <unistd.h>

    int isatty(int fd);
    char *ttyname(int fd);
    int ttyslot(void);

    int main(void)
    {
      char *ret;

      ret = ttyname(STDIN_FILENO);

      if (ret == NULL)
        perror("ttyname() error");
      else
      {
        printf("isatty: %d\n", isatty(STDIN_FILENO));//isatty: 1
        printf("ttyname: %s\n", ret); //ttyname: /dev/ttys003
        printf("ttyslot: %d\n", ttyslot()); // ttyslot: 0
      }
      return (0);
    }
    ```

- sys/stat.h

  ```c
  struct stat {
      dev_t     st_dev;      /* ID du périphérique contenant le fichier */
      ino_t     st_ino;      /* Numéro inœud */
      mode_t    st_mode;     /* Protection */
      nlink_t   st_nlink;    /* Nb liens matériels */
      uid_t     st_uid;      /* UID propriétaire */
      gid_t     st_gid;      /* GID propriétaire */
      dev_t     st_rdev;     /* ID périphérique (si fichier spécial) */
      off_t     st_size;     /* Taille totale en octets */
      blksize_t st_blksize;  /* Taille de bloc pour E/S */
      blkcnt_t  st_blocks;   /* Nombre de blocs alloués */
      time_t    st_atime;    /* Heure dernier accès */
      time_t    st_mtime;    /* Heure dernière modification */
      time_t    st_ctime;    /* Heure dernier changement état */
  };
  ```

  - stat(), fstat(), lstat()

    ```c
    #include <sys/stat.h>
    #include <stdio.h>
    #include <fcntl.h>

    int stat(const char *path, struct stat *buf);
    int fstat(int fd, struct stat *buf);
    int lstat(const char *path, struct stat *buf);

    int main()
    {
      struct stat _buf;
      struct stat _buf_f;
      struct stat _buf_l;

      int _stat = stat("./testdir/fe", &_buf); // 0 if sucess, else -1
      int _fstat = fstat(open("./testdir/fe", O_RDONLY), &_buf_f); // 0 if sucess, else -1
      int _lstat = lstat("./testdir/fe", &_buf_l); // 0 if sucess, else -1

      printf("_stat(return:%d)\n", _stat); // 0
      printf("\t-size:%lld\n", _buf.st_size); // 7

      printf("_fstat(return:%d)\n", _fstat); // 0
      printf("\t-size:%lld\n", _buf_f.st_size); // 7

      printf("_lstat(return:%d)\n", _lstat); // 0
      printf("\t-size:%lld\n", _buf_l.st_size); // 7

      return (0);
      // _stat(return:0)
      //         -size:7
      // _fstat(return:0)
      //         -size:7
      // _lstat(return:0)
      //         -size:7
    }
    ```

  - readline/readline.h, readline/history.h

    - readline(), add_history()

      ```c

      #include <stdio.h>
      #include <readline/readline.h>
      #include <readline/history.h>


      //must compile with -lreadline
      //=> ex) gcc readline.c -lreadline
      int main(int ac, char **av)
      {
          char *line;

          while (1)
          {
              line =readline("$>");
              add_history(line); // save and able to call with `key_up`
              printf("line:%s\n", line);
          }
          return (0);
      }

      ```

  - exit code(status): https://www.cyberciti.biz/faq/linux-bash-exit-status-set-exit-statusin-bash/

    - 0: Success
    - 1: Operation not permitted
    - 2: No such file or directory
    - 4: Interrupted system call
    - 13: Permission denied
    - 130: Owner died
    - 131: State not recoverable

  - waitpid : https://linux.die.net/man/2/waitpid

    - WNOHANG

      ```
      If WNOHANG was specified in options and there were no children in a waitable state,
      then waitid() returns 0 immediately and the state of the siginfo_t structure pointed
      to by infop is unspecified. To distinguish this case from that where a child was in a waitable state,
      zero out the si_pid field before the call
      and check for a nonzero value in this field after the call returns.
      ```

    - Returns value

      ```
      wait(): on success, returns the process ID of the terminated child;
      on error, -1 is returned.

      waitpid(): on success, returns the process ID of the child whose state has changed;
      if WNOHANG was specified and one or more child(ren) specified by pid exist,
      but have not yet changed state, then 0 is returned. On error, -1 is returned.

      waitid(): returns 0 on success or if WNOHANG was specified and no child(ren)
      specified by id has yet changed state;
      on error, -1 is returned.
      Each of these calls sets errno to an appropriate value in the case of an error.
      ```

### ETC

- Makefile:

  - diff between `:=` and `=`

    - := : simple assignment (once calculated, use this value all the file)
    - = : recursive assignment (every time re-calculated, when use)

  - usage of `if` statement
    ```Makefile
    [...]
    OS_NAME 	:= $(shell uname -m)
    ifeq ($(OS_NAME),arm64)
      RL_INC 	:= -I /opt/homebrew/opt/readline/include
      RL_LIB	:= -L /opt/homebrew/opt/readline/lib
    endif
    [...]
    ```

- ftw.h

  - Although i can't use this lib, i put this because of its structure pretty interesting.

  - We can create a function which use a pointer of function like this.

    ```c

    #include <stdio.h>
    #include <ftw.h>

    int fn (const char *name, const struct stat *status, int type)
    {
      if (type == FTW_NS) return (0);
      if (type == FTW_F) printf("%s\t0%o\n", name, status->st_mode&0777); //%o is unsigned
      // if (type == FTW_F) printf("%-30s\t0%3o\n", name, status->st_mode&0777);
      // origin code...(it manage espace to print more prettily in console)
      else printf("%-30s*\t0%3o\n", name, status->st_mode&0777); // * is to inform that is dir.

      return (0);
    }

    int	main(void)
    {
      ftw("./practices/fct_main/testdir", fn, 1);
      return (0);
    }
    // ./practices/fct_main/testdir  * 0755
    // ./practices/fct_main/testdir/fe 0644
    // ./practices/fct_main/testdir/ediohwf    0644
    ```

### Reference

```

```
