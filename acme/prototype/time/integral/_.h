#pragma once



//#include "acme/prototype/time/time.h"

CLASS_DECL_ACME huge_integer huge_integer_nanosecond();

inline huge_integer huge_integer_microsecond() { return (huge_integer) (huge_integer_nanosecond() / 1'000); }

inline huge_integer huge_integer_millisecond() { return (huge_integer) (huge_integer_nanosecond() / 1'000'000); }

inline huge_integer huge_integer_second() { return (huge_integer) (huge_integer_nanosecond() / 1'000'000'000); }

inline huge_integer huge_integer_minute() { return (huge_integer) (huge_integer_nanosecond() / 60'000'000'000); }

inline huge_integer huge_integer_hour() { return (huge_integer) (huge_integer_nanosecond() / 3'600'000'000'000); }

inline huge_integer huge_integer_day() { return (huge_integer) (huge_integer_nanosecond() / 86'400'000'000'000); }



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










