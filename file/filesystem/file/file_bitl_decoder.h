// BitlDecoder.h -- the Least Significant Bit of unsigned char is First
// from 7-zip on 2012-12-23, dawn
#pragma once

//#include "../IStream.h"

namespace file
{

   namespace bitl
   {

      const unsigned int kNumBigValueBits = 8 * 4;
      const unsigned int kNumValueBytes = 3;
      const unsigned int kNumValueBits = 8  * kNumValueBytes;

      const unsigned int kMask = (1 << kNumValueBits) - 1;

      extern unsigned char kInvertTable[256];

      template < class TInByte >
      class base_decoder
      {
      protected:
         unsigned int m_BitPos;
         unsigned int m_Value;
         TInByte m_Stream;
      public:
         unsigned int NumExtraBytes;
         bool Create(unsigned int bufferSize) { return m_Stream.Create(bufferSize); }
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
               unsigned char b = 0;
               if (!m_Stream.ReadByte(b))
               {
                  b = 0xFF; // check it
                  NumExtraBytes++;
               }
               m_Value = (b << (kNumBigValueBits - m_BitPos)) | m_Value;
            }
         }

         unsigned int ReadBits(unsigned int numBits)
         {
            Normalize();
            unsigned int res = m_Value & ((1 << numBits) - 1);
            m_BitPos += numBits;
            m_Value >>= numBits;
            return res;
         }

         bool ExtraBitsWereRead() const
         {
            if (NumExtraBytes == 0)
               return false;
            return ((unsigned int)(kNumBigValueBits - m_BitPos) < (NumExtraBytes << 3));
         }
      };

      template < class TInByte >
      class decoder :
         public base_decoder < TInByte >
      {
         unsigned int m_NormalValue;

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
               unsigned char b = 0;
               if (!this->m_Stream.ReadByte(b))
               {
                  b = 0xFF; // check it
                  this->NumExtraBytes++;
               }
               m_NormalValue = (b << (kNumBigValueBits - this->m_BitPos)) | m_NormalValue;
               this->m_Value = (this->m_Value << 8) | kInvertTable[b];
            }
         }

         unsigned int GetValue(unsigned int numBits)
         {
            Normalize();
            return ((this->m_Value >> (8 - this->m_BitPos)) & kMask) >> (kNumValueBits - numBits);
         }

         void MovePos(unsigned int numBits)
         {
            this->m_BitPos += numBits;
            m_NormalValue >>= numBits;
         }

         unsigned int ReadBits(unsigned int numBits)
         {
            Normalize();
            unsigned int res = m_NormalValue & ((1 << numBits) - 1);
            MovePos(numBits);
            return res;
         }

         void AlignToByte() { MovePos((32 - this->m_BitPos) & 7); }

         unsigned char ReadByte()
         {
            if (this->m_BitPos == kNumBigValueBits)
            {
               unsigned char b = 0;
               if (!this->m_Stream.ReadByte(b))
               {
                  b = 0xFF;
                  this->NumExtraBytes++;
               }
               return b;
            }
            {
               unsigned char b = (unsigned char)(m_NormalValue & 0xFF);
               MovePos(8);
               return b;
            }
         }
      };

      typedef CLASS_DECL_CA2_FILE decoder < in_buffer > in_buffer_decoder;

   } // namespace bitl

} // namespace file
