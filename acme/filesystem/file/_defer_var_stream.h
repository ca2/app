#pragma once



template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void __exchange(::var_stream& stream, ::array_base < TYPE, ARG_TYPE, ALLOCATOR >& array)
{

   __exchange_array(stream, array);

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void __exchange(::var_stream& stream, ::raw_array < TYPE, ARG_TYPE, ALLOCATOR >& array)
{

   __exchange_array(stream, array);

}


template < class TYPE >
inline void __exchange(::var_stream& stream, ::numeric_array < TYPE >& array)
{

   __exchange_array(stream, array);

}


template < typename Type, typename RawType >
inline void __exchange(::var_stream& stream, ::string_array_base < Type, RawType >& array)
{

   __exchange_array(stream, array);

}


template < class ARRAY >
inline void __exchange_array(::var_stream& stream, ARRAY& array)
{

   if (stream.is_storing())
   {

      __exchange_save_array(stream, array);

   }
   else
   {

      __exchange_load_array(stream, array);
   }

}


template < typename ARRAY >
inline void __exchange_save_array(::var_stream& stream, ARRAY& array)
{

   auto c = array.get_count();

   stream.stream_exchange(e_property_count, c);

   if (stream.fail())
   {

      return;

   }

   for (index i = 0; i < c; i++)
   {

      stream.stream_exchange(i, __typed(array.element_at(i)));

      if (stream.fail())
      {

         return;

      }

   }

}


template < typename ARRAY >
inline void __exchange_load_array(::var_stream& stream, ARRAY& array)
{

   auto c = array.get_count();

   stream.stream_exchange(e_property_count, c);

   if (stream.fail())
   {

      return;

   }

   array.set_size(c);

   for (index i = 0; i < c; i++)
   {

      auto& t = __typed_defer_new(array.element_at(i));

      stream.stream_exchange(i, t);

      if (stream.fail())
      {

         array.set_size(i);

         return;

      }

   }

}





template < typename OBJECT >
inline void __exchange(::var_stream& s, __pointer(OBJECT)& pobject)
{

   __exchange(s, __typed_defer_create(pobject));

}


template < typename TYPE >
inline void var_stream::stream_exchange(const ::id& id, TYPE& t) 
{ 
   
   var_exchange(id, t); 

}




