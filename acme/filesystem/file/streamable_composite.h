// Created by camilo on 2021-09-09 22:58 Thomas Month!! <3ThomasBS__!!
#pragma once


namespace file
{


   class CLASS_DECL_ACME streamable_composite :
      virtual public streamable
   {
   public:


      __pointer(streamable)      m_pstreamable;


      streamable_composite();
      streamable_composite(streamable * pstreamable);
      ~streamable_composite() override;


      virtual enum_status _open(const char * pszFilePath, const ::file::enum_open & eopen) override;

      filesize translate(filesize offset, ::enum_seek eseek) override;

      virtual memsize read(void * pdata, memsize nCount) override;

      virtual void write(const void * pdata, memsize nCount) override;

      virtual void close() override;

      virtual void flush() override;

      void set_size(filesize dwNewLen) override;

      virtual filesize get_size() const override;


   };


} // namespace file



