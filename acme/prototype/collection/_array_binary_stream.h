// From file/binary_stream.h by camilo on 2022-10-14 23:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/binary_stream.h"


template < prototype_serializable_array<binary_stream> SERIALIZABLE_ARRAY >
inline binary_stream & operator <<(binary_stream & stream, const SERIALIZABLE_ARRAY & a)
{

   return stream.write_serializable_array(a);

   // ::collection::count c = a.get_count();
   
   // stream << c;

   // for (auto & element : a)
   // {
      
   //    stream << element;

   //    if (stream. nok())
   //    {

   //       break;

   //    }

   // }

   // return stream;

}


template < prototype_serializable_array<binary_stream> SERIALIZABLE_ARRAY >
binary_stream & operator >>(binary_stream & stream, SERIALIZABLE_ARRAY & a)
{

   stream.read_serializable_array(a);

   // ::collection::count c;
   
   // stream >> c;
   
   // if (stream.nok() || c <= 0)
   // {

   //    return stream  ;

   // }
   
   // a.set_size(c);

   // ::collection::index i = 0;

   // try
   // {

   //    for (; i < c && stream.has_ok_flag(); i++)
   //    {

   //             stream >> a[i];

   //    }

   // }
   // catch (...)
   // {

   //    stream.set_nok();

   // }

   // if (stream.nok())
   // {

   //    a.set_size(i);

   // }

   // return stream;

}



template < prototype_writable_array<binary_stream> WRITABLE_ARRAY >
inline binary_stream & operator <<(binary_stream & stream, const WRITABLE_ARRAY & a)
{

   return stream.write_array(a);

   // ::collection::count c = a.get_count();
   
   // stream << c;

   // for (auto & element : a)
   // {
      
   //    stream.write(element);

   //    if (stream. nok())
   //    {

   //       break;

   //    }

   // }

   // return stream;

}


template < prototype_readable_array<binary_stream> READABLE_ARRAY >
binary_stream & operator >>(binary_stream & stream, READABLE_ARRAY & a)
{

   return stream.read_array(a);

   // ::collection::count c;
   
   // stream >> c;
   
   // if (stream.nok() || c <= 0)
   // {

   //    return stream  ;

   // }
   
   // a.set_size(c);

   // ::collection::index i = 0;

   // try
   // {

   //    for (; i < c && stream.has_ok_flag(); i++)
   //    {

   //       stream.read(a[i]);

   //    }

   // }
   // catch (...)
   // {

   //    stream.set_nok();

   // }

   // if (stream.nok())
   // {

   //    a.set_size(i);

   // }

   // return stream;

}



template<prototype_double_angle_bracket_writable_array<::binary_stream> DOUBLE_ANGLE_BRACKET_WRITABLE_ARRAY>
inline binary_stream &operator<<(binary_stream &stream, const DOUBLE_ANGLE_BRACKET_WRITABLE_ARRAY &a)
   requires(!prototype_raw_array_class<DOUBLE_ANGLE_BRACKET_WRITABLE_ARRAY>)
{

   return stream.double_angle_bracket_write(a);

   // ::collection::count c = a.get_count();

   // stream << c;

   // for (auto & element : a)
   // {

   //    stream.write(element);

   //    if (stream. nok())
   //    {

   //       break;

   //    }

   // }

   // return stream;
}


template<prototype_double_angle_bracket_readable_array<::binary_stream> DOUBLE_ANGLE_BRACKET_READABLE_ARRAY>
binary_stream &operator>>(binary_stream &stream, DOUBLE_ANGLE_BRACKET_READABLE_ARRAY &a) 
   requires(!prototype_raw_array_class<DOUBLE_ANGLE_BRACKET_READABLE_ARRAY>)
{

   return stream.double_angle_bracket_read(a);

   // ::collection::count c;

   // stream >> c;

   // if (stream.nok() || c <= 0)
   // {

   //    return stream  ;

   // }

   // a.set_size(c);

   // ::collection::index i = 0;

   // try
   // {

   //    for (; i < c && stream.has_ok_flag(); i++)
   //    {

   //       stream.read(a[i]);

   //    }

   // }
   // catch (...)
   // {

   //    stream.set_nok();

   // }

   // if (stream.nok())
   // {

   //    a.set_size(i);

   // }

   // return stream;
}

template<prototype_raw_array_class RAW_ARRAY_CLASS>
binary_stream & operator <<(binary_stream & stream, const RAW_ARRAY_CLASS & a)
{

   return stream.write_raw_array(a);

   // ::collection::count c = a.get_count();

   // stream << c;

   // stream.write({ a.get_data(), sizeof(typename ARRAY::BASE_TYPE) * c});

   // return stream;

}

template<prototype_raw_array_class RAW_ARRAY_CLASS>
binary_stream & operator >>(binary_stream & stream, RAW_ARRAY_CLASS & a)
{

   return stream.read_raw_array(a);
   
   // ::collection::count c;
   
   // stream >> c;
   
   // if (stream.nok())
   // {
      
   //    return stream;
      
   // }
   
   // a.set_size(c);
   
   // auto iRead = m_pfile->read({ a.get_data(), sizeof(typename ARRAY::BASE_TYPE) * c });
   
   // if (stream.nok() || iRead < (memsize)(sizeof(typename ARRAY::BASE_TYPE) * c))
   // {
      
   //    a.set_size(iRead / sizeof(typename ARRAY::BASE_TYPE));
      
   // }
   
   // return stream;
   
}



template<polymorphic_smart_pointer_array POLYMORPHIC_SMART_POINTER_ARRAY>
inline binary_stream & operator <<(binary_stream & stream, const POLYMORPHIC_SMART_POINTER_ARRAY & a)
{

   return stream.write_polymorphic_pointer_array(a);

   // ::collection::count c = a.get_count();

   // stream << c;

   // for (auto & p : a)
   // {

   //    stream.write_polymorphic_type(p);

   //    if (stream.nok())
   //    {

   //       break;

   //    }

   // }

   // return stream;

}


template < polymorphic_smart_pointer_array POLYMORPHIC_SMART_POINTER_ARRAY >
inline binary_stream & operator >>(binary_stream & stream, POLYMORPHIC_SMART_POINTER_ARRAY & a)
{

return stream.read_polymorphic_pointer_array(a);

   // ::collection::count c;

   // stream >> c;

   // if (stream.nok())
   // {

   //    return stream;

   // }

   // a.set_size(c);

   // ::collection::index i = 0;

   // try
   // {

   //    for (; i < c && stream.has_ok_flag(); i++)
   //    {

   //       a[i] = stream.read_particle();

   //    }

   // }
   // catch (...)
   // {

   //    stream.set_nok();

   // }

   // if (stream.nok())
   // {

   //    a.set_size(i);

   // }

   // return stream;

}


template < prototype_raw_pointer_array RAW_POINTER_ARRAY >
inline binary_stream & operator <<(binary_stream & stream, const RAW_POINTER_ARRAY & a)
{

   return stream.write_raw_pointer_array(a);

}

 
// template < prototype_raw_pointer_array RAW_POINTER_ARRAY >
// inline binary_stream & read_raw_pointer_array(ARRAY & a)
// {

//    ::collection::count c;
   
//    *this >> c;

//    if (this->nok())
//    {

//       return *this;

//    }

//    a.set_size(c);

//    ::collection::index i = 0;

//    try
//    {

//       for (; i < c && this->has_ok_flag(); i++)
//       {
         
//          auto p = ___new typename ARRAY::BASE_TYPE();
         
//          a[i] = p;

//          *this >> *p;

//       }

//    }
//    catch (...)
//    {

//          this->set_nok();

//    }

//    if (this->nok())
//    {

//       a.set_size(i);

//    }

//    return *this;

// }



// template<typename ARRAY>
// inline binary_stream &create_read_raw_pointer_array(ARRAY &a)
// {

//    ::collection::count c;

//    *this >> c;

//    if (this->nok())
//    {

//       return *this;
//    }

//    a.set_size(c);

//    ::collection::index i = 0;

//    try
//    {

//       for (; i < c && this->has_ok_flag(); i++)
//       {

//          auto p = ___new typename ARRAY::BASE_TYPE();

//          a[i] = p;

//          *this >> *p;
//       }
//    }
//    catch (...)
//    {

//       this->set_nok();
//    }

//    if (this->nok())
//    {

//       a.set_size(i);
//    }

//    return *this;
// }


template<prototype_raw_pointer_array RAW_POINTER_ARRAY>
inline binary_stream &operator >>(binary_stream & stream, RAW_POINTER_ARRAY & a)
{

   return stream.read_raw_pointer_array(a);

}



CLASS_DECL_ACME binary_stream & operator <<(binary_stream & stream, const ::property_set & propertyset);
CLASS_DECL_ACME binary_stream & operator >>(binary_stream & stream, ::property_set & propertyset);


CLASS_DECL_ACME binary_stream& binary_stream_write_property(::binary_stream& stream, const property& property);
CLASS_DECL_ACME binary_stream& binary_stream_read_property(::binary_stream& stream, property& property);


inline binary_stream & operator <<(binary_stream & stream, const ::property * pproperty)
{

   return binary_stream_write_property(stream, *pproperty);

}


inline binary_stream & operator >>(binary_stream & stream, ::property * pproperty)
{

   return binary_stream_read_property(stream, *pproperty);

}




