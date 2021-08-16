#pragma once


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
      ::index translate(::count c, ::enum_seek eseek) override;
      filesize get_position() const override;
      filesize get_size() const override;

      using ::file::file::read;
      memsize read(void *pdata, memsize nCount) override;

      using ::file::file::write;
      void write(const void * pdata, memsize nCount) override;

      int put_character_back(int iCharacterPutBack) override;

      void flush() override;
      bool buffer(memsize uiGrow = 0);
      void set_size(filesize dwNewLen) override;

      virtual memsize get_buffer_size();


   };


} // namespace file


