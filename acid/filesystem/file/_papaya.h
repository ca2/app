#pragma once


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type t_etypeContainer >
//void __io_array(stream & stream, ::array_base < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & array);

//template < typename ARRAY, typename READER >
//inline void __load_array(ARRAY & array, READER && reader);

//template < typename ARRAY, typename WRITER >
//inline void __save_array(ARRAY & array, WRITER && writer);


CLASS_DECL_ACID void __transfer_to_writable(::file::writable * pwritable, ::file::file * pfileIn, memsize uiBufSize =-1);

namespace acid
{


   namespace array
   {


   } // namespace array


} // namespace acid





//template < class T >
//inline stream & operator << (stream & os, const pointer < T > & sp);
//
//
//template < class T >
//inline stream & operator >> (stream & is, pointer < T > & sp);


