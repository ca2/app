// BitlEncoder.h -- the Least Significant Bit of ::u8 is First
// from 7-zip on 2012-12-23, dawn
#pragma once

//#include "../Common/OutBuffer.h"

namespace file
{

   namespace bitl
   {

      template < class TOutByte >
      class encoder
      {
         TOutByte m_Stream;
         u32 m_BitPos;
         ::u8 m_CurByte;
      public:
         bool Create(u32 bufferSize) { return m_Stream.Create(bufferSize); }
         void SetStream(writer *outStream) { m_Stream.SetStream(outStream); }
         void ReleaseStream() { m_Stream.ReleaseStream(); }
         u32 GetBitPosition() const { return (8 - m_BitPos); }
         u64 GetProcessedSize() const { return m_Stream.GetProcessedSize() + (8 - m_BitPos + 7) /8; }
         void Init()
         {
            m_Stream.Init();
            m_BitPos = 8;
            m_CurByte = 0;
         }
         HRESULT flush()
         {
            FlushByte();
            return m_Stream.flush();
         }
         void FlushByte()
         {
            if (m_BitPos < 8)
               m_Stream.WriteByte(m_CurByte);
            m_BitPos = 8;
            m_CurByte = 0;
         }
         void WriteBits(u32 value, u32 numBits)
         {
            while (numBits > 0)
            {
               if (numBits < m_BitPos)
               {
                  m_CurByte |= (value & ((1 << numBits) - 1)) << (8 - m_BitPos);
                  m_BitPos -= numBits;
                  return;
               }
               numBits -= m_BitPos;
               m_Stream.WriteByte((::u8)(m_CurByte | (value << (8 - m_BitPos))));
               value >>= m_BitPos;
               m_BitPos = 8;
               m_CurByte = 0;
            }
         }
         void WriteByte(::u8 b) { m_Stream.WriteByte(b);}
      };

      typedef CLASS_DECL_CA2_FILE encoder < out_buffer > out_buffer_encoder;

   } // namespace bitl

} // namespace file




