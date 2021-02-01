#pragma once


template < typename TYPE >
inline void __string_exchange(text_stream & s, TYPE & t)
{

   s.json_exchange(t);

}

inline void __string_exchange(text_stream & s, ansichar & ansich) { s.string_exchange(ansich); }
inline void __string_exchange(text_stream & s, widechar & widech) { s.string_exchange(widech); }
inline void __string_exchange(text_stream & s, i8 & i) { s.number_exchange(i); }
inline void __string_exchange(text_stream & s, i16 & i) { s.number_exchange(i); }
inline void __string_exchange(text_stream & s, i32 & i) { s.number_exchange(i); }
inline void __string_exchange(text_stream & s, i64 & i) { s.number_exchange(i); }
inline void __string_exchange(text_stream & s, u8 & u) { s.number_exchange(u); }
inline void __string_exchange(text_stream & s, u16 & u) { s.number_exchange(u); }
inline void __string_exchange(text_stream & s, u32 & u) { s.number_exchange(u); }
inline void __string_exchange(text_stream & s, u64 & u) { s.number_exchange(u); }
#if !defined(LINUX)
inline void __string_exchange(text_stream & s, long & l) { s.number_exchange(l); }
#endif
inline void __string_exchange(text_stream & s, float & f) { s.number_exchange(f); }
inline void __string_exchange(text_stream & s, double & d) { s.number_exchange(d); }
inline void __string_exchange(text_stream & s, ::datetime::time & time) { s.number_exchange(time.m_time); }
inline void __string_exchange(text_stream & s, const char * psz) { s.write_only(psz); }
inline void __string_exchange(text_stream & s, char * psz) { s.string_exchange(psz); }
inline void __string_exchange(text_stream & s, string & str) { s.string_exchange(str); }
inline void __string_exchange(text_stream & s, ::file::path & path) { s.string_exchange(path); }
inline void __string_exchange(text_stream & s, ::id & id) { s.string_exchange(id); }
inline void __string_exchange(text_stream & s, void * & p) { s.number_exchange((::iptr &)p); }
inline void __string_exchange(text_stream & s, wchar_t wsz[]) { s.string_exchange(wsz); }
//inline void __string_exchange(text_stream & s, matter & matter) { s.json_exchange(matter); }


//inline void __string_exchange(text_stream & s, ::rectangle_i32 & r) { s.json_exchange(r); }




template < typename TYPE >
inline void text_stream::json_exchange(TYPE & t)
{

   if (is_storing())
   {

      json_write(t);

   }
   else
   {

      json_read(t);

   }

}


template < typename TYPE >
inline void text_stream::json_write(const TYPE & t)
{

   var_stream s;

   string strJson;

   s.set_storing();

   ::__exchange(s, (TYPE &) t);

   strJson = s.m_pvar->get_json();

   string_write(strJson);

}


template < typename TYPE >
inline void text_stream::json_read(TYPE & t)
{

   var_stream s;

   string strJson;

   string_read(strJson);

   s.m_pvar->parse_json(strJson);

   s.set_loading();

   ::__exchange(s, t);

}



