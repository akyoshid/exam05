#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data {
    int width;
    int height;
    int iterations;
    char *command;
    char **map;
} t_data;

void ft_putstr(char *s) {
    for (int i = 0; s[i] != '\0'; ++i)
        putchar(s[i]);
}

// Success: return 0
// Failure: return -1
int check_args(int argc, char **argv, t_data *d) {
    if (argc != 4) {
        ft_putstr("Error\nUsage: ./life width height iterations\n");
        return -1;
    }
    d->width = atoi(argv[1]);
    if (d->width <= 0) {
        ft_putstr("Error\nUsage: width must be a number greater than 0\n");
        return -1;
    }
    d->height = atoi(argv[2]);
    if (d->height <= 0) {
        ft_putstr("Error\nUsage: height must be a number greater than 0\n");
        return -1;
    }
    d->iterations = atoi(argv[3]);
    if (d->iterations < 0) {
        ft_putstr("Error\nUsage: iterations must be a number greater than or equal to 0\n");
        return -1;
    }
    return 0;
}

// Success: return 0
// Failure: return -1
int get_command(t_data *d) {
    ssize_t read_ret;
    int i = 0;
    int alloc_count = 0;
    while (1) {
        if ((i + 1) / 64 == alloc_count) {
            alloc_count++;
            char *tmp = realloc(d->command, alloc_count * 64);
            if (tmp == NULL) {
                ft_putstr("Error\nrealloc: failed to allocate memory\n");
                free(d->command);
                return -1;
            } else {
                d->command = tmp;
            }
        }
        read_ret = read(0, d->command + i, 1);
        if (read_ret == 0) {
            d->command[i] = '\0';
            return 0;
        } else if (read_ret == -1) {
            ft_putstr("Error\nread: failed to read\n");
            free(d->command);
            return -1;
        }
        i++;
    }
}

// Success: return a pointer to allocated memory
// Failure: return NULL
char **alloc_map(t_data *d) {
    char **tmp = calloc(d->height + 1, sizeof(char *));
    if (tmp == NULL) {
        ft_putstr("Error\ncalloc: failed to allocate memory\n");
        return NULL;
    }
    for (int i = 0; i < d->height; ++i) {
        tmp[i] = calloc(d->width + 1, sizeof(char));
        if (tmp[i] == NULL) {
            ft_putstr("Error\ncalloc: failed to allocate memory\n");
            for (int j = 0; i < j; ++j)
                free(tmp[j]);
            free(tmp);
            return NULL;
        }
        for (int j = 0; j < d->width; ++j)
            tmp[i][j] = ' ';
    }
    return tmp;
}

void free_map(t_data *d) {
    for (int i = 0; i < d->height; ++i)
        free(d->map[i]);
    free(d->map);
}

void print_map(t_data *d) {
    for (int i = 0; i < d->height; ++i) {
        ft_putstr(d->map[i]);
        putchar('\n');
    }
}

void exec_command(t_data *d) {
    int y = 0;
    int x = 0;
    bool write_mode = false;
    for (int i = 0; d->command[i] != '\0'; ++i) {
        if (d->command[i] == 'x') {
            if (write_mode == true)
                write_mode = false;
            else
                write_mode = true;
        } else if (d->command[i] == 'w' && y > 0) {
            y--;
        } else if (d->command[i] == 'a' && x > 0) {
            x--;
        } else if (d->command[i] == 's' && y < d->height - 1) {
            y++;
        } else if (d->command[i] == 'd' && x < d->width - 1) {
            x++;
        }
        if (write_mode == true)
            d->map[y][x] = '0';
    }
}

// Success: return 0
// Failure: return -1
int init_map(t_data *d) {
    d->map = alloc_map(d);
    if (d->map == NULL) {
        free(d->command);
        return -1;
    }
    exec_command(d);
    free(d->command);
    return 0;
}

bool can_survive(t_data *d, int i, int j) {
    int alive_neighbor = 0;

    if (i > 0) {
        if (j > 0 && d->map[i - 1][j - 1] == '0')
            alive_neighbor++;
        if (d->map[i - 1][j] == '0')
            alive_neighbor++;
        if (j < d->width - 1 && d->map[i - 1][j + 1] == '0')
            alive_neighbor++;
    }

    if (j > 0 && d->map[i][j - 1] == '0')
        alive_neighbor++;
    if (j < d->width - 1 && d->map[i][j + 1] == '0')
        alive_neighbor++;

    if (i < d->height - 1) {
        if (j > 0 && d->map[i + 1][j - 1] == '0')
            alive_neighbor++;
        if (d->map[i + 1][j] == '0')
            alive_neighbor++;
        if (j < d->width - 1 && d->map[i + 1][j + 1] == '0')
            alive_neighbor++;
    }

    if (d->map[i][j] == '0') {
        if (alive_neighbor == 2 || alive_neighbor == 3)
            return true;
    } else {
        if (alive_neighbor == 3)
            return true;
    }
    return false;
}

int simulate_life(t_data *d) {
    char **new_map = alloc_map(d);
    if (new_map == NULL)
        return -1;
    for (int i = 0; i < d->height; ++i) {
        for (int j = 0; j < d->width; ++j) {
            if (can_survive(d, i, j) == true)
                new_map[i][j] = '0';
        }
    }
    free_map(d);
    d->map = new_map;
    return 0;
}

int main(int argc, char *argv[]) {
    t_data d = {0, 0, 0, NULL, NULL};
    if (check_args(argc, argv, &d) == -1)
        return 1;
    if (get_command(&d) == -1)
        return 1;
    if (init_map(&d) == -1)
        return 1;
    for (int i = 0; i < d.iterations; ++i) {
        if (simulate_life(&d) == -1) {
            free_map(&d);
            return 1;
        }
    }
    print_map(&d);
    free_map(&d);
    return 0;
}
