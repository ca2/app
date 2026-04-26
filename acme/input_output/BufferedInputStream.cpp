#include "framework.h"
#include "BufferedInputStream.h"
// #include aaa_<string.h>
// #include aaa_<istream>
// #include aaa_<sstream>
// #include aaa_<algorithm>

//namespace subsystem
//{
   BufferedInputStream::BufferedInputStream()
   : m_have(0),
     m_iInitialBufferSize(100000),
     m_iMaximumBufferSize(10000000),
     m_pos(0)
   {
//      m_input = new DataInputStream(input);
   }

// BufferedInputStream::BufferedInputStream()
//    : m_have(0),
//   INITIAL_BUFFER_SIZE(100000),
//   MAX_BUFFER_SIZE(10000000),
//   m_buffer(INITIAL_BUFFER_SIZE),
//   m_pos(0)
//    {
//       m_input = new DataInputStream(input);
//    }

   BufferedInputStream::~BufferedInputStream() {
      //delete m_input;
   }


void BufferedInputStream::initialize_buffered_input_stream(InputStream * pinputstream, memsize iInitialBufferSize, memsize iMaximumBufferSize)
   {

      if (iInitialBufferSize > 0)
      {

         m_iInitialBufferSize = iInitialBufferSize;

      }

      if (iMaximumBufferSize > m_iInitialBufferSize)
      {

         m_iMaximumBufferSize = iMaximumBufferSize;

      }

      m_buffer.set_size(m_iInitialBufferSize);

      ::system()->construct_newø(m_pdatainputstream);

      m_pdatainputstream->initialize_data_input_stream(pinputstream);


   }


   memsize BufferedInputStream::available() {
      return m_have;
   }


   memsize BufferedInputStream::read(void *buffer, memsize len) {
      char *buf = (char *)buffer;

      if (m_have == 0) {
         m_pos = 0;
      }

      if (len <= m_have) {
         memcpy(buf, &m_buffer[m_pos], len);
         m_have -= len;
         m_pos += len;
         return len;
      }
      memcpy(buf, &m_buffer[m_pos], m_have);
      memsize copied = m_have;
      m_pos = 0;
      if (m_buffer.size() > m_iInitialBufferSize) {
         m_buffer.set_size(m_iInitialBufferSize);
      }
      // FIXME: available() sometimes does not work for POCO
      // Websocket (always for secure connection).
      memsize need = m_pdatainputstream->available();
      if (need > m_iInitialBufferSize) {
         m_buffer.set_size(::minimum(need, m_iMaximumBufferSize));
      }
      try {
         m_have = m_pdatainputstream->read(&m_buffer[0], m_buffer.size());
      }
      catch (::exception &e) {
         if (m_buffer.size() == m_iMaximumBufferSize) {
            throw e;
         }
         m_buffer.set_size(m_iMaximumBufferSize);
         m_have = m_pdatainputstream->read(&m_buffer[0], m_buffer.size());
      }
      memsize remain = ::minimum(m_have, len - copied);
      memcpy(&buf[copied], &m_buffer[0], remain);
      copied += remain;
      m_have -= remain;
      m_pos += remain;
      if (m_have == 0) {
         m_pos = 0;
      }
      return copied;
   }
//} // namespace subsystem
