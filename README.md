# Cub3d

## Resume

### Goal : create a 3d game with mlx library using raycasting manually.

### Library && Function autorized

```c

# include <stdio.h>
int printf(const char * restrict format, ...);
void perror(const char *s);


# include <stdlib.h>
void * malloc(size_t size);
void free(void *ptr);
void exit(int status);


# include <unistd.h>
ssize_t read(int fildes, void *buf, size_t nbyte);
ssize_t write(int fildes, const void *buf, size_t nbyte);
int     close(int fildes);

# include <string.h>
char *strerror(int errnum);

# include <fcntl.h>
int		open(const char *path, int oflag, ...);

# include <math.h>


```

### Subject

1.  General :

    > - blabla
    >
    > - blabla2

### Program

1.  Parsing :

        ```bash
        # managed on err_forbidden_char()
        bash-3.2$ ;
        bash: syntax error near unexpected token`;'
        ```

2.  Raycasting :


3.  move event :

    3-1. ajust to do not enter in the wall

        ```c

        //prototype
        game->player->x = game->player->x + (game->player->dir_x / 10);

        //to
        game->player->x = game->player->x + (game->player->dir_x / 9);

        //example
        void	move_player(int code, t_game *game)
        {
            if (code == KEY_W)
            {
                game->player->x = game->player->x + (game->player->dir_x / 9);
                game->player->y = game->player->y + (game->player->dir_y / 9);
            }
            else if (code == KEY_S)
            {
                game->player->x = game->player->x - (game->player->dir_x / 9);
                game->player->y = game->player->y - (game->player->dir_y / 9);
            }
            else if (code == KEY_A)
            {
                game->player->x = game->player->x - (game->player->dir_y / 9);
                game->player->y = game->player->y + (game->player->dir_x / 9);
            }
            else if (code == KEY_D)
            {
                game->player->x = game->player->x + (game->player->dir_y / 9);
                game->player->y = game->player->y - (game->player->dir_x / 9);
            }
        }
        ```


### Theory

### ETC

- Makefile:

### Reference

```

```
