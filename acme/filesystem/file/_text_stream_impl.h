﻿#pragma once


//template < typename TYPE >
//inline void __string_exchange(text_stream & s, TYPE & t)
//{
//
//   s.network_payload_exchange(t);
//
//}
//
//inline void __string_exchange(text_stream & s, ::ansi_character & ansich) { s.string_exchange(ansich); }
//inline void __string_exchange(text_stream & s, ::wide_character & widech) { s.string_exchange(widech); }
//inline void __string_exchange(text_stream & s, i8 & i) { s.number_exchange(i); }
//inline void __string_exchange(text_stream & s, i16 & i) { s.number_exchange(i); }
//inline void __string_exchange(text_stream & s, i32 & i) { s.number_exchange(i); }
//inline void __string_exchange(text_stream & s, i64 & i) { s.number_exchange(i); }
//inline void __string_exchange(text_stream & s, u8 & u) { s.number_exchange(u); }
//inline void __string_exchange(text_stream & s, u16 & u) { s.number_exchange(u); }
//inline void __string_exchange(text_stream & s, u32 & u) { s.number_exchange(u); }
//inline void __string_exchange(text_stream & s, u64 & u) { s.number_exchange(u); }
//#if !defined(LINUX) && !defined(FREEBSD)
//inline void __string_exchange(text_stream & s, long & l) { s.number_exchange(l); }
//#endif
//inline void __string_exchange(text_stream & s, float & f) { s.number_exchange(f); }
//inline void __string_exchange(text_stream & s, double & d) { s.number_exchange(d); }
//inline void __string_exchange(text_stream & s, ::earth::time & time) { s.number_exchange(time.m_i); }
//inline void __string_exchange(text_stream & s, const scoped_string & str) { s.write_only(psz); }
//inline void __string_exchange(text_stream & s, char * psz) { s.string_exchange(psz); }
//inline void __string_exchange(text_stream & s, string & str) { s.string_exchange(str); }
//inline void __string_exchange(text_stream & s, ::file::path & path) { s.string_exchange(path); }
//inline void __string_exchange(text_stream & s, ::atom & atom) { s.string_exchange(atom); }
//inline void __string_exchange(text_stream & s, void * & p) { s.number_exchange((::iptr &)p); }
//inline void __string_exchange(text_stream & s, wchar_t wsz[]) { s.string_exchange(wsz); }
////inline void __string_exchange(text_stream & s, matter & matter) { s.network_payload_exchange(matter); }
//
//
////inline void __string_exchange(text_stream & s, ::rectangle_i32 & r) { s.network_payload_exchange(r); }
//
//
//
//
//template < typename TYPE >
//inline void text_stream::network_payload_exchange(TYPE & t)
//{
//
//   if (is_storing())
//   {
//
//      network_payload_write(t);
//
//   }
//   else
//   {
//
//      network_payload_read(t);
//
//   }
//
//}
//
//
//template < typename TYPE >
//inline void text_stream::network_payload_write(const TYPE & t)
//{
//
//   payload_stream s;
//
//   string strNetworkPayload;
//
//   s.set_storing();
//
//   ::__exchange(s, (TYPE &) t);
//
//   strNetworkPayload = s.m_ppayload->get_network_payload();
//
//   string_write(strNetworkPayload);
//
//}
//
//
//template < typename TYPE >
//inline void text_stream::network_payload_read(TYPE & t)
//{
//
//   payload_stream s;
//
//   string strNetworkPayload;
//
//   string_read(strNetworkPayload);
//
//   s.m_ppayload->parse_network_payload(strNetworkPayload);
//
//   s.set_loading();
//
//   ::__exchange(s, t);
//
//}
//
//
//
