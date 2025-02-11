#pragma once



//#include "acme/prototype/time/time.h"

CLASS_DECL_ACME long long long_long_nanosecond();

inline long long long_long_microsecond() { return (long long) (long_long_nanosecond() / 1'000); }

inline long long long_long_millisecond() { return (long long) (long_long_nanosecond() / 1'000'000); }

inline long long long_long_second() { return (long long) (long_long_nanosecond() / 1'000'000'000); }

inline long long long_long_minute() { return (long long) (long_long_nanosecond() / 60'000'000'000); }

inline long long long_long_hour() { return (long long) (long_long_nanosecond() / 3'600'000'000'000); }

inline long long long_long_day() { return (long long) (long_long_nanosecond() / 86'400'000'000'000); }



//#include "acme/prototype/time/integral/time.h"


//#include "nanosecond.h"
//#include "microsecond.h"
//#include "millisecond.h"
//
//
//#include "second.h"
//
//
//#include "minute.h"
//#include "hour.h"
//#include "day.h"










