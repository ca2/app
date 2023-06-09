#pragma once


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//void __io_array(stream & stream, ::array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & array);

//template < typename ARRAY, typename READER >
//inline void __load_array(ARRAY & array, READER && reader);

//template < typename ARRAY, typename WRITER >
//inline void __save_array(ARRAY & array, WRITER && writer);


CLASS_DECL_ACME void __transfer_to_writable(::file::writable * pwritable, ::file::file * pfileIn, memsize uiBufSize =-1);

namespace acme
{


   namespace array
   {


   } // namespace array


} // namespace acme





//template < class T >
//inline stream & operator << (stream & os, const pointer < T > & sp);
//
//
//template < class T >
//inline stream & operator >> (stream & is, pointer < T > & sp);


