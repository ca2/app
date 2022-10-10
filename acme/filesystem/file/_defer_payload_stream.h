#pragma once



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
inline void __exchange(::payload_stream& stream, ::array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >& array)
{

   __exchange_array(stream, array);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, enum_type t_etypePayload >
inline void __exchange(::payload_stream& stream, ::raw_array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >& array)
{

   __exchange_array(stream, array);

}


template < typename TYPE, enum_type t_etypePayload >
inline void __exchange(::payload_stream& stream, ::numeric_array < TYPE, t_etypePayload >& array)
{

   __exchange_array(stream, array);

}


template < typename Type, typename RawType, enum_type t_etypePayload >
inline void __exchange(::payload_stream& stream, ::string_array_base < Type, RawType, t_etypePayload >& array)
{

   __exchange_array(stream, array);

}



template < class ARRAY >
inline void __exchange_array(::payload_stream& stream, ARRAY& array)
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
inline void __exchange_save_array(::payload_stream& stream, ARRAY& array)
{

   auto c = array.get_count();

   stream.stream_exchange(e_property_count, c);

   //if (stream.fail())
   //{

   //   return;

   //}

   for (index i = 0; i < c; i++)
   {

      stream.stream_exchange(i, __typed(array.element_at(i)));

      //if (stream.fail())
      //{

      //   return;

      //}

   }

}


template < typename ARRAY >
inline void __exchange_load_array(::payload_stream& stream, ARRAY& array)
{

   auto c = array.get_count();

   stream.stream_exchange(e_property_count, c);

   //if (stream.fail())
   //{

   //   return;

   //}

   array.set_size(c);

   for (index i = 0; i < c; i++)
   {

      auto& t = __typed_defer_new(array.element_at(i));

      stream.stream_exchange(i, t);

      //if (stream.fail())
      //{

      //   array.set_size(i);

      //   return;

      //}

   }

}





template < typename OBJECT >
inline void __exchange(::payload_stream& s, ::pointer<OBJECT> pobject)
{

   s.__defer_construct(pobject);

   __exchange(s, *pobject);

}


template < typename TYPE >
inline void payload_stream::stream_exchange(const ::atom& atom, TYPE& t) 
{ 
   
   var_exchange(atom, t); 

}




