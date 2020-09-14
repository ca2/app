#pragma once


//namespace file
//{
//
//   namespace array
//   {
//
//      template < class ARRAY >
//      void write(stream & ostream, const ARRAY & a)
//      {
//         ::count count = a.get_count();
//         ostream.write(count);
//         for (index index = 0; index < count; index++)
//         {
//            ostream << a.element_at(index);
//         }
//      }
//
//      template < class ARRAY >
//      void read(stream & istream, ARRAY & a)
//      {
//         ::count count;
//         //istream >> count;
//         istream.read(count);
//
//         if (istream.fail())
//         {
//            return;
//         }
//
//         a.allocate(count);
//         for (index index = 0; index < count; index++)
//         {
//            istream >> a.element_at(index);
//            if (istream.fail())
//            {
//               return;
//            }
//         }
//         a.on_after_read();
//      }
//
//
//   } // namespace array
//
//   namespace ptra
//   {
//
//      template < class ARRAY >
//      void write(stream & ostream, const ARRAY & a)
//      {
//         ::count count = a.get_count();
//         ostream.write(count);
//         for (index index = 0; index < count; index++)
//         {
//            ostream << *a.element_at(index);
//         }
//      }
//
//      template < class ARRAY >
//      void read(stream & istream, ARRAY & a)
//      {
//         ::count count;
//         //istream >> count;
//         istream.read(count);
//
//         if (istream.fail())
//         {
//            return;
//         }
//
//         a.allocate(count);
//         for (index index = 0; index < count; index++)
//         {
//            istream >> *a.element_at(index);
//            if (istream.fail())
//            {
//               return;
//            }
//         }
//         a.on_after_read();
//      }
//
//
//   } // namespace array
//
//   namespace map
//   {
//
//      template < class type_map >
//      void write(stream & ostream, const type_map & m)
//      {
//
//         ostream.write(m.get_count());
//
//         auto p = m.get_start();
//
//         while (p != nullptr)
//         {
//
//            ostream << p->element1();
//
//            ostream << p->element2();
//
//            p = m.get_next(p);
//
//         }
//
//      }
//
//
//      template < class type_map >
//      void read(stream & istream, type_map & m)
//      {
//
//         ::count count;
//
//         istream.read(count);
//
//         if (istream.fail())
//         {
//
//            return;
//
//         }
//
//         typename type_map::BASE_KEY key;
//
//         typename type_map::BASE_VALUE value;
//
//         for (index index = 0; index < count; index++)
//         {
//
//            istream >> key;
//
//            if (istream.fail())
//            {
//
//               return;
//
//            }
//
//            istream >> value;
//
//            if (istream.fail())
//            {
//
//               return;
//
//            }
//
//            m.set_at(key, value);
//
//         }
//
//         m.on_after_read();
//
//      }
//
//   } // namespace map
//
//
//
//} // namespace file
//
//
////template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = ::allocator::def < TYPE > >
////stream & operator << (stream & s, array < TYPE, ARG_TYPE, ALLOCATOR > & a)
////{
////
////   s.stream_array(a);
////
////   return s;
////
////}
//
//
////template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = ::allocator::def < TYPE > >
////stream & operator >> (stream & s, array < TYPE, ARG_TYPE, ALLOCATOR > & a)
////{
////
////   s (a);
////
////   return s;
////
////}
//
//
//
////template<class TYPE, class ARG_TYPE = const TYPE &>
////stream & operator << (stream & stream, raw_array < TYPE, ARG_TYPE> & a)
////{
////
////   ASSERT(stream.is_storing());
////
////   stream.stream_array(a);
////
////   return stream;
////
////}
//
//
////template<class TYPE, class ARG_TYPE = const TYPE &>
////stream & operator >> (stream & s, raw_array < TYPE, ARG_TYPE > & a)
////{
////
////   s.stream_array(a);
////
////   return s;
////
////}
//
//
//
//
//
//
//
//
////inline memsize stream::gcount() { return m_gcount; }
////inline filesize stream::tellg() { return m_p->tell(); }
////inline stream & stream::seekg(filesize position) { m_p->seek_from_begin(position); return *this; }
////inline stream & stream::seekg(filesize offset, ::file::e_seek eseek) { m_p->seek(offset, eseek); return *this; }
//
////inline filesize stream::get_left() const { return m_p->get_length() - m_p->get_position(); }
