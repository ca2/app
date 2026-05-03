//#ifndef BUFFEREDINPUTSTREAM_H
#pragma once
//#define BUFFEREDINPUTSTREAM_H

#include "acme/input_output/DataInputStream.h"
//// #include aaa_<vector>

//namespace subsystem
//{
   class CLASS_DECL_ACME BufferedInputStream :
         virtual public InputStream
   {
   public:


      //   protected:

      memsize m_iMaximumBufferSize;
      memsize m_iInitialBufferSize;

      ::pointer < DataInputStream > m_pdatainputstream;

      //::array_base<char> m_buffer;
      ::memory m_buffer;

      memsize m_have;
      memsize m_pos;


      BufferedInputStream();
      BufferedInputStream(InputStream *input, memsize iInitialBufferSize = -1, memsize iMaximumBufferSize = -1);
      ~BufferedInputStream() override;


      virtual void _initialize_buffered_input_stream(InputStream *input, memsize iInitialBufferSize = -1, memsize iMaximumBufferSize = -1);


      virtual memsize read(void *buffer, memsize len);

      memsize available();


   };

   //// BUFFEREDINPUTSTREAM_H
//}//namespace subsystem
