
#ifdef UA_ARCHITECTURE_ZERYNTH
#include "zerynth.h"
#include "ua_types.h"
#include <time.h>
#include <sys/time.h>

UA_DateTime UA_DateTime_now(void) {
    // struct timeval tv;
    // gettimeofday(&tv, NULL);
    // return (tv.tv_sec * UA_DATETIME_SEC) +     (tv.tv_usec * UA_DATETIME_USEC)              + UA_DATETIME_UNIX_EPOCH;
    return (_systime_seconds * UA_DATETIME_SEC) + (_systime_millis * 1000 * UA_DATETIME_USEC) + UA_DATETIME_UNIX_EPOCH;
}

/* Credit to https://stackoverflow.com/questions/13804095/get-the-time-zone-gmt-offset-in-c */
// it doesn't seems neccessary at the moment.
UA_Int64 UA_DateTime_localTimeUtcOffset(void) {
    time_t gmt, rawtime = time(NULL);
    struct tm *ptm;
    struct tm gbuf;
    ptm = gmtime_r(&rawtime, &gbuf);
    // Request that mktime() looksup dst in timezone database
    ptm->tm_isdst = -1;
    gmt = mktime(ptm);
    return (UA_Int64) (difftime(rawtime, gmt) * UA_DATETIME_SEC);
}

UA_DateTime UA_DateTime_nowMonotonic(void) {
#if defined(__APPLE__) || defined(__MACH__)
    /* OS X does not have clock_gettime, use clock_get_time */
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    return (mts.tv_sec * UA_DATETIME_SEC) + (mts.tv_nsec / 100);
#elif !defined(CLOCK_MONOTONIC_RAW)
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * UA_DATETIME_SEC) + (ts.tv_nsec / 100);
#else
    // struct timespec ts;
    // clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    // return (ts.tv_sec * UA_DATETIME_SEC) + (ts.tv_nsec / 100);
    return (_systime_seconds * UA_DATETIME_SEC) + (_systime_millis * 10000);
#endif
}

#endif /* UA_ARCHITECTURE_ZERYNTH */
