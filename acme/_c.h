#pragma once




inline int c_is_null(const void * p) { return ((uptr)p) < 65536; }
inline int c_is_set(const void * p) { return !c_is_null(p); }



