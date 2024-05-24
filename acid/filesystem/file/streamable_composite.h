// Created by camilo on 2021-09-09 22:58 Thomas Month!! <3ThomasBS__!!
#pragma once


#include "streamable.h"
//#include "acid/primitive/primitive/pointer.h"


namespace file
{


   class CLASS_DECL_ACID streamable_composite :
      virtual public streamable
   {
   public:


      ::pointer<streamable>     m_pstreamable;


      streamable_composite();
      streamable_composite(streamable * pstreamable);
      ~streamable_composite() override;


      virtual enum_status _open(const ::scoped_string & scopedstrFilePath, const ::file::enum_open & eopen) override;

      void translate(filesize offset, ::enum_seek eseek) override;

      using ::file::streamable::read;
      virtual memsize read(void * p, ::memsize s) override;

      using ::file::streamable::write;
      virtual void write(const void * p, ::memsize s) override;

      virtual void close() override;

      virtual void flush() override;

      void set_size(filesize dwNewLen) override;

      virtual filesize size() const override;


   };


} // namespace file



