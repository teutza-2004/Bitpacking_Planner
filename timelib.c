#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"

// Task 1
TTime convertUnixTimestampToTime(unsigned int timestamp) {
    TTime result;
    result.hour = (timestamp / HOUR) % DAY;
    result.min = (timestamp % HOUR) / MINUTE;
    result.sec = timestamp % MINUTE;
    return result;
}

// Task 2
TDate convertUnixTimestampToDateWithoutLeapYears(unsigned int timestamp) {
    TDate result;
    timestamp /= DAY * HOUR;
    result.year = START + timestamp / YEAR_D;
    int aux_day = (int)timestamp % YEAR_D;
    int i = 0;
    for (i = 0; i < YEAR_M && aux_day - MONTH[i] >= 0; i++) {
        aux_day -= MONTH[i];
    }
    result.month = ++i;
    result.day = 1 + aux_day;
    return result;
}

// Task 3
TDate convertUnixTimestampToDate(unsigned int timestamp) {
    TDate result;
    timestamp /= DAY * HOUR;
    int aux_4years = (int)timestamp / (YEAR_D * 4 + 1);  // ultimii 4 ani la rand, al treilea din ei bisect (in zile)
    int this_4years = (int)timestamp % (YEAR_D * 4 + 1) / YEAR_D;  // in care an din ultimul cluster sunt (0,1,2 sau 3)
    result.year = START + aux_4years * 4 + this_4years;
    int aux_day = (int)timestamp % (YEAR_D * 4 + 1);  // nr de zile din cluster
    aux_day -= YEAR_D * this_4years;
    aux_day += ((this_4years < 2 || (this_4years == 2 && aux_day < MONTH[0] + MONTH[1] - 1)) ? 0 : -1);
    int i = 0;
    for (i = 0; i < YEAR_M && aux_day - MONTH[i] >= 0; i++) {
        aux_day -= MONTH[i];
    }
    result.month = ++i;
    result.day = 1 + aux_day;
    return result;
}

void TimeZone(unsigned int *hour, unsigned int *day, unsigned int *month, unsigned int *year, unsigned int difference) {
    *hour += difference;
    if ((int)(*hour) < 0) {
        *hour = DAY + *hour;
        (*day)--;
        if (*day < 1) {
            (*month)--;
            if (*month < 1) {
                *month = YEAR_M;
                *day = MONTH[YEAR_M-1];
                (*year)--;
            } else {
                *day = MONTH[*month-1];
                if (*year % 4 == 0 && *month == 2) {
                    (*day)++;
                }
            }
        }
    } else if ((int)(*hour) > DAY - 1) {
        *hour = *hour % DAY;
        (*day)++;
        if (*day > MONTH[*month-1]) {
            *day = 1;
            (*month)++;
            if (*month > YEAR_M) {
                (*year)++;
                *month = 1;
            }
        }
    }
}

// Task 4
TDateTimeTZ convertUnixTimestampToDateTimeTZ(unsigned int timestamp, TTimezone *timezones, int timezone_index) {
    TDateTimeTZ result;
    unsigned int difference = timezones[timezone_index].utc_hour_difference;
    result.time = convertUnixTimestampToTime(timestamp);
    result.date = convertUnixTimestampToDate(timestamp);
    result.tz = timezones + timezone_index;

    unsigned int hour = result.time.hour;
    unsigned int day = result.date.day;
    unsigned int month = result.date.month;
    unsigned int year = result.date.year;

    TimeZone(&hour, &day, &month, &year, difference);

    result.time.hour = hour;
    result.date.day = day;
    result.date.month = month;
    result.date.year = year;
    return result;
}

// Task 5
unsigned int convertDateTimeTZToUnixTimestamp(TDateTimeTZ datetimetz) {
    unsigned int difference = datetimetz.tz->utc_hour_difference;
    unsigned int hour = datetimetz.time.hour;
    unsigned int day = datetimetz.date.day;
    unsigned int month = datetimetz.date.month;
    unsigned int year = datetimetz.date.year;
    TimeZone(&hour, &day, &month, &year, -difference);  // adus inapoi in UTC
    datetimetz.time.hour = hour;
    datetimetz.date.day = day;
    datetimetz.date.month = month;
    datetimetz.date.year = year;

    unsigned int timestamp = 0;
    timestamp += datetimetz.time.sec;
    timestamp += datetimetz.time.min * MINUTE;
    timestamp += datetimetz.time.hour * HOUR;
    timestamp += datetimetz.date.day * DAY * HOUR - (DAY * HOUR);
    int i = 0;
    for (i = 0; i < datetimetz.date.month -1; i++) {
        timestamp += MONTH[i] * DAY * HOUR;
    }
    timestamp += (datetimetz.date.year - START) * YEAR_D * DAY * HOUR;
    timestamp += ((datetimetz.date.year - START - 2) / 4 + 1) * DAY * HOUR;
    timestamp += ((datetimetz.date.year % 4 == 0 && datetimetz.date.month < 2) ? -1 : 0) * DAY * HOUR;
    return timestamp;
}

// Task 6
void printDateTimeTZ(TDateTimeTZ datetimetz) {
    printf("%02d %s %d, %02d:%02d:%02d %s ",
           datetimetz.date.day, month_name[datetimetz.date.month-1], datetimetz.date.year,
           datetimetz.time.hour, datetimetz.time.min, datetimetz.time.sec, datetimetz.tz->name);
    if (datetimetz.tz->utc_hour_difference < 0) {
        printf("(UTC%d)\n", datetimetz.tz->utc_hour_difference);
    } else {
        printf("(UTC+%d)\n", datetimetz.tz->utc_hour_difference);
    }
}
