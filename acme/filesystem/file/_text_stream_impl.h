#pragma once


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
//inline void __string_exchange(text_stream & s, char & i) { s.number_exchange(i); }
//inline void __string_exchange(text_stream & s, short & i) { s.number_exchange(i); }
//inline void __string_exchange(text_stream & s, int & i) { s.number_exchange(i); }
//inline void __string_exchange(text_stream & s, huge_integer & i) { s.number_exchange(i); }
//inline void __string_exchange(text_stream & s, unsigned char & u) { s.number_exchange(u); }
//inline void __string_exchange(text_stream & s, unsigned short & u) { s.number_exchange(u); }
//inline void __string_exchange(text_stream & s, unsigned int & u) { s.number_exchange(u); }
//inline void __string_exchange(text_stream & s, huge_natural & u) { s.number_exchange(u); }
//#if !defined(LINUX) && !defined(FREEBSD) && !defined(OPENBSD)
//inline void __string_exchange(text_stream & s, long & l) { s.number_exchange(l); }
//#endif
//inline void __string_exchange(text_stream & s, float & f) { s.number_exchange(f); }
//inline void __string_exchange(text_stream & s, double & d) { s.number_exchange(d); }
//inline void __string_exchange(text_stream & s, ::earth::time & time) { s.number_exchange(time.m_i); }
//inline void __string_exchange(text_stream & s, const ::scoped_string & scopedstr) { s.write_only(psz); }
//inline void __string_exchange(text_stream & s, char * psz) { s.string_exchange(psz); }
//inline void __string_exchange(text_stream & s, string & str) { s.string_exchange(str); }
//inline void __string_exchange(text_stream & s, ::file::path & path) { s.string_exchange(path); }
//inline void __string_exchange(text_stream & s, ::atom & atom) { s.string_exchange(atom); }
//inline void __string_exchange(text_stream & s, void * & p) { s.number_exchange((::iptr &)p); }
//inline void __string_exchange(text_stream & s, wchar_t wsz[]) { s.string_exchange(wsz); }
////inline void __string_exchange(text_stream & s, matter & matter) { s.network_payload_exchange(matter); }
//
//
////inline void __string_exchange(text_stream & s, ::int_rectangle & r) { s.network_payload_exchange(r); }
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
