// BitmEncoder.h -- the Most Significant Bit of byte is First
// from 7-zip on 2012-12-23, dawn
#pragma once


//#include "../IStream.h"

namespace file
{

   namespace bitm
   {

      template<class TOutByte>
      class encoder
      {
         TOutByte m_Stream;
         u32 m_BitPos;
         byte m_CurByte;
      public:
         bool Create(u32 bufferSize) { return m_Stream.Create(bufferSize); }
         void SetStream(writer *outStream) { m_Stream.SetStream(outStream);}
         void ReleaseStream() { m_Stream.ReleaseStream(); }
         u64 GetProcessedSize() const { return m_Stream.GetProcessedSize() + (8 - m_BitPos + 7) / 8; }
         void Init()
         {
            m_Stream.Init();
            m_BitPos = 8;
            m_CurByte = 0;
         }
         HRESULT flush()
         {
            if (m_BitPos < 8)
               WriteBits(0, m_BitPos);
            return m_Stream.flush();
         }
         void WriteBits(u32 value, u32 numBits)
         {
            while (numBits > 0)
            {
               if (numBits < m_BitPos)
               {
                  m_CurByte |= ((byte)value << (m_BitPos -= numBits));
                  return;
               }
               numBits -= m_BitPos;
               u32 newBits = (value >> numBits);
               value -= (newBits << numBits);
               m_Stream.WriteByte((byte)(m_CurByte | newBits));
               m_BitPos = 8;
               m_CurByte = 0;
            }
         }
      };

      typedef CLASS_DECL_CA2_FILE encoder < out_buffer > out_buffer_encoder;

   } // namespace bitm

} // namespace file
