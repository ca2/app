// BitmDecoder.h -- the Most Significant Bit of ::u8 is First
// from 7-zip on 2012-12-23, dawn
#pragma once

//#include "../IStream.h"

namespace file
{

   namespace bitm
   {

      const u32 kNumBigValueBits = 8 * 4;
      const u32 kNumValueBytes = 3;
      const u32 kNumValueBits = 8  * kNumValueBytes;

      const u32 kMask = (1 << kNumValueBits) - 1;

      template<class TInByte>
      class decoder
      {
         u32 m_BitPos;
         u32 m_Value;
      public:
         TInByte m_Stream;
         bool Create(u32 bufferSize) { return m_Stream.Create(bufferSize); }
         void SetStream(reader *inStream) { m_Stream.SetStream(inStream);}
         void ReleaseStream() { m_Stream.ReleaseStream();}

         void Init()
         {
            m_Stream.Init();
            m_BitPos = kNumBigValueBits;
            Normalize();
         }

         u64 GetProcessedSize() const { return m_Stream.GetProcessedSize() - (kNumBigValueBits - m_BitPos) / 8; }

         void Normalize()
         {
            for (;m_BitPos >= 8; m_BitPos -= 8)
               m_Value = (m_Value << 8) | m_Stream.ReadByte();
         }

         u32 GetValue(u32 numBits) const
         {
            // return (m_Value << m_BitPos) >> (kNumBigValueBits - numBits);
            return ((m_Value >> (8 - m_BitPos)) & kMask) >> (kNumValueBits - numBits);
         }

         void MovePos(u32 numBits)
         {
            m_BitPos += numBits;
            Normalize();
         }

         u32 ReadBits(u32 numBits)
         {
            u32 res = GetValue(numBits);
            MovePos(numBits);
            return res;
         }

         void AlignToByte() { MovePos((32 - m_BitPos) & 7); }
      };

      typedef CLASS_DECL_CA2_FILE decoder < in_buffer > in_buffer_decoder;

   } // namespace bitm

} // namespace file
