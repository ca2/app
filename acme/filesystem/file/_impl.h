#pragma once


template < typename TYPE >
inline void __string_exchange(::stream & s, TYPE & t)
{

   // __string_exchange and __exchange may mutually call each other, causing infinite recursion
   // if a certain TYPE causes infinite recursion, either a customized __string_exchange
   // or __exchange function for that type should be declared and implemented.
   __exchange(s, t);

}


template < typename TYPE >
inline void __object_string_exchange(::stream & s, TYPE & t)
{

   if (s.is_storing())
   {

      string str;

      str = t.to_string();

      __string_exchange(s, str);

   }
   else
   {

      string str;

      __string_exchange(s, str);

      t.from_string(str);

   }

}


inline void __string_exchange(stream & s, payload & payload) { s.default_exchange(payload.get_ref_string()); }

template < typename BLOCK_TYPE >
inline void __exchange(stream & s, memory_template < BLOCK_TYPE > & memorytemplate)
{

   auto block = memorytemplate.block();

   if(s.is_loading())
   {

      s.read(block);

   }
   else
   {

      s.write(block);

   }

}

inline void __exchange(stream & s, memory_base & memory)
{
   s.is_loading() ? s.read(memory) : s.write(memory);
}

//template < typename BLOCK_TYPE >
//inline void __exchange(var_stream & s, memory_template < BLOCK_TYPE > & block)
//{
//   s.default_exchange(block);
//}

inline stream & operator <<(stream & s, const ::millis & millis)
{

   s << millis.m_iMilliseconds;

   return s;

}



inline stream & operator >>(stream & s, ::millis & millis)
{

   s >> millis.m_iMilliseconds;

   return s;

}


//inline stream & stream::operator << (e_set_storing) { set_storing(); return *this; }
//inline stream & stream::operator >> (e_set_loading) { set_loading(); return *this; }


//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//stream & stream::operator << (const array_base < TYPE, ARG_TYPE, ALLOCATOR > & a)
//{

//   ::count c = a.get_count();

//   operator()(c);

//   write(a.get_data(), c * sizeof(a.get_data()[0]));

//   return *this;

//}


//template < class TYPE, class ARG_TYPE , class ALLOCATOR >
//stream & stream::operator >> (array_base < TYPE, ARG_TYPE, ALLOCATOR > & a)
//{

//   ::count c = 0;
//   operator()(c);
//   try
//   {
//      a.set_size(c);
//   }
//   catch (...)
//   {
//      __throw(io_exception());
//   }
//   if (!s.fail())
//   {
//      memsize size = c * sizeof(a.get_data()[0]);
//      if (read(a.get_data(), size) != size)
//      {
//         __throw(io_exception());
//      }
//   }

//   return *this;

//}


//template < typename SET >
//stream & stream::write_set(const SET & s)
//{
//   ::count c = s.get_count();
//   operator()(c);
//   for (auto & matter : s)
//   {
//      operator()(matter);
//      if (s.fail())
//         break;
//   }
//   return *this;
//}


//template < typename SET >
//stream & stream::wread_set(SET & s)
//{
//
//   ::count c = 0;
//   operator()(c);
//   while (c > 0)
//   {
//      c--;
//      typename SET::BASE_TYPE matter;
//      operator()(matter);
//      if (s.fail())
//         break;
//      s.add(matter);
//   }
//   return * this;
//}


template < class STREAM, class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR >
inline void __exchange(STREAM & s, map < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR > & m)
{

   if (s.is_storing())
   {

      ::count c = m.get_count();

      s << c;

      for (auto& pair : m)
      {

         s << pair.element1();

         if (s.fail())
            break;

         s << pair.element2();

         if (s.fail())
            break;

      }

   }
   else
   {

      ::count c = 0;

      s >> c;

      while (c > 0)
      {

         c--;
         typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR >::BASE_KEY element1;
         //typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR >::BASE_VALUE element2;
         s >> element1;
         if (s.fail())
            break;
         s >> m[element1];
         if (s.fail())
            break;
         //m.set_at(element1, element2);
      }

   }


}




template < typename TYPE >
inline stream & operator <<(stream & s, const __pointer_array(TYPE) & a)
{

   ::count c = a.get_count();

   s << c;

   for (auto & matter : a.ptra())
   {

      if (matter.is_null())
      {

         s.set_fail_bit();

         return s;

      }

      __save_object(s, matter);

      if (s.fail())
      {

         s.set_fail_bit();

      }

   }

   return s;

}


template < typename TYPE >
inline stream & operator >>(stream & s, __pointer_array(TYPE) & a)
{

   ::count c = 0;

   s >> c;

   if (c < 0)
   {

      s.set_fail_bit();

   }
   else
   {

      index i = 0;

      for (; i < c; i++)
      {

         auto pmatter = __load_object < TYPE >(s);

         if (s.fail() || !pmatter)
         {

            s.set_fail_bit();

            break;

         }

         a.add(pmatter);

      }

   }

   return s;

}


//template < typename TYPE >
//void stream::write_array_2d(const __pointer_array(TYPE) & a)
//{
//
//   if (is_storing())
//   {
//
//      ::count c = a.get_count();
//
//      operator()(c);
//
//      for (auto & matter : a.ptra())
//      {
//
//         if (matter.is_null())
//         {
//
//            s.set_fail_bit()();
//
//            return;
//
//         }
//
//         stream_array(*matter);
//
//         if (s.fail())
//         {
//
//            s.set_fail_bit()();
//
//         }
//
//      }
//
//   }
//   else
//   {
//      ::count c = 0;
//
//      operator()(c);
//
//      if (c < 0)
//      {
//
//         s.set_fail_bit()();
//
//         return;
//
//      }
//
//      index i = 0;
//
//      for (; i < c; i++)
//      {
//
//         __pointer(TYPE) pmatter;
//
//         pmatter->alloc(get_object());
//
//         stream_array(*pmatter);
//
//         if (s.fail() || pmatter->is_null())
//         {
//
//            s.set_fail_bit()();
//
//            return;
//
//         }
//
//         a.add(pmatter);
//
//      }
//
//   }
//
//}
//
//
//inline void stream::prop_read_start(::property_set & set)
//{
//
//   m_pset = &set;
//
//   m_pset->read(*this);
//
//}
//
//
//inline void stream::prop_write_end()
//{
//
//   m_pset->write(*this);
//
//   m_pset = nullptr;
//
//}




inline stream & operator <<(stream & s, const ::datetime::time & time)
{

   s << time.m_time;

   return s;

}



inline stream & operator >>(stream & s, ::datetime::time & time)
{

   s >> time.m_time;

   return s;

}



inline stream & operator <<(stream & s, const ::memory_base & memory)
{

   s.write(memory);

   return s;

}



inline stream & operator >>(stream & s, ::memory_base & memory)
{

   s.read(memory);

   return s;

}




inline stream & operator >>(stream & s, ::datetime::zonetime & z)
{

   s.write((i64)z.m_time);
   s.write((i32)z.m_iZoneOffset);

   return s;

}



inline stream & operator <<(stream & s, const ::datetime::zonetime & z)
{

   s.read((i64 &)z.m_time);
   s.read((i32 &)z.m_iZoneOffset);

   return s;

}





inline stream & operator << (stream & s, ::file::file * pfile)
{

   memory m;

   m.set_size(min((memsize)pfile->get_remaining_byte_count(), (memsize)1024 * 1024));

   memsize sizeRead;

   while ((sizeRead = pfile->read(m.get_data(), m.get_size())) > 0)
   {

      s.write((const void *) m.get_data(), sizeRead);

   }

   return s;

}












template < typename BASE_TYPE >
__pointer(BASE_TYPE) __load_object(stream & stream)
{

   string strText;

   stream >> strText;

   if (strText.is_empty())
   {

      stream.setstate(::file::failbit);

      return nullptr;

   }

   //auto id = stream.text_to_factory_id(strText);

   if (!strText.begins_eat_ci("factoryless://"))
   {

      strText = stream.text_to_factory_id(strText);

   }

   __pointer(matter) p = stream.create_object_from_text(strText);

   if (!p)
   {

      stream.setstate(::file::failbit);

      return nullptr;

   }

   p->exchange(stream);

   return p;

}



template < typename BASE_TYPE >
inline stream & __save_object(stream & stream, BASE_TYPE * p)
{

   string strText;

   auto type = p->type_name();

   if (p->has(e_object_factory))
   {

      strText = stream.factory_id_to_text(::str::demangle(type));

   }
   else
   {

      strText = "factoryless://" + ::str::demangle(type);

   }

   stream << strText;

   p->exchange(stream);

   return stream;

}


//template < typename BASE_TYPE >
//void matter::save_to(const payload & varFile, BASE_TYPE * pobject)
//{
//
//   auto writer = Context.file().get_writer(varFile, ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_truncate | ::file::e_open_defer_create_directory | ::file::e_open_share_exclusive);
//
//   __save_object(writer, pobject);
//
//}

//
//inline void __io(::stream & s, ::payload & payload) { s.io(payload); }
//
//
//inline void __io(::stream & s, const enum_type & etype) { s.io(etype); }
//
//
//inline void __io(::stream & s, const char * psz) { s.io(psz); }
//
//
//inline void __io(::stream & s, ::ansistring & str) { s.io(str); }
//
//
//inline void __io(::stream & s, ::wd16string & str) { s.io(str); }
//
//
//inline void __io(::stream & s, ::wd32string & str) { s.io(str); }
//
//
//inline void __io(::stream & s, ::file::path & path) { s.io(path); }
//
//
//inline void __io(::stream & s, bool & b) { s.io(b); }
//
//
//inline void __io(::stream & s, ::i8 & i) { s.io(i); }
//
//
//inline void __io(::stream & s, ::i16 & i) { s.io(i); }
//
//
//inline void __io(::stream & s, ::i32 & i) { s.io(i); }
//
//
//inline void __io(::stream & s, ::i64 & i) { s.io(i); }
//
//
//inline void __io(::stream & s, ::u8 & u) { s.io(u); }
//
//
//inline void __io(::stream & s, ::u16 & u) { s.io(u); }
//
//
//inline void __io(::stream & s, ::u32 & u) { s.io(u); }
//
//
//inline void __io(::stream & s, ::u64 & u) { s.io(u); }
//
//inline void __io(property & property, ::matter & matter)
//{
//
//   matter.exchange(property.propset());
//
//}
//
//template < typename TYPE >
//inline void __io(property_set & set, const __pointer(TYPE) & p)
//{
//
//   ((TYPE *) p.m_p)->exchange(set[id].propset());
//
//}
//
//
//template < typename TYPE >
//inline void __io(property_set & set, __pointer(TYPE) & p)
//{
//
//   p->exchange(set[id].propset());
//
//}

template < typename ARRAY >
inline void __exchange_save_array(::stream & stream, ARRAY & array)
{

   auto c = array.get_count();

   stream.exchange(property_count, c);

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
inline void __exchange_load_array(::stream & stream, ARRAY & array)
{

   auto c = array.get_count();

   stream.exchange(property_count, c);

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


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void __exchange(::stream & stream, ::array_base < TYPE, ARG_TYPE, ALLOCATOR > & array)
{
   __exchange_array(stream, array);
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void __exchange(::stream & stream, ::raw_array < TYPE, ARG_TYPE, ALLOCATOR > & array)
{
   __exchange_array(stream, array);
}


template < class TYPE >
inline void __exchange(::stream & stream, ::numeric_array < TYPE > & array)
{
   __exchange_array(stream, array);
}


template < typename Type, typename RawType >
inline void __exchange(::stream & stream, ::string_array_base < Type, RawType > & array)
{
   __exchange_array(stream, array);
}


template < class ARRAY >
inline void __exchange_array(::stream & stream, ARRAY & array)
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


inline var_stream::var_stream() : m_pvar(new ::payload) {}
inline var_stream::var_stream(::payload * pvar) : m_pvar(pvar) {}

inline payload & var_stream::payload() { return *m_pvar; }
inline const payload & var_stream::payload() const { return *m_pvar; }

//void var_stream::write_object(const ::id & id, ::id & idFactory, ::matter * pobject)
//{
//   var_stream stream(new ::payload(&payload()[id].propset()));
//   stream.exchange("", idFactory);
//   pobject->exchange(stream);
//}

//
//__pointer(::matter) var_stream::read_object(const ::id & id)
//{
//   var_stream stream(new ::payload(&payload()[id].propset()));
//   ::id idFactory;
//   stream.exchange("", idFactory);
//   auto pobject = __id_create<::matter>(idFactory);
//   pobject->exchange(stream);
//   return pobject;
//}


inline void stream::exchange(const ::id & id, void * pdata, memsize s)
{
   if (is_storing())
   {
      ::memory mem(pdata, s);
      write(mem);
   }
   else
   {
      ::memory mem;
      read(mem);
      mem.copy_to(pdata, s);
   }
}

inline void __exchange(::stream & s, char & ch) { s.default_exchange(ch); }

#ifdef WINDOWS
inline void __exchange(::stream& s, unichar& wch) { s.default_exchange(wch); }
#endif


inline void __exchange(::stream & s, bool & b) { s.default_exchange(b); }



inline void __exchange(::stream & s, i8 & i) { s.default_exchange(i); }
inline void __exchange(::stream & s, i16 & i) { s.default_exchange(i); }
inline void __exchange(::stream & s, i32 & i) { s.default_exchange(i); }
inline void __exchange(::stream & s, i64 & i) { s.default_exchange(i); }

#if defined(__APPLE__)  || defined(ANDROID) || defined(RASPBIAN) || defined(WINDOWS)
inline void __exchange(::stream & s, long & l) { s.default_exchange(l); }
#endif

#if defined(__APPLE__) || defined(ANDROID) || defined(WINDOWS) || defined(RASPBIAN)
inline void __exchange(::stream& s, unsigned long& ul) { s.default_exchange(ul); }
//inline void __exchange(::stream& s, long& l) { s.default_exchange(l); }
//inline void __exchange(::stream & s, long long & ll);
#endif


inline void __exchange(::stream & s, u8 & u) { s.default_exchange(u); }
inline void __exchange(::stream & s, u16 & u) { s.default_exchange(u); }
inline void __exchange(::stream & s, u32 & u) { s.default_exchange(u); }
inline void __exchange(::stream & s, u64 & u) { s.default_exchange(u); }
inline void __exchange(::stream & s, float & f) { s.default_exchange(f); }
inline void __exchange(::stream & s, double & d) { s.default_exchange(d); }
inline void __exchange(::stream & s, ::datetime::time & time) { s.default_exchange(time.m_time); }
inline void __exchange(::stream & s, const char * psz) { s.write_only(psz); }
inline void __exchange(::stream & s, string & str) { s.default_exchange(str); }
inline void __exchange(::stream & s, ::file::path & path) { s.default_exchange(path); }
inline void __exchange(::stream & s, ::id & id) { s.default_exchange(id); }
inline void __exchange(::stream & s, ::payload & payload) { s.default_exchange(payload); }
inline void __exchange(::stream & s, ::property & property) { s.default_exchange(property); }
inline void __exchange(::stream & s, ::property_set & set) { s.default_exchange(set); }


inline void __exchange(::stream & s, ::block & block)
{

   s.default_exchange(block);

}


inline void __exchange(::stream & s, ::matter & matter)
{

   matter.exchange(s);

}


template < typename TYPE >
inline var_stream & operator >> (var_stream & stream, TYPE & t)
{

   stream.defer_set_loading(); stream.exchange(::id::e_type_null, t);

   return stream;

}


template < typename TYPE >
inline var_stream & operator << (var_stream & stream, const TYPE & t)
{

   stream.defer_set_storing(); stream.exchange(::id::e_type_null, (TYPE &)t);

   return stream;


}


template < typename TYPE >
inline text_stream & operator >> (text_stream & stream, TYPE & t)
{

   stream.defer_set_loading(); stream.exchange(::id::e_type_null, t);

   return stream;

}


template < typename TYPE >
inline text_stream & operator << (text_stream & stream, const TYPE & t)
{

   stream.defer_set_storing(); stream.exchange(::id::e_type_null, (TYPE &)t); return stream;

}


inline text_stream & operator << (text_stream & stream, const file_result & pfile)
{

   stream.defer_set_storing();

   stream.m_p->from(pfile);

   return stream;

}


inline void __exchange(::stream & s, RECT32 & rect)
{

   s.exchange("left", rect.left); s.exchange("top", rect.top); s.exchange("right", rect.right); s.exchange("bottom", rect.bottom);

}

inline void __exchange(::stream & s, RECT64 & rect)
{

   s.exchange("left", rect.left); s.exchange("top", rect.top); s.exchange("right", rect.right); s.exchange("bottom", rect.bottom);

}



inline void __exchange(::stream & s, RECTF & rect)
{
   s.exchange("left", rect.left); s.exchange("top", rect.top); s.exchange("right", rect.right); s.exchange("bottom", rect.bottom);
}



inline void __exchange(::stream & s, RECTD & rect)
{
   s.exchange("left", rect.left); s.exchange("top", rect.top); s.exchange("right", rect.right); s.exchange("bottom", rect.bottom);
}





inline void __exchange(::stream & s, SIZE32 & size)
{
   s.exchange("cx", size.cx); s.exchange("cy", size.cy);
}


//
//inline void __exchange(::stream & s, SIZEL & size)
//{
//   s.exchange("cx", size.cx); s.exchange("cy", size.cy);
//}
//
//



inline void __exchange(::stream & s, SIZEF & size)
{

   s.exchange("cx", size.cx); s.exchange("cy", size.cy);

}



inline void __exchange(::stream & s, SIZED & size)
{
   s.exchange("cx", size.cx); s.exchange("cy", size.cy);
}





inline void __exchange(::stream & s, POINT32 & point)
{
   s.exchange("x", point.x); s.exchange("y", point.y);
}



inline void __exchange(::stream & s, POINT64 & point)
{
   s.exchange("x", point.x); s.exchange("y", point.y);
}



inline void __exchange(::stream & s, POINTF & point)
{
   s.exchange("x", point.x); s.exchange("y", point.y);
}



inline void __exchange(::stream & s, POINTD & point)
{
   s.exchange("x", point.x); s.exchange("y", point.y);
}

template < typename TYPE >
inline stream & operator >> (stream & stream, TYPE & t);

template < typename TYPE >
inline stream & operator << (stream & stream, const TYPE & t);

template < typename TYPE >
inline binary_stream & operator >> (binary_stream & stream, TYPE & t)
{

   stream.defer_set_loading();

   stream.stream_exchange(::id::e_type_null, t);

   return stream;

}


template < typename TYPE >
inline binary_stream & operator << (binary_stream & stream, const TYPE & t)
{

   stream.defer_set_storing();

   stream.stream_exchange(::id::e_type_null, (TYPE &)t);

   return stream;

}

template < typename TYPE >
inline ::file::file & operator >> (::file::file & file, TYPE & t)
{

   if (::is_null_ref(file))
   {

      __throw(io_exception());

   }

   binary_stream stream(&file);

   stream >> t;

   return file;

}


template < typename TYPE >
inline ::file::file & operator << (::file::file & file, const TYPE & t)
{

   binary_stream stream(&file);

   stream << t;

   return file;

}

inline void assign(::memory & memory, const ::payload & payload)
{

   memory = (const ::memory &) payload;

}


template < typename TYPE >
void var_stream::default_exchange(TYPE & t)
{

   try
   {

      if(is_loading())
      {

         ::assign(t, *this->m_pvar);

      }
      else
      {

         ::assign(*this->m_pvar, t);

      }

  }
  catch (const ::exception_pointer & pe)
  {

     add_exception(pe);

  }
  catch (...)
  {

     on_catch_all_exception();

  }

}


template < typename TYPE >
void var_stream::write_only(TYPE & t)
{

  if (is_loading())
  {

     set_fail_bit();

  }
  else
  {

     payload() = t;

  }

}




template < typename TYPE >
inline void var_stream::var_exchange(const ::id & id, TYPE & t)
{

  ::payload * pvar = m_pvar;

  if (id.m_etype != id::e_type_null)
  {

     m_pvar = &m_pvar->operator[](id);

  }

  __exchange(*this, t);

  m_pvar = pvar;

}


#include "_var_stream_impl.h"



