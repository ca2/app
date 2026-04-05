#pragma once


#include "InputStream.h"
#include "OutputStream.h"


#include "remoting/remoting_common/util/inttypes.h"
namespace remoting
{
   class CLASS_DECL_REMOTING_COMMON DataCopy : public InputStream, public OutputStream
   {
   public:


      DataCopy();

      size_t read(void* buffer, size_t len);
      size_t write(const void* buffer, size_t len);
      size_t available();


      ::memory m_memory;


   };
}//namespace remoting
