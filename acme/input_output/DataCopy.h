#pragma once


#include "InputStream.h"
#include "OutputStream.h"


/////#include "subsystem/platform/inttypes.h"
//namespace subsystem
//{
   class CLASS_DECL_ACME DataCopy : public InputStream, public OutputStream
   {
   public:

      ::memory m_memory;



      DataCopy();

      memsize read(void* buffer, memsize len) override;
      memsize defer_write(const void* buffer, memsize len) override;
      memsize available() override;


   };
//}//namespace subsystem
