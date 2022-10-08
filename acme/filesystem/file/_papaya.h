#pragma once


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//void __io_array(stream & stream, ::array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > & array);

//template < typename ARRAY, typename READER >
//inline void __load_array(ARRAY & array, READER && reader);

//template < typename ARRAY, typename WRITER >
//inline void __save_array(ARRAY & array, WRITER && writer);

template < typename WRITER >
void __transfer_to_writer(WRITER & writer, ::file::file * pfileIn, memsize uiBufSize =-1);

namespace papaya
{


   namespace array
   {


   } // namespace array


} // namespace papaya





//template < class T >
//inline stream & operator << (stream & os, const ___pointer < T > & sp);
//
//
//template < class T >
//inline stream & operator >> (stream & is, ___pointer < T > & sp);


