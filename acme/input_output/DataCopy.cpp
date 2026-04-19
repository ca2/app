#include "framework.h"
#include "DataCopy.h"

//namespace subsystem
//{
   DataCopy::DataCopy() {}

   memsize DataCopy::defer_write(const void* buffer, memsize len)
   {
      m_memory.append(buffer, len);
      return len;
   }

   memsize DataCopy::read(void* buffer, memsize len)
   {
      auto read = minimum(len, m_memory.size());
      m_memory.copy_to(buffer, read);
      m_memory.delete_begin(read);
      // memsize have = buf.size();
      // if (have < len) {
      //   len = have;
      // }
      // std::copy(buf.begin(), buf.begin() + len, (unsigned char*)buffer);
      // std::copy(buf.begin() + len, buf.end(), buf.begin());
      // buf.resize(have - len);
      return read;
   }

   memsize DataCopy::available()
   {
      return m_memory.size();
   }
//}//namespace subsystem
