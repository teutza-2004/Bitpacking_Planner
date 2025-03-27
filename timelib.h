#ifndef TIMELIB_H_INCLUDED
#define TIMELIB_H_INCLUDED

#define LEN_TZ 5
#define LEN_NAME 10

typedef struct {
    unsigned char hour;
    unsigned char min;
    unsigned char sec;
} TTime;

typedef struct {
    unsigned char day;
    unsigned char month;
    unsigned int year;
} TDate;

typedef struct {
    char name[LEN_TZ];
    signed char utc_hour_difference;
} TTimezone;

typedef struct {
    TDate date;
    TTime time;
    TTimezone *tz;
} TDateTimeTZ;

typedef struct {
    unsigned int timestamp;
    unsigned int len;
} TInterval;

typedef struct {
    char name[LEN_NAME];
    char tz_name[LEN_TZ];
    unsigned int tz_index;
    unsigned int nr;  // nr de intervale
    TInterval *intervals;
} TPersons;

typedef struct {
    unsigned int nr_able;
    unsigned int timestamp;
} TEventInterval;

TTime convertUnixTimestampToTime(unsigned int timestamp);
TDate convertUnixTimestampToDateWithoutLeapYears(unsigned int timestamp);
TDate convertUnixTimestampToDate(unsigned int timestamp);
TDateTimeTZ convertUnixTimestampToDateTimeTZ(unsigned int timestamp, TTimezone *timezones, int timezone_index);
unsigned int convertDateTimeTZToUnixTimestamp(TDateTimeTZ);
void printDateTimeTZ(TDateTimeTZ datetimetz);

#define MINUTE 60  // nr de secunde intr-un minut
#define HOUR 3600  // nr de secunde intr-o ora
#define DAY 24  // nr de ore intr-o zi
static const int MONTH[13] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  // nr de zile in fiecare luna
#define YEAR_M 12  // nr de luni intr-un an
#define YEAR_D 365  // nr de zile intr-un an
#define START 1970  // anul primordial
static const char month_name[13][15] = {"ianuarie", "februarie", "martie", "aprilie", "mai",
                                  "iunie", "iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};

#endif  // TIMELIB_H_INCLUDED
