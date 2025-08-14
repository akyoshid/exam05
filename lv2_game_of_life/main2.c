#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data {
    int width;
    int height;
    int iterations;
    char *command;
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

int main(int argc, char *argv[]) {
    t_data d = {0, 0, 0, NULL};
    if (check_args(argc, argv, &d) == -1)
        return 1;
    if (get_command(&d) == -1)
        return 1;

    //
    ft_putstr(d.command);
    putchar('\n');
    free(d.command);
    //
    return 0;
}
