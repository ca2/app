#pragma once



//#include "acme/prototype/time/time.h"

CLASS_DECL_ACME huge_integer i64_nanosecond();

inline huge_integer i64_microsecond() { return (huge_integer) (i64_nanosecond() / 1'000); }

inline huge_integer i64_millisecond() { return (huge_integer) (i64_nanosecond() / 1'000'000); }

inline huge_integer i64_second() { return (huge_integer) (i64_nanosecond() / 1'000'000'000); }

inline huge_integer i64_minute() { return (huge_integer) (i64_nanosecond() / 60'000'000'000); }

inline huge_integer i64_hour() { return (huge_integer) (i64_nanosecond() / 3'600'000'000'000); }

inline huge_integer i64_day() { return (huge_integer) (i64_nanosecond() / 86'400'000'000'000); }



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










