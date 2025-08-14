#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_data {
    int width;
    int height;
    int iterations;
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

int main(int argc, char *argv[]) {
    t_data d = {0, 0, 0};
    if (check_args(argc, argv, &d) == -1)
        return -1;

    //
    ft_putstr("Success\n");
    //
    return 0;
}
