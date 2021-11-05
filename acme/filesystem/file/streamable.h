// Created by camilo on 2021-08-01 22:40 Thomas Month!! <3ThomasBS__!!
#pragma once


namespace file
{


   class CLASS_DECL_ACME streamable :
      virtual public translatable
   {
   public:


      virtual enum_status _open(const char * pszFilePath, const ::file::enum_open & eopen);

      virtual filesize translate(filesize offset, ::enum_seek eseek);

      virtual memsize read(void * pdata, memsize nCount);

      virtual void write(const void * pdata, memsize nCount);

      virtual void flush();
      virtual void close();
      virtual void abort();


      virtual void set_size(filesize dwNewLen);

      virtual filesize get_size() const;


   };


} // namespace file



