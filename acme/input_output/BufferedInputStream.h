//#ifndef BUFFEREDINPUTSTREAM_H
#pragma once
//#define BUFFEREDINPUTSTREAM_H

#include "acme/input_output/DataInputStream.h"
//// #include aaa_<vector>

//namespace subsystem
//{
   class CLASS_DECL_ACME BufferedInputStream : public InputStream
   {
   public:

      BufferedInputStream(InputStream *input);

      virtual ~BufferedInputStream();

      virtual memsize read(void *buffer, memsize len);

      memsize available();

   protected:

      const memsize MAX_BUFFER_SIZE;
      const memsize INITIAL_BUFFER_SIZE;

      DataInputStream *m_input;

      ::array_base<char> m_buffer;

      memsize m_have;
      memsize m_pos;

   };

   //// BUFFEREDINPUTSTREAM_H
//}//namespace subsystem
