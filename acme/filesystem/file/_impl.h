#pragma once




//template < typename TYPE >
//inline void __string_exchange(::binary_stream & s, TYPE & t)
//{
//
//   // __string_exchange and __exchange may mutually call each other, causing infinite recursion
//   // if a certain TYPE causes infinite recursion, either a customized __string_exchange
//   // or __exchange function for that type should be declared and implemented.
//   __exchange(s, t);
//
//}
//

//template < typename TYPE >
//inline void operator(::string & s, TYPE & t)
//{
//
//   if (s.is_storing())
//   {
//
//      t.to_string(str);
//
//   }
//   else
//   {
//
//      t.from_string(str);
//
//   }
//
//}


//inline void __string_exchange(binary_stream & s, ::payload & payload) { s.default_exchange(payload.string_reference()); }


//template < typename BLOCK_TYPE >
//inline void __exchange(binary_stream & s, memory_template < BLOCK_TYPE > & memorytemplate)
//{
//
//   auto block = memorytemplate.block();
//
//   if(s.is_loading())
//   {
//
//      s.read(block);
//
//   }
//   else
//   {
//
//      s.write(block);
//
//   }
//
//}
//
//inline void __exchange(binary_stream & s, memory_base & memory)
//{
//   s.is_loading() ? s.read(memory) : s.write(memory);
//}
//
////template < typename BLOCK_TYPE >
////inline void __exchange(payload_stream & s, memory_template < BLOCK_TYPE > & block)
////{
////   s.default_exchange(block);
////}
//



//
//
//
////inline binary_stream & operator >>(binary_stream & s, class ::time & class ::time)
////{
////
////   s >> class ::time.m_i;
////
////   return s;
////
////}
//
//
////inline binary_stream & binary_stream::operator << (e_set_storing) { set_storing(); return *this; }
////inline binary_stream & binary_stream::operator >> (e_set_loading) { set_loading(); return *this; }
//
//
////template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
////binary_stream & binary_stream::operator << (const array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & a)
////{
//
////   ::count c = a.get_count();
//
////   operator()(c);
//
////   write(a.get_data(), c * sizeof(a.get_data()[0]));
//
////   return *this;
//
////}
//
//
////template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
////binary_stream & binary_stream::operator >> (array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & a)
////{
//
////   ::count c = 0;
////   operator()(c);
////   try
////   {
////      a.set_size(c);
////   }
////   catch (...)
////   {
////      throw ::exception(error_io);
////   }
////   if (!s.fail())
////   {
////      memsize size = c * sizeof(a.get_data()[0]);
////      if (read(a.get_data(), size) != size_i32)
////      {
////         throw ::exception(error_io);
////      }
////   }
//
////   return *this;
//
////}
//
//
////template < typename SET >
////binary_stream & binary_stream::write_set(const SET & s)
////{
////   ::count c = s.get_count();
////   operator()(c);
////   for (auto & matter : s)
////   {
////      operator()(matter);
////      if (s.fail())
////         break;
////   }
////   return *this;
////}
//
//
////template < typename SET >
////binary_stream & binary_stream::wread_set(SET & s)
////{
////
////   ::count c = 0;
////   operator()(c);
////   while (c > 0)
////   {
////      c--;
////      typename SET::BASE_TYPE matter;
////      operator()(matter);
////      if (s.fail())
////         break;
////      s.add(matter);
////   }
////   return * this;
////}
//
//
//template < class STREAM, class KEY, class ARG_KEY, class PAYLOAD, class ARG_VALUE, class PAIR >
//inline void __exchange(STREAM & s, map < KEY, ARG_KEY, PAYLOAD, ARG_VALUE, PAIR > & m)
//{
//
//   if (s.is_storing())
//   {
//
//      ::count c = m.get_count();
//
//      s << c;
//
//      for (auto& pair : m)
//      {
//
//         s << pair.element1();
//
//         //if (s.fail())
//           // break;
//
//         s << pair.element2();
//
//         //if (s.fail())
//           // break;
//
//      }
//
//   }
//   else
//   {
//
//      ::count c = 0;
//
//      s >> c;
//
//      while (c > 0)
//      {
//
//         c--;
//         typename map < KEY, ARG_KEY, PAYLOAD, ARG_VALUE, PAIR >::BASE_KEY element1;
//         //typename map < KEY, ARG_KEY, PAYLOAD, ARG_VALUE, PAIR >::BASE_VALUE element2;
//         s >> element1;
//         //if (s.fail())
//           // break;
//         s >> m[element1];
//         //if (s.fail())
//           // break;
//         //m.set_at(element1, element2);
//      }
//
//   }
//
//
//}
//
//
//
//
//template < typename TYPE >
//inline binary_stream & operator <<(binary_stream & s, const pointer_array < TYPE > & a)
//{
//
//   ::count c = a.get_count();
//
//   s << c;
//
//   for (auto & matter : a.ptra())
//   {
//
//      if (matter.is_null())
//      {
//
//         throw ::exception(error_io);
//
//         return s;
//
//      }
//
//      __save_object(s, matter);
//
//      //if (s.fail())
//      //{
//
//      //   s.set_fail_bit();
//
//      //}
//
//   }
//
//   return s;
//
//}
//
//
//template < typename TYPE >
//inline binary_stream & operator >>(binary_stream & s, pointer_array < TYPE > & a)
//{
//
//   ::count c = 0;
//
//   s >> c;
//
//   if (c < 0)
//   {
//
//      throw ::exception(error_io);
//
//   }
//
//   index i = 0;
//
//   for (; i < c; i++)
//   {
//
//      auto pmatter = __load_object < TYPE >(s);
//
//      if (!pmatter)
//      {
//
//         throw ::exception(error_io);
//
//         break;
//
//      }
//
//      a.add(pmatter);
//
//   }
//
//   return s;
//
//}
//
//
////template < typename TYPE >
////void binary_stream::write_array_2d(const pointer_array < TYPE > & a)
////{
////
////   if (is_storing())
////   {
////
////      ::count c = a.get_count();
////
////      operator()(c);
////
////      for (auto & matter : a.ptra())
////      {
////
////         if (matter.is_null())
////         {
////
////            s.set_fail_bit()();
////
////            return;
////
////         }
////
////         stream_array(*matter);
////
////         if (s.fail())
////         {
////
////            s.set_fail_bit()();
////
////         }
////
////      }
////
////   }
////   else
////   {
////      ::count c = 0;
////
////      operator()(c);
////
////      if (c < 0)
////      {
////
////         s.set_fail_bit()();
////
////         return;
////
////      }
////
////      index i = 0;
////
////      for (; i < c; i++)
////      {
////
////         ::pointer<TYPE>pmatter;
////
////         pmatter->alloc(this);
////
////         stream_array(*pmatter);
////
////         if (s.fail() || pmatter->is_null())
////         {
////
////            s.set_fail_bit()();
////
////            return;
////
////         }
////
////         a.add(pmatter);
////
////      }
////
////   }
////
////}
////
////
////inline void binary_stream::prop_read_start(::property_set & set)
////{
////
////   m_ppropertyset = &set;
////
////   m_ppropertyset->read(*this);
////
////}
////
////
////inline void binary_stream::prop_write_end()
////{
////
////   m_ppropertyset->write(*this);
////
////   m_ppropertyset = nullptr;
////
////}



//// template < typename FILE >
//inline binary_stream & operator <<(binary_stream & s, const ::earth::time & time)
//{
//
//   s << time.m_i;
//
//   return s;
//
//}


//// template < typename FILE >
//inline binary_stream & operator >>(binary_stream & s, ::earth::time & time)
//{
//
//   s >> time.m_i;
//
//   return s;
//
//}

//
//
//inline binary_stream & operator <<(binary_stream & s, const ::memory_base & memory)
//{
//
//   s.write(memory);
//
//   return s;
//
//}
//
//
//
//inline binary_stream & operator >>(binary_stream & s, ::memory_base & memory)
//{
//
//   s.read(memory);
//
//   return s;
//
//}
//
//

//
//inline binary_stream & operator << (binary_stream & s, ::file::file * pfile)
//{
//
//   memory m;
//
//   m.set_size(minimum((memsize)pfile->get_remaining_byte_count(), (memsize)1024 * 1024));
//
//   memsize sizeRead;
//
//   while ((sizeRead = pfile->read(m.get_data(), m.get_size())) > 0)
//   {
//
//      s.write((const void *) m.get_data(), sizeRead);
//
//   }
//
//   return s;
//
//}
//
//
//template < typename BASE_TYPE >
//::pointer<BASE_TYPE>__load_object(binary_stream & binary_stream)
//{
//
//   string strText;
//
//   binary_stream >> strText;
//
//   if (strText.is_empty())
//   {
//
//      //binary_stream.setstate(::file::failbit);
//
//      throw ::exception(error_io);
//
//      return nullptr;
//
//   }
//
//   //auto atom = binary_stream.text_to_factory_id(strText);
//
//   if (!strText.case_insensitive_begins_eat("factoryless://"))
//   {
//
//      strText = as_string(binary_stream.text_to_factory_id(strText));
//
//   }
//
//   ::pointer<matter>p = binary_stream.create_object_from_text(strText);
//
//   if (!p)
//   {
//
//      throw ::exception(error_io);
//
//      return nullptr;
//
//   }
//
//   p->exchange(binary_stream);
//
//   return p;
//
//}
//
//
//
//template < typename BASE_TYPE >
//inline binary_stream & __save_object(binary_stream & binary_stream, BASE_TYPE * p)
//{
//
//   string strText;
//
//   auto type = __type_name(p);
//
//   if (p->has(e_flag_factory))
//   {
//
//      strText = binary_stream.factory_id_to_text(type);
//
//   }
//   else
//   {
//
//      strText = "factoryless://" + type;
//
//   }
//
//   binary_stream << strText;
//
//   p->exchange(binary_stream);
//
//   return binary_stream;
//
//}
//
//
////template < typename BASE_TYPE >
////void matter::save_to(const ::payload & payloadFile, BASE_TYPE * pparticle)
////{
////
////   auto writer = file()->get_writer(payloadFile, ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_truncate | ::file::e_open_defer_create_directory | ::file::e_open_share_exclusive);
////
////   __save_object(writer, pparticle);
////
////}
//
////
////inline void __io(::binary_stream & s, ::payload & payload) { s.io(payload); }
////
////
////inline void __io(::binary_stream & s, const enum_type & etype) { s.io(etype); }
////
////
////inline void __io(::binary_stream & s, const ::scoped_string & scopedstr) { s.io(psz); }
////
////
////inline void __io(::binary_stream & s, ::ansi_string & str) { s.io(str); }
////
////
////inline void __io(::binary_stream & s, ::wd16_string & str) { s.io(str); }
////
////
////inline void __io(::binary_stream & s, ::wd32_string & str) { s.io(str); }
////
////
////inline void __io(::binary_stream & s, ::file::path & path) { s.io(path); }
////
////
////inline void __io(::binary_stream & s, bool & b) { s.io(b); }
////
////
////inline void __io(::binary_stream & s, ::i8 & i) { s.io(i); }
////
////
////inline void __io(::binary_stream & s, ::i16 & i) { s.io(i); }
////
////
////inline void __io(::binary_stream & s, ::i32 & i) { s.io(i); }
////
////
////inline void __io(::binary_stream & s, ::i64 & i) { s.io(i); }
////
////
////inline void __io(::binary_stream & s, ::u8 & u) { s.io(u); }
////
////
////inline void __io(::binary_stream & s, ::u16 & u) { s.io(u); }
////
////
////inline void __io(::binary_stream & s, ::u32 & u) { s.io(u); }
////
////
////inline void __io(::binary_stream & s, ::u64 & u) { s.io(u); }
////
////inline void __io(property & property, ::matter & matter)
////{
////
////   matter.exchange(property.propset());
////
////}
////
////template < typename TYPE >
////inline void __io(property_set & set, const ::pointer<TYPE>& p)
////{
////
////   ((TYPE *) p.m_p)->exchange(set[atom].propset());
////
////}
////
////
////template < typename TYPE >
////inline void __io(property_set & set, ::pointer<TYPE>& p)
////{
////
////   p->exchange(set[atom].propset());
////
////}
//
//template < typename ARRAY >
//inline void __exchange_save_array(::binary_stream & binary_stream, ARRAY & array)
//{
//
//   auto c = array.get_count();
//
//   binary_stream.exchange(e_property_count, c);
//
//   //if (binary_stream.fail())
//   //{
//
//   //   return;
//
//   //}
//
//   for (index i = 0; i < c; i++)
//   {
//
//      binary_stream.stream_exchange(i, __typed(array.element_at(i)));
//
//      //if (binary_stream.fail())
//      //{
//
//      //   return;
//
//      //}
//
//   }
//
//}
//
//
//template < typename ARRAY >
//inline void __exchange_load_array(::binary_stream & binary_stream, ARRAY & array)
//{
//
//   auto c = array.get_count();
//
//   binary_stream.exchange(e_property_count, c);
//
//   //if (binary_stream.fail())
//   //{
//
//   //   return;
//
//   //}
//
//   array.set_size(c);
//
//   for (index i = 0; i < c; i++)
//   {
//
//      auto& t = __typed_defer_new(array.element_at(i));
//
//      binary_stream.stream_exchange(i, t);
//
//      //if (binary_stream.fail())
//      //{
//
//      //   array.set_size(i);
//
//      //   return;
//
//      //}
//
//   }
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline void __exchange(::binary_stream & binary_stream, ::array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & array)
//{
//   __exchange_array(binary_stream, array);
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline void __exchange(::binary_stream & binary_stream, ::raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & array)
//{
//   __exchange_array(binary_stream, array);
//}
//
//
//template < typename TYPE, ::enum_type m_etypeContainer >
//inline void __exchange(::binary_stream & binary_stream, ::numeric_array < TYPE, m_etypeContainer > & array)
//{
//   __exchange_array(binary_stream, array);
//}
//
//
//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//inline void __exchange(::binary_stream & binary_stream, ::string_array_base < Type, RawType, m_etypeContainer > & array)
//{
//   __exchange_array(binary_stream, array);
//}
//
//
//template < class ARRAY >
//inline void __exchange_array(::binary_stream & binary_stream, ARRAY & array)
//{
//
//   if (binary_stream.is_storing())
//   {
//
//      __exchange_save_array(binary_stream, array);
//
//   }
//   else
//   {
//
//      __exchange_load_array(binary_stream, array);
//   }
//
//}
//
//
//inline payload_stream::payload_stream() : m_ppayload(memory_new ::payload) {}
//inline payload_stream::payload_stream(::payload * pvar) : m_ppayload(pvar) {}
//
//inline ::payload & payload_stream::payload() { return *m_ppayload; }
//inline const ::payload & payload_stream::payload() const { return *m_ppayload; }
//
////void payload_stream::write_object(const ::atom & atom, ::atom & idFactory, ::particle * pparticle)
////{
////   payload_stream binary_stream(memory_new ::payload(&payload()[atom].propset()));
////   binary_stream.exchange("", idFactory);
////   pparticle->exchange(binary_stream);
////}
//
////
////::pointer<::matter>payload_stream::read_object(const ::atom & atom)
////{
////   payload_stream binary_stream(memory_new ::payload(&payload()[atom].propset()));
////   ::atom idFactory;
////   binary_stream.exchange("", idFactory);
////   auto pparticle = __id_create<::matter>(idFactory);
////   pparticle->exchange(binary_stream);
////   return pparticle;
////}
//
//
//inline void binary_stream::exchange(const ::atom & atom, void * pdata, memsize s)
//{
//   if (is_storing())
//   {
//      ::memory mem(pdata, s);
//      write(mem);
//   }
//   else
//   {
//      ::memory mem;
//      read(mem);
//      mem.copy_to(pdata, s);
//   }
//}
//
//inline void __exchange(::binary_stream & s, char & ch) { s.default_exchange(ch); }
//
//#ifdef WINDOWS
//inline void __exchange(::binary_stream& s, unichar& wch) { s.default_exchange(wch); }
//#endif
//
//
//inline void __exchange(::binary_stream & s, bool & b) { s.default_exchange(b); }
//
//
//
//inline void __exchange(::binary_stream & s, i8 & i) { s.default_exchange(i); }
//inline void __exchange(::binary_stream & s, i16 & i) { s.default_exchange(i); }
//inline void __exchange(::binary_stream & s, i32 & i) { s.default_exchange(i); }
//inline void __exchange(::binary_stream & s, i64 & i) { s.default_exchange(i); }
//
//#if defined(__APPLE__)  || defined(ANDROID) || defined(RASPBERRYPIOS) || defined(WINDOWS)
//inline void __exchange(::binary_stream & s, long & l) { s.default_exchange(l); }
//#endif
//
//#if defined(__APPLE__) || defined(ANDROID) || defined(WINDOWS) || defined(RASPBERRYPIOS)
//inline void __exchange(::binary_stream& s, unsigned long& ul) { s.default_exchange(ul); }
////inline void __exchange(::binary_stream& s, long& l) { s.default_exchange(l); }
////inline void __exchange(::binary_stream & s, long long & ll);
//#endif
//
//
//inline void __exchange(::binary_stream & s, u8 & u) { s.default_exchange(u); }
//inline void __exchange(::binary_stream & s, u16 & u) { s.default_exchange(u); }
//inline void __exchange(::binary_stream & s, u32 & u) { s.default_exchange(u); }
//inline void __exchange(::binary_stream & s, u64 & u) { s.default_exchange(u); }
//inline void __exchange(::binary_stream & s, float & f) { s.default_exchange(f); }
//inline void __exchange(::binary_stream & s, double & d) { s.default_exchange(d); }
//inline void __exchange(::binary_stream & s, ::earth::time & time) { s.default_exchange(time.m_i); }
//inline void __exchange(::binary_stream & s, class ::time & time) { s.default_exchange(time.m_iSecond); s.default_exchange(time.m_iNanosecond); }
//inline void __exchange(::binary_stream & s, const ::scoped_string & scopedstr) { s.write_only(psz); }
//inline void __exchange(::binary_stream & s, string & str) { s.default_exchange(str); }
//inline void __exchange(::binary_stream & s, ::file::path & path) { s.default_exchange(path); }
//inline void __exchange(::binary_stream & s, ::atom & atom) { s.default_exchange(atom); }
//inline void __exchange(::binary_stream & s, ::payload & payload) { s.default_exchange(payload); }
//inline void __exchange(::binary_stream & s, ::property & property) { s.default_exchange(property); }
//inline void __exchange(::binary_stream & s, ::property_set & set) { s.default_exchange(set); }
//
//
//inline void __exchange(::binary_stream & s, ::block & block)
//{
//
//   s.default_exchange(block);
//
//}
//
//
//inline void __exchange(::binary_stream & s, ::matter & matter)
//{
//
//   matter.exchange(s);
//
//}
//
//
//template < typename TYPE >
//inline payload_stream & operator >> (payload_stream & binary_stream, TYPE & t)
//{
//
//   binary_stream.defer_set_loading(); binary_stream.exchange(::atom::e_type_null, t);
//
//   return binary_stream;
//
//}
//
//
//template < typename TYPE >
//inline payload_stream & operator << (payload_stream & binary_stream, const TYPE & t)
//{
//
//   binary_stream.defer_set_storing(); binary_stream.exchange(::atom::e_type_null, (TYPE &)t);
//
//   return binary_stream;
//
//
//}
//
//
//template < typename TYPE >
//inline text_stream & operator >> (text_stream & binary_stream, TYPE & t)
//{
//
//   binary_stream.defer_set_loading(); binary_stream.exchange(::atom::e_type_null, t);
//
//   return binary_stream;
//
//}
//
//
//template < typename TYPE >
//inline text_stream & operator << (text_stream & binary_stream, const TYPE & t)
//{
//
//   binary_stream.defer_set_storing(); binary_stream.exchange(::atom::e_type_null, (TYPE &)t); return binary_stream;
//
//}
//
//
//inline text_stream & operator << (text_stream & binary_stream, const file_pointer & pfile)
//{
//
//   binary_stream.defer_set_storing();
//
//   binary_stream.m_p->from(pfile);
//
//   return binary_stream;
//
//}
//
//
//inline void __exchange(::binary_stream & s, ::rectangle_i32 & rectangle)
//{
//
//   s.exchange("left", rectangle.left); s.exchange("top", rectangle.top); s.exchange("right", rectangle.right); s.exchange("bottom", rectangle.bottom);
//
//}
//
//inline void __exchange(::binary_stream & s, ::rectangle_i64 & rectangle)
//{
//
//   s.exchange("left", rectangle.left); s.exchange("top", rectangle.top); s.exchange("right", rectangle.right); s.exchange("bottom", rectangle.bottom);
//
//}
//
//
//
//inline void __exchange(::binary_stream & s, ::rectangle_f32 & rectangle)
//{
//   s.exchange("left", rectangle.left); s.exchange("top", rectangle.top); s.exchange("right", rectangle.right); s.exchange("bottom", rectangle.bottom);
//}
//
//
//
//inline void __exchange(::binary_stream & s, ::rectangle_f64 & rectangle)
//{
//   s.exchange("left", rectangle.left); s.exchange("top", rectangle.top); s.exchange("right", rectangle.right); s.exchange("bottom", rectangle.bottom);
//}
//
//
//
//
//
//inline void __exchange(::binary_stream & s, ::size_i32 & size)
//{
//   s.exchange("cx", size.cx()); s.exchange("cy", size.cy());
//}
//
//
////
////inline void __exchange(::binary_stream & s, SIZEL & size)
////{
////   s.exchange("cx", size.cx()); s.exchange("cy", size.cy());
////}
////
////
//
//
//
//inline void __exchange(::binary_stream & s, ::size_f32 & size)
//{
//
//   s.exchange("cx", size.cx()); s.exchange("cy", size.cy());
//
//}
//
//
//
//inline void __exchange(::binary_stream & s, ::size_f64 & size)
//{
//   s.exchange("cx", size.cx()); s.exchange("cy", size.cy());
//}
//
//
//
//
//
//inline void __exchange(::binary_stream & s, ::point_i32 & point)
//{
//   s.exchange("x", point.x()); s.exchange("y", point.y());
//}
//
//
//
//inline void __exchange(::binary_stream & s, ::point_i64 & point)
//{
//   s.exchange("x", point.x()); s.exchange("y", point.y());
//}
//
//
//
//inline void __exchange(::binary_stream & s, ::point_f32 & point)
//{
//   s.exchange("x", point.x()); s.exchange("y", point.y());
//}
//
//
//
//inline void __exchange(::binary_stream & s, ::point_f64 & point)
//{
//   s.exchange("x", point.x()); s.exchange("y", point.y());
//}
//
//template < typename TYPE >
//inline binary_stream & operator >> (binary_stream & binary_stream, TYPE & t);
//
//template < typename TYPE >
//inline binary_stream & operator << (binary_stream & binary_stream, const TYPE & t);
//
//template < typename TYPE >
//inline binary_stream & operator >> (binary_stream & binary_stream, TYPE & t)
//{
//
//   binary_stream.defer_set_loading();
//
//   binary_stream.stream_exchange(::atom::e_type_null, t);
//
//   return binary_stream;
//
//}
//
//
//template < typename TYPE >
//inline binary_stream & operator << (binary_stream & binary_stream, const TYPE & t)
//{
//
//   binary_stream.defer_set_storing();
//
//   binary_stream.stream_exchange(::atom::e_type_null, (TYPE &)t);
//
//   return binary_stream;
//
//}
//
//template < typename TYPE >
//inline ::file::file & operator >> (::file::file & file, TYPE & t)
//{
//
//   if (::is_null(file))
//   {
//
//      throw ::exception(error_io);
//
//   }
//
//   binary_stream binary_stream(&file);
//
//   binary_stream >> t;
//
//   return file;
//
//}
//
//
//template < typename TYPE >
//inline ::file::file & operator << (::file::file & file, const TYPE & t)
//{
//
//   binary_stream binary_stream(&file);
//
//   binary_stream << t;
//
//   return file;
//
//}
//
//inline void assign(::memory & memory, const ::payload & payload)
//{
//
//   memory = (const ::memory &) payload;
//
//}
//
//
//template < typename TYPE >
//void payload_stream::default_exchange(TYPE & t)
//{
//
//   try
//   {
//
//      if(is_loading())
//      {
//
//         ::assign(t, *this->m_ppayload);
//
//      }
//      else
//      {
//
//         ::assign(*this->m_ppayload, t);
//
//      }
//
//  }
//  catch(const ::exception & e)
//  {
//
//     add_exception(e);
//
//  }
//  catch (...)
//  {
//
//     on_catch_all_exception();
//
//  }
//
//}
//
//
//template < typename TYPE >
//void payload_stream::write_only(TYPE & t)
//{
//
//  if (is_loading())
//  {
//
//     throw ::exception(error_io);
//
//  }
//  else
//  {
//
//     m_ppayload->operator =(t);
//
//  }
//
//}
//
//
//
//
//template < typename TYPE >
//inline void payload_stream::var_exchange(const ::atom & atom, TYPE & t)
//{
//
//  ::payload * pvar = m_ppayload;
//
//  if (atom.m_etype != atom::e_type_null)
//  {
//
//     m_ppayload = &m_ppayload->operator[](atom);
//
//  }
//
//  __exchange(*this, t);
//
//  m_ppayload = pvar;
//
//}
//
//
//#include "_payload_stream_impl.h"
//
//
//
