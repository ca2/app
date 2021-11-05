// BitlDecoder.h -- the Least Significant Bit of byte is First
// from 7-zip on 2012-12-23, dawn
#pragma once

//#include "../IStream.h"

namespace file
{

   namespace bitl
   {

      const u32 kNumBigValueBits = 8 * 4;
      const u32 kNumValueBytes = 3;
      const u32 kNumValueBits = 8  * kNumValueBytes;

      const u32 kMask = (1 << kNumValueBits) - 1;

      extern byte kInvertTable[256];

      template < class TInByte >
      class base_decoder
      {
      protected:
         u32 m_BitPos;
         u32 m_Value;
         TInByte m_Stream;
      public:
         u32 NumExtraBytes;
         bool Create(u32 bufferSize) { return m_Stream.Create(bufferSize); }
         void SetStream(reader *inStream) { m_Stream.SetStream(inStream); }
         void ReleaseStream() { m_Stream.ReleaseStream(); }
         void Init()
         {
            m_Stream.Init();
            m_BitPos = kNumBigValueBits;
            m_Value = 0;
            NumExtraBytes = 0;
         }
         u64 GetProcessedSize() const { return m_Stream.GetProcessedSize() + NumExtraBytes - (kNumBigValueBits - m_BitPos) / 8; }

         void Normalize()
         {
            for (; m_BitPos >= 8; m_BitPos -= 8)
            {
               byte b = 0;
               if (!m_Stream.ReadByte(b))
               {
                  b = 0xFF; // check it
                  NumExtraBytes++;
               }
               m_Value = (b << (kNumBigValueBits - m_BitPos)) | m_Value;
            }
         }

         u32 ReadBits(u32 numBits)
         {
            Normalize();
            u32 res = m_Value & ((1 << numBits) - 1);
            m_BitPos += numBits;
            m_Value >>= numBits;
            return res;
         }

         bool ExtraBitsWereRead() const
         {
            if (NumExtraBytes == 0)
               return false;
            return ((u32)(kNumBigValueBits - m_BitPos) < (NumExtraBytes << 3));
         }
      };

      template < class TInByte >
      class decoder :
         public base_decoder < TInByte >
      {
         u32 m_NormalValue;

      public:
         void Init()
         {
            base_decoder<TInByte>::Init();
            m_NormalValue = 0;
         }

         void Normalize()
         {
            for (; this->m_BitPos >= 8; this->m_BitPos -= 8)
            {
               byte b = 0;
               if (!this->m_Stream.ReadByte(b))
               {
                  b = 0xFF; // check it
                  this->NumExtraBytes++;
               }
               m_NormalValue = (b << (kNumBigValueBits - this->m_BitPos)) | m_NormalValue;
               this->m_Value = (this->m_Value << 8) | kInvertTable[b];
            }
         }

         u32 GetValue(u32 numBits)
         {
            Normalize();
            return ((this->m_Value >> (8 - this->m_BitPos)) & kMask) >> (kNumValueBits - numBits);
         }

         void MovePos(u32 numBits)
         {
            this->m_BitPos += numBits;
            m_NormalValue >>= numBits;
         }

         u32 ReadBits(u32 numBits)
         {
            Normalize();
            u32 res = m_NormalValue & ((1 << numBits) - 1);
            MovePos(numBits);
            return res;
         }

         void AlignToByte() { MovePos((32 - this->m_BitPos) & 7); }

         byte ReadByte()
         {
            if (this->m_BitPos == kNumBigValueBits)
            {
               byte b = 0;
               if (!this->m_Stream.ReadByte(b))
               {
                  b = 0xFF;
                  this->NumExtraBytes++;
               }
               return b;
            }
            {
               byte b = (byte)(m_NormalValue & 0xFF);
               MovePos(8);
               return b;
            }
         }
      };

      typedef CLASS_DECL_CA2_FILE decoder < in_buffer > in_buffer_decoder;

   } // namespace bitl

} // namespace file
