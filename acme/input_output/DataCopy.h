#pragma once


#include "InputStream.h"
#include "OutputStream.h"


///#include "remoting/remoting_common/util/inttypes.h"
//namespace subsystem
//{
   class CLASS_DECL_ACME DataCopy : public InputStream, public OutputStream
   {
   public:


      DataCopy();

      memsize read(void* buffer, memsize len);
      memsize write(const void* buffer, memsize len);
      memsize available();


      ::memory m_memory;


   };
//}//namespace subsystem
