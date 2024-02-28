#pragma once


#include "acme/primitive/primitive/memory.h"
#include "file.h"


namespace file
{


   class CLASS_DECL_ACME buffered_file :
      virtual public ::file::file
   {
   public:


      file_pointer            m_pfile;

      memsize                 m_uiBufferSize;
      filesize                m_uiPosition;
      filesize                m_uiBufLPos;
      filesize                m_uiBufUPos;
      bool                    m_bDirty;
      filesize                m_uiWriteLPos;
      filesize                m_uiWriteUPos;
      memory                  m_storage;


      buffered_file(file_pointer pfile, memsize iBufferSize = 1024 * 128);
      ~buffered_file() override;


      bool is_valid() const override;
      void translate(filesize offset, ::enum_seek eseek) override;
      filesize get_position() const override;
      filesize size() const override;


      using ::file::file::read;
      memsize read(void * p, ::memsize s) override;

      
      using ::file::file::write;
      void write(const void * p, ::memsize s) override;


      void put_byte_back(::u8 u8) override;

      void flush() override;
      bool buffer(memsize uiGrow = 0);
      void set_size(filesize dwNewLen) override;

      virtual memsize get_buffer_size();


   };


} // namespace file


