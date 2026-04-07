#include "framework.h"
#include "DataCopy.h"

namespace remoting
{
   DataCopy::DataCopy() {}

   size_t DataCopy::write(const void* buffer, size_t len)
   {
      m_memory.append(buffer, len);
      return len;
   }

   size_t DataCopy::read(void* buffer, size_t len)
   {
      auto read = minimum(len, m_memory.size());
      m_memory.copy_to(buffer, read);
      m_memory.delete_begin(read);
      // size_t have = buf.size();
      // if (have < len) {
      //   len = have;
      // }
      // std::copy(buf.begin(), buf.begin() + len, (unsigned char*)buffer);
      // std::copy(buf.begin() + len, buf.end(), buf.begin());
      // buf.resize(have - len);
      return read;
   }

   size_t DataCopy::available()
   {
      return m_memory.size();
   }
}//namespace remoting
