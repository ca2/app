// Created by camilo on 2021-08-01 22:40 Thomas Month!! <3ThomasBS__!!
#pragma once


namespace file
{


   class CLASS_DECL_ACME streamable :
      virtual public translatable
   {
   public:


      virtual enum_status _open(const char * pszFilePath, const ::file::enum_open & eopen) { throw error_interface_only; }


      //virtual filesize get_position() const { throw error_interface_only; }
      //virtual filesize set_position(filesize position) { throw error_interface_only; }

      ::index translate(::count c, ::enum_seek eseek) override { throw error_interface_only; }

      virtual memsize read(void * pdata, memsize nCount) { throw error_interface_only; }

      virtual void write(const void * pdata, memsize nCount) { throw error_interface_only; }

      virtual void close() { throw error_interface_only; }

      virtual void flush() { throw error_interface_only; }

      virtual void set_size(filesize dwNewLen) { throw error_interface_only; }
      virtual filesize get_size() const { throw error_interface_only; }


   };


   class CLASS_DECL_ACME streamable_composite :
      virtual public streamable
   {
   public:


      streamable * m_pstreamable;


      streamable_composite() { m_pstreamable = nullptr; }
      streamable_composite(streamable * pstreamble) { m_pstreamable = pstreamble; m_pstreamable->increment_reference_count(); }
      ~streamable_composite() override { if(m_pstreamable) m_pstreamable->release(); }


      virtual enum_status _open(const char * pszFilePath, const ::file::enum_open & eopen) override { return m_pstreamable->_open(pszFilePath, eopen); }

      //virtual filesize get_position() const override { return m_pstreamable->get_position(); }
      //virtual filesize set_position(filesize position) override { return m_pstreamable->set_position(position); }

      ::index translate(::count c, ::enum_seek eseek) override { return m_pstreamable->translate(c, eseek); }

      virtual memsize read(void * pdata, memsize nCount) override { return m_pstreamable->read(pdata, nCount); }

      virtual void write(const void * pdata, memsize nCount) override { return m_pstreamable->write(pdata, nCount); }

      virtual void close()  override { return m_pstreamable->close(); }

      virtual void flush() override { return m_pstreamable->flush(); }

      virtual void set_size(filesize dwNewLen) override { throw error_interface_only; }
      virtual filesize get_size() const override { throw error_interface_only; }


   };


} // namespace file



