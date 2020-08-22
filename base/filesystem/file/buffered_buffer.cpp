#include "framework.h"


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


   filesize buffered_file::seek(filesize lOff, ::file::e_seek nFrom)
   {

      u64 uiBegBufPosition = m_uiBufLPos;
      u64 uiEndBufPosition = m_uiBufUPos;
      u64 uiNewPos;
      if(nFrom == ::file::seek_begin)
      {
         if(lOff < 0)
            lOff = 0;
         uiNewPos = lOff;
      }
      else if(nFrom == ::file::seek_end)
      {

         uiNewPos = m_pfile->get_size() + lOff;

      }
      else if(nFrom == ::file::seek_current)
      {
         
         i64 iNewPos = m_uiPosition + lOff;

         if (iNewPos < 0)
         {

            iNewPos = 0;

         }
         else if (::comparison::gt(iNewPos, m_pfile->get_size()))
         {

            iNewPos = m_pfile->get_size();

         }
         
         uiNewPos = iNewPos;

      }
      else
      {

         __throw(invalid_argument_exception("::file::buffered_file::seek invalid seek option"));

      }

      if(uiNewPos >= uiBegBufPosition && uiNewPos <= uiEndBufPosition)
      {

         m_uiPosition = uiNewPos;

      }
      else
      {

         m_uiPosition = m_pfile->seek(uiNewPos, ::file::seek_begin);

         if (m_bDirty)
         {

            flush();

         }

         m_uiBufLPos     = 0;
         m_uiBufUPos     = 0xffffffff;
         m_uiWriteLPos   = 0xffffffff;
         m_uiWriteUPos   = 0xffffffff;

      }

      return m_uiPosition;

   }


   filesize buffered_file::get_position() const
   {

      return m_uiPosition;

   }


   filesize buffered_file::get_size() const
   {

      if (!m_pfile)
      {

         return 0;

      }

      return m_pfile->get_size();

   }


   memsize buffered_file:: read(void *pBufParam, memsize nCount)
   {

      if (nCount == 0)
      {

         return 0;

      }

      memsize uiRead = 0;

      memsize uiReadNow = 0;

      while(uiRead < nCount)
      {

         if(m_uiPosition >= m_uiBufLPos && m_uiPosition <= m_uiBufUPos && m_uiBufUPos != 0xFFFFFFFF)
         {

            uiReadNow = MIN(nCount - uiRead, (memsize) (m_uiBufUPos - m_uiPosition + 1));

            if(nCount == 1)
            {

               ((byte *)pBufParam)[uiRead] = m_storage.get_data()[m_uiPosition - m_uiBufLPos];

            }
            else
            {

               ::memcpy_dup(&((byte *)pBufParam)[uiRead], &m_storage.get_data()[m_uiPosition - m_uiBufLPos], (size_t) uiReadNow);

            }

            m_uiPosition += uiReadNow;

            uiRead += uiReadNow;

         }

         if(uiRead < nCount)
         {

            if (!buffer())
            {

               break;

            }

         }

      }

      return uiRead;

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

      m_pfile->seek((filesize) m_uiPosition, ::file::seek_begin);

      memsize uiCopy;

      if (uiGrow > 0)
      {

         uiCopy = MIN(m_uiBufferSize, uiGrow);

      }
      else
      {

         uiCopy = m_uiBufferSize;

      }

      memsize uiRead    = m_pfile->read(m_storage.get_data(), uiCopy);

      m_uiBufLPos       = m_uiPosition;

      m_uiBufUPos       = m_uiPosition + uiRead - 1;

      m_uiWriteLPos     = 0xffffffff;

      m_uiWriteUPos     = 0xffffffff;

      return uiRead > 0;

   }


   void buffered_file::write(const void * pdata, memsize nCount)
   {

      memsize uiWrite = 0;

      memsize uiWriteNow = 0;

      while(uiWrite < nCount)
      {

         if(m_uiPosition >= m_uiBufLPos && m_uiPosition < (m_uiBufLPos + m_uiBufferSize))
         {

            m_bDirty = true;

            uiWriteNow = MIN(nCount - uiWrite, (memsize) ((m_uiBufLPos + m_uiBufferSize) - m_uiPosition + 1));

            if (m_uiWriteLPos == 0xffffffff || m_uiWriteLPos > m_uiPosition)
            {

               m_uiWriteLPos = m_uiPosition;

            }

            if (m_uiWriteUPos == 0xffffffff || m_uiWriteUPos < (m_uiPosition + uiWriteNow - 1))
            {

               m_uiWriteUPos = (m_uiPosition + uiWriteNow - 1);

            }

            ::memcpy_dup(&m_storage.get_data()[m_uiPosition - m_uiBufLPos], &((byte *)pdata)[uiWrite], (size_t) uiWriteNow);

            m_uiPosition += uiWriteNow;

            uiWrite += uiWriteNow;

         }

         if(uiWrite < nCount)
         {

            buffer(nCount - uiWrite);

         }

      }

   }


   void buffered_file::flush()
   {

      if(m_bDirty)
      {

         m_pfile->seek((filesize) m_uiWriteLPos, ::file::seek_begin);

         m_pfile->write(&m_storage.get_data()[m_uiWriteLPos - m_uiBufLPos], (memsize) (m_uiWriteUPos - m_uiWriteLPos + 1));

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



