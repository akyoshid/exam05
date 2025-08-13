#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

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

// Success -> Return 0
// Failure -> Return -1
int check_args(int argc, char *argv[], t_data *d) {
    if (argc != 4) {
        ft_putstr("Error\nUsage: ./life width height iterations\n");
        return -1;
    }
    d->width = atoi(argv[1]);
    d->height = atoi(argv[2]);
    d->iterations = atoi(argv[3]);
    if (d->width <= 0) {
        ft_putstr("Error\nUsage: width must be a number greater than 0\n");
        return -1;
    }
    else if (d->height <= 0) {
        ft_putstr("Error\nUsage: height must be a number greater than 0\n");
        return -1;
    }
    else if (d->iterations < 0) {
        ft_putstr("Error\nUsage: iterations must be a number greater than or equal to 0\n");
        return -1;
    }
    return 0;
}

// Success -> Return 0
// Failure -> Return -1
int get_command(t_data *d) {
    int i = 0;
    int alloc_count = 0;
    ssize_t read_ret;
    while (1) {
        if ((i + 1) / 64 == alloc_count) {
            alloc_count++;
            char *tmp = (char *)realloc(d->command, 64 * alloc_count);
            if (tmp == NULL) {
                ft_putstr("Error\nrealloc: failed to allocate memory\n");
                free(d->command);
                d->command = NULL;
                return -1;
            }
            d->command = tmp;
        }
        read_ret = read(0, d->command + i, 1);
        if (read_ret == 0) {
            d->command[i] = '\0';
            return 0;
        } else if (read_ret == -1) {
            ft_putstr("Error\nread: failed to read\n");
            free(d->command);
            d->command = NULL;
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
    ft_putstr("\n");
    free(d.command);

    //

    return 0;
}
