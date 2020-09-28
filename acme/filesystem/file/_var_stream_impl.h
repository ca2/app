#pragma once


//inline void __var_exchange(var_stream & s, const ::id & id, i8 & i) { s.default_exchange(id, i); }
//inline void __var_exchange(var_stream & s, const ::id & id, i16 & i) { s.default_exchange(id, i); }
//inline void __var_exchange(var_stream & s, const ::id & id, i32 & i) { s.default_exchange(id, i); }
//inline void __var_exchange(var_stream & s, const ::id & id, i64 & i) { s.default_exchange(id, i); }
//inline void __var_exchange(var_stream & s, const ::id & id, u8 & u) { s.default_exchange(id, u); }
//inline void __var_exchange(var_stream & s, const ::id & id, u16 & u) { s.default_exchange(id, u); }
//inline void __var_exchange(var_stream & s, const ::id & id, u32 & u) { s.default_exchange(id, u); }
//inline void __var_exchange(var_stream & s, const ::id & id, u64 & u) { s.default_exchange(id, u); }
//inline void __var_exchange(var_stream & s, const ::id & id, float & f) { s.default_exchange(id, f); }
//inline void __var_exchange(var_stream & s, const ::id & id, double & d) { s.default_exchange(id, d); }
//inline void __var_exchange(var_stream & s, const ::id & id, ::datetime::time & time) { s.default_exchange(id, time.m_time); }
//inline void __var_exchange(var_stream & s, const ::id & id, const char * psz) { s.write_only(id, psz); }
//inline void __var_exchange(var_stream & s, const ::id & id, string & str) { s.default_exchange(id, str); }
//inline void __var_exchange(var_stream & s, const ::id & id, ::file::path & path) { s.default_exchange(id, path); }
//inline void __var_exchange(var_stream & s, const ::id & id, ::id & idId) { s.default_exchange(id, idId); }
//inline void __var_exchange(var_stream & s, const ::id & id, ::block & block) { s.default_exchange(id, block); }
//inline void __var_exchange(var_stream & s, const ::id & id, ::var & var) { s.default_exchange(id, var); }


//inline void __exchange(::var_stream& s, ::file::patha& patha) { s.var_exchange(patha); }



inline void __exchange(::var_stream& s, bool& b) { s.default_exchange(b); }
inline void __exchange(::var_stream& s, i8& i) { s.default_exchange(i); }
inline void __exchange(::var_stream& s, i16& i) { s.default_exchange(i); }
inline void __exchange(::var_stream& s, i32& i) { s.default_exchange(i); }
inline void __exchange(::var_stream& s, i64& i) { s.default_exchange(i); }
#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN)
inline void __exchange(::var_stream& s, long& l) { s.default_exchange(l); }
#endif
inline void __exchange(::var_stream& s, u8& u) { s.default_exchange(u); }
inline void __exchange(::var_stream& s, u16& u) { s.default_exchange(u); }
inline void __exchange(::var_stream& s, u32& u) { s.default_exchange(u); }
inline void __exchange(::var_stream& s, u64& u) { s.default_exchange(u); }
inline void __exchange(::var_stream& s, float& f) { s.default_exchange(f); }
inline void __exchange(::var_stream& s, double& d) { s.default_exchange(d); }
inline void __exchange(::var_stream& s, ::datetime::time& time) { s.default_exchange(time.m_time); }
inline void __exchange(::var_stream& s, const char* psz) { s.write_only(psz); }
inline void __exchange(::var_stream& s, string& str) { s.default_exchange(str); }
inline void __exchange(::var_stream& s, ::file::path& path) { s.default_exchange(path); }
inline void __exchange(::var_stream& s, ::id& id) { s.default_exchange(id); }
inline void __exchange(::var_stream& s, ::var& var) { s.default_exchange(var); }
inline void __exchange(::var_stream& s, ::property& property) { s.default_exchange(property); }
inline void __exchange(::var_stream& s, ::property_set& set) { s.default_exchange(set); }
inline void __exchange(::var_stream& s, ::block& block) { s.default_exchange(block); }
inline void __exchange(::var_stream& s, ::int_array& ia) { s.default_exchange(ia); }
inline void __exchange(::var_stream& s, ::string_array& stra) { s.default_exchange(stra); }
inline void __exchange(::var_stream& s, ::memory& memory) { s.default_exchange(memory); }




inline void __exchange(::var_stream& s, ::elemental& elemental) { elemental.exchange(s); }





