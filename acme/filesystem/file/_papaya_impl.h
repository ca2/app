#pragma once


//inline ::file_pointer matter::get_reader(const ::payload & payloadFile, const ::file::e_open & eopen)
//{
//
//   return m_pcontext->m_papexcontext->file().get_reader(payloadFile, eopen);
//
//}
//
//
//inline ::file_pointer matter::get_writer(const ::payload & payloadFile, const ::file::e_open & eopen)
//{
//
//   return m_pcontext->m_papexcontext->file().get_writer(payloadFile, eopen);
//
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//void __io_array(stream & stream, ::array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > & array)
//{
//
//  if (stream.is_storing())
//  {
//
//     stream << array;
//
//  }
//  else
//  {
//
//     stream >> array;
//
//  }
//
//}


////template < typename ARRAY, typename READER >
////inline void __load_array(ARRAY & array, READER && reader)
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline stream & operator >>(stream & stream, ::array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > & array)
//{
//
//   ::count cSerialized = 0;
//
//   ::count c = 0;
//
//   stream >> c;
//
//   //if (!stream.fail())
//   {
//
//      //try
//      //{
//
//         for (::index i = 0; i < c; i++)
//         {
//
//            array.set_size(i + 1, minimum((size_t)(c - i), 96_mb / sizeof(array[0])));
//
//            auto & item = __typed(array[i]);
//
//            stream >> item;
//
//            //if (stream.fail())
//            //{
//
//            //   break;
//
//            //}
//
//            cSerialized++;
//
//         }
//
//      //}
//      //catch (...)
//      //{
//
//      //   stream.set_fail_bit();
//
//      //}
//
//      //if (stream.fail())
//      //{
//
//      //   array.set_size((::count) cSerialized);
//
//      //}
//
//   }
//
//   return stream;
//
//}
//
////template < typename ARRAY, typename WRITER >
////inline void __save_array(ARRAY & array, WRITER && writer)
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
//inline stream & operator <<(stream & stream, const ::array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > & array)
//{
//
//   ::count c = array.get_count();
//
//   stream << c;
//
//   for (auto & matter : array.values())
//   {
//
//      stream << matter;
//
//      //if (stream.fail())
//      //{
//
//      //   break;
//
//      //}
//
//   }
//
//   return stream;
//
//}
//

namespace acme
{


   namespace array
   {



   } // namespace array


} // namespace acme




