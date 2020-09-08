#pragma once


namespace file
{


   class CLASS_DECL_APEX buffered_file :
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
      virtual ~buffered_file();


      virtual bool is_valid() const override;
      virtual filesize seek(filesize lOff, ::file::e_seek nFrom) override;
      virtual filesize get_position() const override;
      virtual filesize get_size() const override;

      using ::file::file::read;
      virtual memsize read(void *pdata, memsize nCount) override;

      using ::file::file::write;
      virtual void write(const void * pdata, memsize nCount) override;

      virtual void flush() override;
      virtual bool buffer(memsize uiGrow = 0);
      virtual void set_size(filesize dwNewLen) override;

      virtual memsize get_buffer_size();


   };


} // namespace file


