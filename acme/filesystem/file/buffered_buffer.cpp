#include "framework.h"
#include "buffered_file.h"
//////#include "acme/exception/exception.h"
//#include "acme/prototype/comparison/compare.h"


namespace file
{


   buffered_file::buffered_file(file_pointer pfile, memsize iBufferSize)
   {

      m_storage.set_size(iBufferSize);
      m_pfile              = pfile;
      m_uiBufferSize        = iBufferSize;
      m_uiPosition          = 0;
      m_uiBufLPos           = 0;
      m_uiBufUPos           = 0xffffffff;
      m_uiWriteLPos         = 0xffffffff;
      m_uiWriteUPos         = 0xffffffff;
      m_bDirty = false;

   }


   buffered_file::~buffered_file()
   {

      flush();

   }


   bool buffered_file::is_valid() const
   {

      return m_pfile.is_set();

   }


   void buffered_file::translate(filesize offset, ::enum_seek eseek)
   {

      u64 uiBegBufPosition = m_uiBufLPos;

      u64 uiEndBufPosition = m_uiBufUPos;

      u64 uiNewPos;

      if(eseek == ::e_seek_set)
      {
         
         if (offset < 0)
         {

            offset = 0;

         }

         uiNewPos = offset;

      }
      else if(eseek == ::e_seek_from_end)
      {

         uiNewPos = m_pfile->size() + offset;

      }
      else if(eseek == ::e_seek_current)
      {
         
         i64 iNewPosition = m_uiPosition + offset;

         if (iNewPosition < 0)
         {

            iNewPosition = 0;

         }
         else if (::comparison::gt(iNewPosition, m_pfile->size()))
         {

            iNewPosition = m_pfile->size();

         }
         
         uiNewPos = iNewPosition;

      }
      else
      {

         throw ::exception(error_bad_argument, "::file::buffered_file::seek invalid seek option");

      }

      if(uiNewPos >= uiBegBufPosition && uiNewPos <= uiEndBufPosition)
      {

         m_uiPosition = uiNewPos;

      }
      else
      {

         m_pfile->set_position(uiNewPos);

         m_uiPosition = m_pfile->get_position();

         if (m_bDirty)
         {

            flush();

         }

         m_uiBufLPos     = 0;
         m_uiBufUPos     = 0xffffffff;
         m_uiWriteLPos   = 0xffffffff;
         m_uiWriteUPos   = 0xffffffff;

      }

      //return m_uiPosition;

   }


   filesize buffered_file::get_position() const
   {

      return m_uiPosition;

   }


   filesize buffered_file::size() const
   {

      if (!m_pfile)
      {

         return 0;

      }

      return m_pfile->size();

   }


   memsize buffered_file:: read(void * p, ::memsize s)
   {

      auto data = (unsigned char *) p;

      if (::is_null(data) || s <= 0)
      {

         return 0;

      }

      memsize uRead = 0;

      memsize uiReadNow = 0;

      while(uRead < s)
      {

         if(m_uiPosition >= m_uiBufLPos && m_uiPosition <= m_uiBufUPos && m_uiBufUPos != 0xFFFFFFFF)
         {

            uiReadNow = minimum(s - uRead, (memsize)(m_uiBufUPos - m_uiPosition + 1));

            if(s == 1)
            {

               data[uRead] = m_storage.data()[m_uiPosition - m_uiBufLPos];

            }
            else
            {

               ::memory_copy(data + uRead, &m_storage.data()[m_uiPosition - m_uiBufLPos], (size_t) uiReadNow);

            }

            m_uiPosition += uiReadNow;

            uRead += uiReadNow;

         }

         if(uRead < s)
         {

            if (!buffer())
            {

               break;

            }

         }

      }

      return uRead;

   }


   bool buffered_file::buffer(memsize uiGrow)
   {

      if(!m_pfile)
      {
      
         return false;
      
      }

      if(m_bDirty)
      {

         flush();

      }

      m_pfile->set_position((filesize) m_uiPosition);

      memsize uiCopy;

      if (uiGrow > 0)
      {

         uiCopy = minimum(m_uiBufferSize, uiGrow);

      }
      else
      {

         uiCopy = m_uiBufferSize;

      }

      memsize uRead    = 0;

      try
      {

         uRead = m_pfile->read(m_storage.data(), uiCopy);

      }
      catch(...)
      {

      }

      m_uiBufLPos       = m_uiPosition;

      m_uiBufUPos       = m_uiPosition + uRead - 1;

      m_uiWriteLPos     = 0xffffffff;

      m_uiWriteUPos     = 0xffffffff;

      return uRead > 0;

   }


   void buffered_file::write(const void * p, ::memsize s)
   {

      auto data = (const unsigned char *)p;

      memsize uiWrite = 0;

      memsize uiWriteNow = 0;

      while(uiWrite < s)
      {

         if(m_uiPosition >= m_uiBufLPos && m_uiPosition < (m_uiBufLPos + m_uiBufferSize))
         {

            m_bDirty = true;

            uiWriteNow = minimum(s - uiWrite, (memsize)((m_uiBufLPos + m_uiBufferSize) - m_uiPosition + 1));

            if (m_uiWriteLPos == 0xffffffff || m_uiWriteLPos > m_uiPosition)
            {

               m_uiWriteLPos = m_uiPosition;

            }

            if (m_uiWriteUPos == 0xffffffff || m_uiWriteUPos < (m_uiPosition + uiWriteNow - 1))
            {

               m_uiWriteUPos = (m_uiPosition + uiWriteNow - 1);

            }

            ::memory_copy(&m_storage.data()[m_uiPosition - m_uiBufLPos], data + uiWrite, (size_t) uiWriteNow);

            m_uiPosition += uiWriteNow;

            uiWrite += uiWriteNow;

         }

         if(uiWrite < s)
         {

            buffer(s - uiWrite);

         }

      }

   }


   void buffered_file::put_byte_back(unsigned char uch)
   {

      m_uiPosition--;

      if (m_uiPosition < m_uiBufLPos)
      {

         buffer(1);

      }

      m_storage.data()[m_uiPosition] = (unsigned char) uch;

   }


   void buffered_file::flush()
   {

      if(m_bDirty)
      {

         m_pfile->set_position((filesize) m_uiWriteLPos);

         m_pfile->write(m_storage.data() + (m_uiWriteLPos - m_uiBufLPos), (memsize)(m_uiWriteUPos - m_uiWriteLPos + 1));

         m_bDirty = false;

         m_uiWriteLPos = 0xffffffff;

         m_uiWriteUPos = 0xffffffff;

      }

   }


   void buffered_file::set_size(filesize dwNewLen)
   {

      m_pfile->set_size(dwNewLen);

      m_uiPosition = 0;
      m_uiBufLPos = 0;
      m_uiBufUPos = 0xffffffff;
      m_uiWriteLPos = 0xffffffff;
      m_uiWriteUPos = 0xffffffff;
      m_bDirty = false;

   }

   
   memsize buffered_file::get_buffer_size()
   {

      return m_uiBufferSize;

   }


} // namespace file



