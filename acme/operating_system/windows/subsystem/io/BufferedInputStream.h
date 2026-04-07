//#ifndef BUFFEREDINPUTSTREAM_H
#pragma once
//#define BUFFEREDINPUTSTREAM_H

#include "acme/subsystem/io/DataInputStream.h"
//#include <vector>

namespace remoting
{
   class CLASS_DECL_REMOTING_COMMON BufferedInputStream : public InputStream
   {
   public:

      BufferedInputStream(InputStream *input);

      virtual ~BufferedInputStream();

      virtual size_t read(void *buffer, size_t len);

      size_t available();

   protected:

      const size_t MAX_BUFFER_SIZE;
      const size_t INITIAL_BUFFER_SIZE;

      DataInputStream *m_input;

      ::array_base<char> m_buffer;

      size_t m_have;
      size_t m_pos;

   };

   //// BUFFEREDINPUTSTREAM_H
}//namespace remoting
