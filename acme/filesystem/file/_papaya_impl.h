#pragma once


//inline ::file_result matter::get_reader(const ::var & varFile, const ::efileopen & efileopen)
//{
//
//   return Context.file().get_reader(varFile, efileopen);
//
//}
//
//
//inline ::file_result matter::get_writer(const ::var & varFile, const ::efileopen & efileopen)
//{
//
//   return Context.file().get_writer(varFile, efileopen);
//
//}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
void __io_array(stream & stream, ::array_base < TYPE, ARG_TYPE, ALLOCATOR > & array)
{

  if (stream.is_storing())
  {

     stream << array;

  }
  else
  {

     stream >> array;

  }

}


//template < typename ARRAY, typename READER >
//inline void __load_array(ARRAY & array, READER && reader)
template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline stream & operator >>(stream & stream, ::array_base < TYPE, ARG_TYPE, ALLOCATOR > & array)
{

   ::count cSerialized = 0;

   ::count c = 0;

   stream >> c;

   if (!stream.fail())
   {

      try
      {

         for (::index i = 0; i < c; i++)
         {

            array.set_size(i + 1, min((size_t)(c - i), 96_mb / sizeof(array[0])));

            auto & item = __typed(array[i]);

            stream >> item;

            if (stream.fail())
            {

               break;

            }

            cSerialized++;

         }

      }
      catch (...)
      {

         stream.set_fail_bit();

      }

      if (stream.fail())
      {

         array.set_size((::count) cSerialized);

      }

   }

   return stream;

}

//template < typename ARRAY, typename WRITER >
//inline void __save_array(ARRAY & array, WRITER && writer)
template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline stream & operator <<(stream & stream, const ::array_base < TYPE, ARG_TYPE, ALLOCATOR > & array)
{

   ::count c = array.get_count();

   stream << c;

   for (auto & matter : array.values())
   {

      stream << matter;

      if (stream.fail())
      {

         break;

      }

   }

   return stream;

}


namespace papaya
{


   namespace array
   {



   } // namespace array


} // namespace papaya




template < typename WRITER >
void __transfer_to_writer(WRITER & writer, ::file::file * pfileIn, memsize uiBufSize)
{


   if (pfileIn->get_internal_data() != nullptr && pfileIn->get_internal_data_size() > pfileIn->get_position())
   {

      writer.write((u8 *)pfileIn->get_internal_data() + pfileIn->get_position(), (memsize)(pfileIn->get_internal_data_size() - pfileIn->get_position()));

      return;

   }


   memsize uiRead;
   memsize uiSize = 0;
   uiBufSize = max(32 * 1024, uiBufSize);

   memory buf;

   buf.set_size(uiBufSize);

   if (buf.get_data() == nullptr)
      __throw(memory_exception());

   try
   {
      while (true)
      {
         uiRead = pfileIn->read(buf.get_data(), buf.get_size());
         if (uiRead <= 0)
         {
            break;
         }
         writer.write(buf.get_data(), uiRead);
         uiSize += uiRead;
      }
   }
   catch (...)
   {
   }

}
