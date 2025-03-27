#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"

int cmp(const void *x, const void *y) {
    TInterval *a = (TInterval *) x;
    TInterval *b = (TInterval *) y;
    if ((*a).timestamp < (*b).timestamp) {
        return -1;
    }
    return 1;
}

int cmp_interval(const void *x, const void *y) {
    TEventInterval *a = (TEventInterval *) x;
    TEventInterval *b = (TEventInterval *) y;
    if ((*a).timestamp < (*b).timestamp) {
        return -1;
    }
    return 1;
}

int cmp_names(const void *x, const void *y) {
    TPersons *a = (TPersons *) x;
    TPersons *b = (TPersons *) y;
    if (strcmp((*a).name, (*b).name) < 0) {
        return -1;
    }
    return 1;
}

// concateneaza intervalele care sunt consecutive la o persoana
// le returneaza doar pe cele care au nr de ore cel putin cat nr de ore al evenimentului
void CompressIntervals(TInterval *person, unsigned int *nr_int, unsigned int len_event) {
    int i = 0, nr = 0;
    qsort(person, *nr_int, sizeof(TInterval), cmp);  // ca sa fie intervalele in ordine cronologica

    TInterval *rez = calloc(*nr_int, sizeof(TInterval));
    if (!rez) {
        exit(0);
    }

    TInterval one;  // un interval auxiliar in care calculam fiecare interval concatenat
    one.len = person[0].len;
    one.timestamp = person[0].timestamp;
    nr = 0;
    for (i = 1; i < *nr_int; i++) {
        if (one.timestamp + one.len * HOUR == person[i].timestamp) {
            one.len += person[i].len;
        } else {
            if (one.len >= len_event) {
                rez[nr].timestamp = one.timestamp;
                rez[nr++].len = one.len;
            }
            one.timestamp = person[i].timestamp;
            one.len = person[i].len;
        }
    }
    if (one.len >= len_event) {
        rez[nr].timestamp = one.timestamp;
        rez[nr++].len = one.len;
    }
    *nr_int = nr;
    for (i = 0; i < nr; i++) {
        person[i].len = rez[i].len;
        person[i].timestamp = rez[i].timestamp;
    }
    free(rez);
}

void Planning(TTimezone *tz, TPersons *pers, int P, unsigned int event_min, unsigned int event_len) {
    int i = 0, j = 0, k = 0, p = 0;
    int nr_event = 0;  // nr maxim de intervale
    int index_event = -1;  // indexul primului interval care indeplineste conditiile
    for (i = 0 ; i < P; i++) {
        CompressIntervals(pers[i].intervals, &pers[i].nr, event_len);
    }

    TEventInterval event[HOUR] = {};
    for (i = 0; i < P; i++) {
        for (j = 0; j < pers[i].nr; j++) {
            for (k = 0; k < nr_event; k++) {
                if (pers[i].intervals[j].timestamp == event[k].timestamp) {
                    event[k].nr_able++;
                }
            }
            if (k == nr_event) {
                for (p = 0; p <= pers[i].intervals[j].len - event_len; p++) {
                    for (k = 0; k < nr_event; k++) {
                        if (p != 0 && pers[i].intervals[j].timestamp + p * HOUR == event[k].timestamp) {
                            event[k].nr_able++;
                        }
                    }
                    if (k == nr_event) {
                        event[nr_event].nr_able = 1;
                        event[nr_event++].timestamp = pers[i].intervals[j].timestamp + p * HOUR;
                    }
                }
            }
        }
    }

    qsort(event, nr_event, sizeof(TEventInterval), cmp_interval);

    for (i = 0; i < nr_event; i++) {
        if (event[i].nr_able >= event_min) {
            index_event = i;
            break;
        }
    }

    if (index_event < 0) {
        printf("imposibil");
        return;
    }

    qsort(pers, P, sizeof(TPersons), cmp_names);

    for (i = 0; i < P; i++) {
        printf("%s: ", pers[i].name);
        for (j = 0; j < pers[i].nr; j++) {
            for (k = 0; k <= pers[i].intervals[j].len - event_len; k++) {
                if (pers[i].intervals[j].timestamp + k * HOUR == event[index_event].timestamp) {
                    TDateTimeTZ aux;
                    aux = convertUnixTimestampToDateTimeTZ(event[index_event].timestamp, tz, (int)pers[i].tz_index);
                    printDateTimeTZ(aux);
                    break;
                }
            }
            if (k <= pers[i].intervals[j].len - event_len) {
                break;
            }
        }
        if (j == pers[i].nr) {
            printf("invalid\n");
        }
        free(pers[i].intervals);
    }
    free(pers);
}

int main() {
    // Task 9
    int i = 0, j = 0;

    // citire timezone
    int T = 0;
    scanf("%d ", &T);
    TTimezone *tz = calloc(T, sizeof(TTimezone));
    if (!tz) {
        exit(0);
    }
    for (i = 0; i < T; i++) {
        scanf("%s %hhd ", tz[i].name, &tz[i].utc_hour_difference);
    }

    // citire persoane + intervale libere
    int P = 0;
    scanf("%d ", &P);
    TPersons *pers = calloc(P, sizeof(TPersons));
    if (!pers) {
        exit(0);
    }
    for (i = 0; i < P; i++) {
        scanf("%s %s %d ", pers[i].name, pers[i].tz_name, &pers[i].nr);
        pers[i].intervals = calloc(pers[i].nr, sizeof(TInterval));
        if (!pers[i].intervals) {
            exit(0);
        }
        for (j = 0; j < pers[i].nr; j++) {
            TDateTimeTZ date;
            int k = 0;
            for (k = 0; k < T; k++) {
                if (strcmp(pers[i].tz_name, tz[k].name) == 0) {
                    date.tz = tz + k;
                    pers[i].tz_index = k;
                    break;
                }
            }
            scanf("%u %hhd %hhd %hhd %u ",
                &date.date.year, &date.date.month, &date.date.day, &date.time.hour, &pers[i].intervals[j].len);
            date.time.min = date.time.sec = 0;
            pers[i].intervals[j].timestamp = convertDateTimeTZToUnixTimestamp(date);
        }
    }

    // citire date eveniment
    unsigned int event_len = 0, event_min = 0;
    scanf("%u %u", &event_min, &event_len);

    Planning(tz, pers, P, event_min, event_len);

    free(tz);
    return 0;
}
