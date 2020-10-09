#pragma once


class var_stream;


inline void __exchange(::var_stream & s, bool & b);
inline void __exchange(::var_stream & s, i8 & i);
inline void __exchange(::var_stream & s, i16 & i);
inline void __exchange(::var_stream & s, i32 & i);
inline void __exchange(::var_stream & s, i64 & i);
#if !defined(LINUX)
inline void __exchange(::var_stream & s, LONG & l);
#endif
inline void __exchange(::var_stream & s, u8 & u);
inline void __exchange(::var_stream & s, u16 & u);
inline void __exchange(::var_stream & s, u32 & u);
inline void __exchange(::var_stream & s, u64 & u);
inline void __exchange(::var_stream & s, float & f);
inline void __exchange(::var_stream & s, double & d);
inline void __exchange(::var_stream & s, ::datetime::time & time);
inline void __exchange(::var_stream & s, const char * psz);
inline void __exchange(::var_stream & s, string & str);
inline void __exchange(::var_stream & s, ::file::path & path);
inline void __exchange(::var_stream & s, ::id & id);
inline void __exchange(::var_stream & s, ::var & var);
inline void __exchange(::var_stream & s, ::property & property);
inline void __exchange(::var_stream & s, ::property_set& set);
inline void __exchange(::var_stream & s, ::block & block);
inline void __exchange(::var_stream & s, ::int_array & ia);
inline void __exchange(::var_stream & s, ::string_array & stra);
inline void __exchange(::var_stream & s, ::memory & memory);






inline void __exchange(::var_stream & s, ::element & element);


template < typename OBJECT >
inline void __exchange(::var_stream& s, __pointer(OBJECT)& pobject);

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void __exchange(::var_stream& stream, ::array_base < TYPE, ARG_TYPE, ALLOCATOR >& array);

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void __exchange(::var_stream& s, const ::raw_array < TYPE, ARG_TYPE, ALLOCATOR >& array);

template < class TYPE >
inline void __exchange(::var_stream& s, const ::numeric_array < TYPE >& array);

template < typename Type, typename RawType >
inline void __exchange(::var_stream& s, const ::string_array_base < Type, RawType >& array);


template < class ARRAY >
inline void __exchange_array(::var_stream& stream, ARRAY& array);

template < typename ARRAY >
inline void __exchange_save_array(::var_stream& s, ARRAY& array);

template < typename ARRAY >
inline void __exchange_load_array(::var_stream& s, ARRAY& array);


class CLASS_DECL_ACME var_stream :
   public stream
{
public:


   class var *          m_pvar;


   var_stream();
   var_stream(class ::var * pvar);
   virtual ~var_stream();


   class var & var();
   const class var & var() const;


   template < typename TYPE >
   void default_exchange(TYPE & t);

   template < typename TYPE >
   void write_only(TYPE & t);

   template < typename TYPE >
   void var_exchange(const ::id & id, TYPE & t);

   //virtual void write_object(const ::id & id, ::element * pobject) override;
   //virtual __pointer(::element) read_object(const ::id & id) override;


   virtual void read(block & block) override;
   virtual void write(const block & block) override;


   virtual void exchange(const ::id & id, double & d) override;
   virtual void exchange(const ::id& id, i64& i) override;


   template < typename TYPE >
   inline void stream_exchange(const ::id& id, TYPE& t);


};





