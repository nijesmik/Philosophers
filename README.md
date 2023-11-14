# Philosophers

## External functs.

### gettimeofday

```c
#include <sys/time.h>

int
gettimeofday(struct timeval *restrict tp, void *restrict tzp);
```

The system's notion of the current Greenwich time and the current time zone is obtained with the `gettimeofday()` call.
The time is expressed in seconds and microseconds since midnight (0 hour), January 1, 1970.
The resolution of the system clock is hardware dependent, and the time may be updated continuously or in "ticks".

If `tp` is non-NULL and `tzp` is NULL, then only the timeval struct in `tp` is populated.

The structure pointed to by `tp` is defined in ⟨sys/time.h⟩ as:

```c
struct timeval {
    time_t       tv_sec;   /* seconds since Jan. 1, 1970 */
    suseconds_t  tv_usec;  /* and microseconds */
};
```

The timeval structure specifies a time value in seconds and microseconds.
The values in timeval are opaque types whose length may vary on different machines; depending on them to have any given length may lead to errors.

#### RETURN

`0` return value indicates that the call succeeded.
`-1` return value indicates an error occurred, and in this case an error code is stored into the global variable errno.