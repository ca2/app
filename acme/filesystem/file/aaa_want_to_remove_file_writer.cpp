#include "framework.h"


//namespace file
//{
//
//
//   writer::writer()
//   {
//   }
//
//
//   writer::~writer()
//   {
//   }
//
//
//   void writer::write(const void *pdata, memsize nCount)
//
//   {
//
//      memsize memsize;
//
//      write(pdata, nCount, &memsize);
//
//
//   }
//
//   void writer::write(const void *pdata, memsize nCount, memsize * dwWritten)
//
//   {
//
//      ::exception::throw_interface_only();
//
//   }
//
//   void writer::transfer_from_begin(reader & reader, memsize uiBufSize)
//   {
//
//      reader.seek_to_begin();
//
//      transfer_from(reader, uiBufSize);
//
//   }
//
//   void writer::transfer_from(reader & reader, memsize uiBufSize)
//   {
//
//
//      if(reader.get_internal_data() != nullptr && reader.get_internal_data_size() > reader.get_position())
//      {
//
//         write((u8 *) reader.get_internal_data() + reader.get_position(), (memsize) (reader.get_internal_data_size() - reader.get_position()));
//
//         return;
//
//      }
//
//
//      memsize uiRead;
//      memsize uiSize = 0;
//      uiBufSize = max(32 * 1024, uiBufSize);
//
//      memory buf;
//
//      buf.set_size(uiBufSize);
//
//      if(buf.get_data() == nullptr)
//         __throw(memory_exception());
//
//      try
//      {
//         while(true)
//         {
//            uiRead = reader.read(buf.get_data(), buf.get_size());
//            if(uiRead <= 0)
//            {
//               break;
//            }
//            write(buf.get_data(), uiRead);
//            uiSize += uiRead;
//         }
//      }
//      catch(...)
//      {
//      }
//
//   }
//
//   /*
//   bool writer::is_writer_null()
//   {
//      return m_spwriter.is_null();
//   }
//
//   bool writer::is_writer_set()
//   {
//      return m_spwriter.is_set();
//   }
//   */
//   void writer::close()
//   {
//      /*
//      if(m_spwriter.is_set())
//      {
//         //m_spwriter->close();
//         ::release(m_spwriter.m_p);
//      }
//      */
//   }
//
//   /*
//   void writer::from_hex(const char * psz)
//   {
//      memory memory;
//      memory.from_hex(psz);
//      write(memory.get_data(), memory.get_size());
//   }*/
//
//   void writer::flush()
//   {
//   }
//
//   /*
//   void writer::write (char ch)
//   {
//      UNREFERENCED_PARAMETER(ch);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (uchar uch)
//   {
//      UNREFERENCED_PARAMETER(uch);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (i16 sh)
//   {
//      UNREFERENCED_PARAMETER(sh);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (u16 ui)
//   {
//      UNREFERENCED_PARAMETER(ui);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (unichar wch)
//   {
//      UNREFERENCED_PARAMETER(wch);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (bool b)
//   {
//      UNREFERENCED_PARAMETER(b);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (i32 i)
//   {
//      UNREFERENCED_PARAMETER(i);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (u32 ui)
//   {
//      UNREFERENCED_PARAMETER(ui);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (i64 i)
//   {
//      UNREFERENCED_PARAMETER(i);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (u64 ui)
//   {
//      UNREFERENCED_PARAMETER(ui);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (float f)
//   {
//      UNREFERENCED_PARAMETER(f);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (double d)
//   {
//      UNREFERENCED_PARAMETER(d);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (const ::rect & rect)
//   {
//      UNREFERENCED_PARAMETER(pcrect);
//
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (const size & & size)
//   {
//      UNREFERENCED_PARAMETER(size);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (::type info)
//   {
//      UNREFERENCED_PARAMETER(info);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (generic & generic)
//   {
//      UNREFERENCED_PARAMETER(generic);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (const char * psz)
//   {
//      UNREFERENCED_PARAMETER(psz);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (const id & id)
//   {
//      UNREFERENCED_PARAMETER(id);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (const var & var)
//   {
//      UNREFERENCED_PARAMETER(var);
//      ::exception::throw_interface_only();
//   }
//
//   void writer::write (const string & str)
//   {
//      UNREFERENCED_PARAMETER(str);
//      ::exception::throw_interface_only();
//   }
//   */
//
//
//   HRESULT write(writer * pwriter, const void * data, memsize size)
//   {
//      HRESULT res = S_OK;
//      try
//      {
//         pwriter->write(data, size);
//      }
//      catch(...)
//      {
//         res = E_FAIL;
//      }
//      RINOK(res);
//      return res;
//   }
//
//} // namespace file
//
//
//
//
