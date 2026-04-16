#include "framework.h"
#include "BufferedInputStream.h"
// #include aaa_<string.h>
// #include aaa_<istream>
// #include aaa_<sstream>
// #include aaa_<algorithm>

//namespace subsystem
//{
   BufferedInputStream::BufferedInputStream(InputStream *input)
   : m_have(0),
     INITIAL_BUFFER_SIZE(100000),
     MAX_BUFFER_SIZE(10000000),
     m_buffer(INITIAL_BUFFER_SIZE),
     m_pos(0)
   {
      m_input = new DataInputStream(input);
   }

   BufferedInputStream::~BufferedInputStream() {
      delete m_input;
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
      if (m_buffer.size() > INITIAL_BUFFER_SIZE) {
         m_buffer.resize(INITIAL_BUFFER_SIZE);
      }
      // FIXME: available() sometimes does not work for POCO
      // Websocket (always for secure connection).
      memsize need = m_input->available();
      if (need > INITIAL_BUFFER_SIZE) {
         m_buffer.resize(::minimum(need, MAX_BUFFER_SIZE));
      }
      try {
         m_have = m_input->read(&m_buffer[0], m_buffer.size());
      }
      catch (::exception &e) {
         if (m_buffer.size() == MAX_BUFFER_SIZE) {
            throw e;
         }
         m_buffer.resize(MAX_BUFFER_SIZE);
         m_have = m_input->read(&m_buffer[0], m_buffer.size());
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
