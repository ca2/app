#pragma once


CLASS_DECL_ACME ::u32 get_fast_tick_count();


CLASS_DECL_ACME i64 first_nano();
CLASS_DECL_ACME i64 get_nanos();


inline i64 first_micro() { return first_nano() / 1'000; }
inline i64 get_micros() { return get_nanos() / 1'000; }


inline i64 first_milli() { return first_nano() / 1'000'000; }
inline i64 get_millis() { return get_nanos() /  1'000'000; }


inline i64 first_sec() { return get_nanos() / 1'000'000'000; }
inline i64 get_secs() { return get_nanos() / 1'000'000'000; }



