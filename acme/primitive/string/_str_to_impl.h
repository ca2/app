#pragma once


inline    i32 ::str().to_with_fallback(const ::string & psz, i32 iDefault) { from_string(iDefault, psz); return iDefault; }
inline   i64 ::str().to_with_fallback(const ::string & psz, i64 iDefault) { from_string(iDefault, psz); return iDefault; }
inline   i32 ::str().to_with_fallback(const ::string & psz, i32 iDefault, i32 iBase) { from_string(iDefault, iBase, psz); return iDefault; }
inline   i64 ::str().to_with_fallback(const ::string & psz, i64 iDefault, i32 iBase) { from_string(iDefault, iBase, psz); return iDefault; }

