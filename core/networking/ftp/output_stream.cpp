#include "framework.h"
#include "_.h"
#include "output_stream.h"
#include "acme/prototype/prototype/memory.h"


namespace ftp
{


   output_stream::implementation::implementation(const string& strEolCharacterSequence, const string& strStreamName) :
      mc_strEolCharacterSequence(strEolCharacterSequence),
      m_iCurrentPos(0),
      m_strStreamName(strStreamName)
   {
   }

   bool output_stream::implementation::GetNextLine(string& strLine)// const
   {

      i64 iFind = m_vBuffer.find_index(mc_strEolCharacterSequence, m_iCurrentPos);

      if (::not_found(iFind))
      {

         return false;

      }

      strLine = m_vBuffer.substr((strsize) m_iCurrentPos, (strsize) (iFind - m_iCurrentPos));

      m_iCurrentPos = (strsize) (iFind + mc_strEolCharacterSequence.size());

      return true;

   }


   void output_stream::implementation::OnPreBytesSend(u8 * pszBuffer, memsize bufferSize, memsize& bytesToSend)
   {

      for (bytesToSend = 0; m_iCurrentPos < m_vBuffer.length() && bytesToSend < bufferSize; ++m_iCurrentPos, ++bytesToSend)
      {

         pszBuffer[bytesToSend] = m_vBuffer[m_iCurrentPos];

      }

   }


   output_stream::output_stream(const string& strEolCharacterSequence, const string& strStreamName) :
      m_pimpl(__new implementation(strEolCharacterSequence, strStreamName))
   {
   }

   output_stream::~output_stream() {}

   void output_stream::SetBuffer(const string& strBuffer)
   {
      m_pimpl->m_vBuffer = strBuffer;
   }

   const string& output_stream::GetBuffer()
   {
      return m_pimpl->m_vBuffer;
   }


   void output_stream::SetStartPosition()
   {

      m_pimpl->m_iCurrentPos = 0;

   }


   bool output_stream::GetNextLine(string& strLine)
   {

      return m_pimpl->GetNextLine(strLine);

   }


   string output_stream::GetLocalStreamName() const
   {

      return m_pimpl->m_strStreamName;

   }


   ::u32 output_stream::GetLocalStreamSize() const
   {
       return (::u32) m_pimpl->m_vBuffer.size();
   }

   void output_stream::SetLocalStreamOffset(::u32 dwOffsetFromBeginOfStream)
   {
      m_pimpl->m_iCurrentPos = dwOffsetFromBeginOfStream;
   }

   void output_stream::OnBytesReceived(const memory& vBuffer, long lReceivedBytes)
   {
      m_pimpl->m_vBuffer +=  vBuffer.get_string(0, lReceivedBytes);
   }

   void output_stream::OnPreBytesSend(u8 * pszBuffer, memsize bufferSize, memsize& bytesToSend)
   {
      m_pimpl->OnPreBytesSend(pszBuffer, bufferSize, bytesToSend);
   }


} // namespace ftp




