#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"

const int L_INT = 32;
const int L_PACK = 15;

int cmp7(const void *x, const void *y) {
    unsigned int *a = (unsigned int *) x;
    unsigned int *b = (unsigned int *) y;
    if (*a < *b) {
        return -1;
    }
    return 1;
}

int cmp8(const void *x, const void *y) {
    TDate *a = (TDate *) x;
    TDate *b = (TDate *) y;
    if ((*a).year < (*b).year) {
        return -1;
    } else if ((*a).year == (*b).year && (*a).month < (*b).month) {
        return -1;
    } else if ((*a).year == (*b).year && (*a).month == (*b).month && (*a).day < (*b).day) {
        return -1;
    }
    return 1;
}

unsigned int BitToInt(unsigned int x, int nr_shift, int nr_crt) {
    unsigned int aux = 0;
    int p = ~0;
    x >>= nr_shift;
    p <<= nr_crt;
    p = ~p;
    aux = x & p;
    return aux;
}

TDate Task7(unsigned int nr) {
    TDate date;
    const int L_DAY = 5, L_MONTH = 4, L_YEAR = 6;
    date.day = BitToInt(nr, 0, L_DAY);
    date.month = BitToInt(nr, L_DAY, L_MONTH);
    date.year = START + BitToInt(nr, L_DAY+L_MONTH, L_YEAR);
    return date;
}

void ControlArrayCalculator(int n, unsigned int *array, unsigned int *my_control_array) {
    int pos = 1;  // stie bitul curent pt nr din my_control_array
    int i = 0, j = 0;

    for (i = 0; i < n; i++) {
        if (i % L_INT == 0) {
            pos = 1;
        }
        int p = 1, nr = 0;
        for (j = 0; j < L_INT; j++) {
            if (array[i] & p) {
                nr++;
            }
            p <<= 1;
        }
        if (nr & 1) {
            my_control_array[i / L_INT] += pos;
        }
        pos <<= 1;
    }
}

void Task8(int N, int n, unsigned int *array, unsigned int *control_array,
            unsigned int *my_control_array, TDate *date, int *index) {
    int i = 0, rand = 0;
    for (i = 1; i <= N; i++) {
        int nr = i * L_PACK;  // nr total de biti pana in momentul curent
        int p1 = ~0, p2 = ~0;
        unsigned int aux = 0;  // pack-ul datii curente
        int p = 1 << (nr / L_INT) % L_INT;
        if (nr / L_INT == (nr - L_PACK) / L_INT &&  // verif daca inceput si sf data sunt in ac int
            (control_array[rand / L_INT] & p) != (my_control_array[rand / L_INT] & p)) {
            continue;
        } else if (nr / L_INT != (nr - L_PACK) / L_INT &&
                    ((control_array[rand / L_INT] & (p >> 1)) != (my_control_array[rand / L_INT] & (p >> 1)) ||
                    (control_array[rand / L_INT] & p) != (my_control_array[rand / L_INT] & p))) {
            rand++;
            continue;
        }
        if (nr % L_INT >= L_PACK) {
            p1 <<= nr % L_INT - L_PACK;
            p2 <<= nr % L_INT;
            p2 = ~p2;
            aux = array[rand] & (p1 & p2);
            aux >>= nr % L_INT - L_PACK;
            date[(*index)++] = Task7(aux);
        } else {
            p1 <<= L_INT - (L_PACK - nr % L_INT);
            aux = array[rand++] & p1;
            aux >>= L_INT - (L_PACK - nr % L_INT);

            p2 <<= nr % L_INT;
            p2 = ~p2;
            aux += (array[rand] & p2) << (L_PACK - nr % L_INT);
            date[(*index)++] = Task7(aux);
        }
    }
}

int main() {
    int nr_task = 0;
    scanf("%d", &nr_task);
    // Task 7
    const int TASK7 = 7;
    if (nr_task == TASK7) {
        int N = 0;
        scanf("%d", &N);

        unsigned int *array = calloc(N, sizeof(unsigned int));
        if (!array) {
            exit(0);
        }
        int i = 0;
        for (i = 0; i < N; i++) {
            scanf("%u", &array[i]);
        }
        qsort(array, N, sizeof(unsigned int), cmp7);

        for (i = 0; i < N; i++) {
            TDate date = Task7(array[i]);
            printf("%d %s %d\n", date.day, month_name[date.month-1], date.year);
        }

        free(array);
        return 0;
    }

    // Task 8
    int i = 0;
    int N = 0;  // nr de pachete
    scanf("%d", &N);
    int n = (N * L_PACK) / L_INT + ((N * L_PACK) % L_INT ? 1 : 0);  // nr de int-uri citite
    unsigned int *array = calloc(n, sizeof(unsigned int));
    if (!array) {
        exit(0);
    }
    for (i  = 0; i < n; i++) {
        scanf("%u", &array[i]);
    }

    int m = n / L_INT + (n % L_INT ? 1 : 0);  // nr de int-uri pt bitii de control
    unsigned int *control_array = calloc(m, sizeof(unsigned int));  // int-urile pt bitii de control dati
    if (!control_array) {
        exit(0);
    }
    for (i  = 0; i < n; i++) {
        scanf("%u", &control_array[i]);
    }

    unsigned int *my_control_array = calloc(m, sizeof(unsigned int));  // bitii de control calculati pt int citite
    if (!my_control_array) {
        exit(0);
    }
    ControlArrayCalculator(n, array, my_control_array);

    TDate *date = calloc(N, sizeof(TDate));
    if (!date) {
        exit(0);
    }
    int index = 0;
    Task8(N, n, array, control_array, my_control_array, date, &index);

    qsort(date, index, sizeof(TDate), cmp8);

    for (i = 0; i < index; i++) {
        printf("%d %s %d\n", date[i].day, month_name[date[i].month-1], date[i].year);
    }

    free(array);
    free(control_array);
    free(my_control_array);
    free(date);
    return 0;
}
