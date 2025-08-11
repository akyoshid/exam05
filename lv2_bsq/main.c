#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct s_data {
    int row;
    int col;
    char empty;
    char obstacle;
    char full;
    char **map;
    int **dp_table;
    int max_size;
    int max_i;
    int max_j;
} t_data;

FILE* get_fstream(char *filename) {
    FILE* f;
    if (filename == NULL)
        f = stdin;
    else
        f = fopen(filename, "r");
    if (f == NULL)
        fprintf(stderr, "map error\n");
    return (f);
}

// Success -> return 1
// Failure -> return 0
int ft_isprint(int c) {
    if (c >= 32 && c <= 126)
        return 1;
    else
        return 0;
}

// Success -> return 1
// Failure -> return 0
int is_1st_line_valid(t_data *d) {
    if (d->row <= 0
        || ft_isprint(d->empty) == 0
        || ft_isprint(d->obstacle) == 0
        || ft_isprint(d->full) == 0
        || d->empty == d->obstacle
        || d->obstacle == d->full
        || d->full == d->empty)
        return 0;
    else
        return 1;
}

int **calloc_dp_table(t_data *d) {
    int **tmp;
    tmp = (int **)calloc(d->row + 1, sizeof(int *));
    if (tmp == NULL)
        return NULL;
    for (int i = 0; i < d->row; ++i) {
        tmp[i] = calloc(d->col + 1, sizeof(int));
        if (tmp[i] == NULL) {
            for (int j = 0; j < i; ++j)
                free(tmp[j]);
            free(tmp);
            return NULL;
        }
    }
    return tmp;
}

void free_map(t_data *d) {
    for (int i = 0; i < d->row; ++i)
        free(d->map[i]);
    free(d->map);
}

void free_dp_table(t_data *d) {
    for (int i = 0; i < d->row; ++i)
        free(d->dp_table[i]);
    free(d->dp_table);
}

// Success -> return 1
// Failure -> return 0
int is_line_valid(char *line, t_data *d) {
    for (int i = 0; i < d->col; ++i) {
        if (!(line[i] == d->empty || line[i] == d->obstacle))
            return 0;
    }
    if (line[d->col] != '\n')
        return 0;
    return 1;
}

// Success -> return 0
// Failure -> return -1
int read_map(FILE *f, t_data *d) {
    int read = 0;
    size_t len = 0;
    for (int i = 0; i < d->row; ++i) {
        read = getline(&(d->map[i]), &len, f);
        if (i == 0)
            d->col = read - 1;
        if (read == -1 || d->col != read - 1 || is_line_valid(d->map[i], d) == 0) {
            fprintf(stderr, "map error\n");
            for (int j = 0; j <= i; ++j)
                free(d->map[j]);
            free(d->map);
            return -1;
        }
    }
    errno = 0;
    char *temp = NULL;
    if (getline(&temp, &len, f) != -1 || errno != 0) {
        fprintf(stderr, "map error\n");
        free(temp);
        free_map(d);
        return -1;
    }
    free(temp);
    return 0;
}

// Success -> return 0
// Failure -> return -1
int set_data(FILE *f, t_data *d) {
    if (fscanf(f, "%d %c %c %c\n", &d->row, &d->empty, &d->obstacle, &d->full) != 4
        || is_1st_line_valid(d) == 0) {
        fprintf(stderr, "map error\n");
        return -1;
    }
    d->map = (char **)calloc(d->row + 1, sizeof(char *));
    if (d->map == NULL)
        return -1;
    if (read_map(f, d) == -1)
        return -1;
    return 0;
}

void print_map(char **map) {
    if (map == NULL)
        return ;
    for (int i = 0; map[i] != NULL; ++i)
        fprintf(stdout, "%s", map[i]);
}

int get_min(int a, int b, int c) {
    int min = a;
    if (b < min)
        min = b;
    if (c < min)
        min = c;
    return min;
}

void fill_dp_table(t_data *d) {
    for (int i = 0; i < d->row; ++i) {
        for (int j = 0; j < d->col; ++j) {
            if (d->map[i][j] == d->obstacle)
                d->dp_table[i][j] = 0;
            else if (i == 0 || j == 0)
                d->dp_table[i][j] = 1;
            else {
                d->dp_table[i][j] = get_min(
                        d->dp_table[i - 1][j - 1],
                        d->dp_table[i - 1][j],
                        d->dp_table[i][j - 1]) + 1;
            }
        }
    }
}

void get_biggest_square(t_data *d) {
    for (int i = 0; i < d->row; ++i) {
        for (int j = 0; j < d->col; ++j) {
            if (d->dp_table[i][j] > d->max_size) {
                d->max_size = d->dp_table[i][j];
                d->max_i = i - d->max_size + 1;
                d->max_j = j - d->max_size + 1;
            }
        }
    }
}

void rewrite_map(t_data *d) {
    if (d->max_size == 0)
        return ;
    for (int i = 0; i < d->max_size; ++i) {
        for (int j = 0; j < d->max_size; ++j)
            d->map[d->max_i + i][d->max_j + j] = d->full;
    }
}

void find_biggest_square(t_data *d) {
    fill_dp_table(d);
    get_biggest_square(d);
    rewrite_map(d);
}

void bsq(char *filename) {
    FILE* f = get_fstream(filename);
    if (f == NULL)
        return ;
    t_data d = {0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0};
    if (set_data(f, &d) == -1) {
        fclose(f);
        return ;
    }
    fclose(f);
    d.dp_table = calloc_dp_table(&d);
    if (d.dp_table == NULL) {
        free_map(&d);
        return ;
    }
    find_biggest_square(&d);
    print_map(d.map);
    free_map(&d);
    free_dp_table(&d);
}

int main(int argc, char *argv[]) {
    if (argc == 1)
        bsq(NULL);
    else {
        for (int i = 1; i < argc; ++i)
            bsq(argv[i]);
    }
    return 0;
}
