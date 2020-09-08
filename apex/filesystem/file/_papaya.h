#pragma once


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
void __io_array(stream & stream, ::array_base < TYPE, ARG_TYPE, ALLOCATOR > & array);

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





template < class T >
inline stream & operator << (stream & os, const pointer < T > & sp);


template < class T >
inline stream & operator >> (stream & is, pointer < T > & sp);


