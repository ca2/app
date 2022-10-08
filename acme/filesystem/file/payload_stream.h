#pragma once


//class payload_stream;
//
//
//inline void __exchange(::payload_stream & s, bool & b);
//inline void __exchange(::payload_stream & s, i8 & i);
//inline void __exchange(::payload_stream & s, i16 & i);
//inline void __exchange(::payload_stream & s, i32 & i);
//inline void __exchange(::payload_stream & s, i64 & i);
//#if !defined(LINUX)
//inline void __exchange(::payload_stream & s, long & l);
//#endif
//inline void __exchange(::payload_stream & s, u8 & u);
//inline void __exchange(::payload_stream & s, u16 & u);
//inline void __exchange(::payload_stream & s, u32 & u);
//inline void __exchange(::payload_stream & s, u64 & u);
//inline void __exchange(::payload_stream & s, float & f);
//inline void __exchange(::payload_stream & s, double & d);
//inline void __exchange(::payload_stream & s, ::earth::time & time);
//inline void __exchange(::payload_stream & s, const char * psz);
//inline void __exchange(::payload_stream & s, string & str);
//inline void __exchange(::payload_stream & s, ::file::path & path);
//inline void __exchange(::payload_stream & s, ::atom & atom);
//inline void __exchange(::payload_stream & s, ::payload & payload);
//inline void __exchange(::payload_stream & s, ::property & property);
//inline void __exchange(::payload_stream & s, ::property_set& set);
//inline void __exchange(::payload_stream & s, ::block & block);
//inline void __exchange(::payload_stream & s, ::int_array & ia);
//inline void __exchange(::payload_stream & s, ::string_array & stra);
//inline void __exchange(::payload_stream & s, ::memory & memory);
//
//
//
//
//
//
//inline void __exchange(::payload_stream & s, ::matter & matter);
//
//
//template < typename OBJECT >
//inline void __exchange(::payload_stream& s, __pointer(OBJECT)& pobject);
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline void __exchange(::payload_stream& stream, ::array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >& array);
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline void __exchange(::payload_stream& s, const ::raw_array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >& array);
//
//template < typename TYPE, enum_type t_etypePayload = e_type_element >
//inline void __exchange(::payload_stream& s, const ::numeric_array < TYPE, t_etypePayload >& array);
//
//template < typename Type, typename RawType, enum_type t_etypePayload >
//inline void __exchange(::payload_stream& s, const ::string_array_base < Type, RawType, t_etypePayload >& array);
//
//
//template < class ARRAY >
//inline void __exchange_array(::payload_stream& stream, ARRAY& array);
//
//template < typename ARRAY >
//inline void __exchange_save_array(::payload_stream& s, ARRAY& array);
//
//template < typename ARRAY >
//inline void __exchange_load_array(::payload_stream& s, ARRAY& array);
//
//
//class CLASS_DECL_ACME payload_stream :
//   virtual public stream_base
//{
//public:
//
//
//   class ::payload *          m_ppayload;
//
//
//   payload_stream();
//   payload_stream(class ::payload * pvar);
//   virtual ~payload_stream();
//
//
//   class ::payload & payload();
//   const class ::payload & payload() const;
//
//
//   template < typename TYPE >
//   void default_exchange(TYPE & t);
//
//   template < typename TYPE >
//   void write_only(TYPE & t);
//
//   template < typename TYPE >
//   void var_exchange(const ::atom & atom, TYPE & t);
//
//   //virtual void write_object(const ::atom & atom, ::matter * pobject) ;
//   //virtual __pointer(::matter) read_object(const ::atom & atom) ;
//
//
//   virtual void read(block & block) ;
//   virtual void write(const block & block) ;
//
//
//   virtual void exchange(const ::atom & atom, double & d) ;
//   virtual void exchange(const ::atom& atom, i64& i) ;
//
//
//   template < typename TYPE >
//   inline void stream_exchange(const ::atom& atom, TYPE& t);
//
//
//};
//
//
//
//
//
