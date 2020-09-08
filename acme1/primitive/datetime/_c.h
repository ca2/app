#pragma once


#define nano_to_tick(nano) ((::i64)(nano) / (::i64)1000000)
#define nano_to_millis(nano) ((double)(nano) / 1e6)
#define nano_to_secs(nano) ((double)(nano) / 1e9)





CLASS_DECL_ACME i64 first_nano();
CLASS_DECL_ACME i64 get_nanos();


CLASS_DECL_ACME DWORD get_fast_tick_count();

/// tick, int milliseconds
inline i64 first_tick() { return nano_to_tick(first_nano()); }
inline i64 get_tick() { return nano_to_tick(get_nanos()); }

/// millis, double milliseconds
inline double first_milli() { return nano_to_millis(first_nano()); }
inline double get_millis() { return nano_to_millis(get_nanos()); }

inline double get_secs() { return nano_to_secs(get_nanos()); }








