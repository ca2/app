#pragma once


//class payload_stream;
//
//
//inline void __exchange(::payload_stream & s, bool & b);
//inline void __exchange(::payload_stream & s, char & i);
//inline void __exchange(::payload_stream & s, short & i);
//inline void __exchange(::payload_stream & s, int & i);
//inline void __exchange(::payload_stream & s, long long & i);
//#if !defined(LINUX)
//inline void __exchange(::payload_stream & s, long & l);
//#endif
//inline void __exchange(::payload_stream & s, unsigned char & u);
//inline void __exchange(::payload_stream & s, unsigned short & u);
//inline void __exchange(::payload_stream & s, unsigned int & u);
//inline void __exchange(::payload_stream & s, unsigned long long & u);
//inline void __exchange(::payload_stream & s, float & f);
//inline void __exchange(::payload_stream & s, double & d);
//inline void __exchange(::payload_stream & s, ::earth::time & time);
//inline void __exchange(::payload_stream & s, const ::scoped_string & scopedstr);
//inline void __exchange(::payload_stream & s, string & str);
//inline void __exchange(::payload_stream & s, ::file::path & path);
//inline void __exchange(::payload_stream & s, ::atom & atom);
//inline void __exchange(::payload_stream & s, ::payload & payload);
//inline void __exchange(::payload_stream & s, ::property & property);
//inline void __exchange(::payload_stream & s, ::property_set & set);
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
//inline void __exchange(::payload_stream& s, ::pointer<OBJECT> pparticle);
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
//inline void __exchange(::payload_stream& stream, ::array_base < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >& array);
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
//inline void __exchange(::payload_stream& s, const ::raw_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >& array);
//
//template < typename TYPE, ::enum_type t_etypeContainer = e_type_element >
//inline void __exchange(::payload_stream& s, const ::numeric_array < TYPE, t_etypeContainer >& array);
//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//inline void __exchange(::payload_stream& s, const ::string_array_base < Type, RawType, t_etypeContainer >& array);
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
//   //virtual void write_object(const ::atom & atom, ::particle * pparticle) ;
//   //virtual ::pointer<::matter>read_object(const ::atom & atom) ;
//
//
//   virtual void read(block & block) ;
//   virtual void write(const block & block) ;
//
//
//   virtual void exchange(const ::atom & atom, double & d) ;
//   virtual void exchange(const ::atom& atom, long long& i) ;
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
