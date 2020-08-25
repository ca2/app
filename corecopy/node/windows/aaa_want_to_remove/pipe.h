#pragma once


namespace windows
{


   class CLASS_DECL_CORE pipe :
      virtual public ::process::pipe
   {
   public:


      class overlapped
      {
      public:
         pipe * m_ppipe;
         OVERLAPPED m_overlapped;
         inline overlapped * from(OVERLAPPED * poverlapped)
         {
            return (overlapped *)((BYTE *)poverlapped - sizeof(pipe *));
         }
      };


      char *               m_pchBuf;
      string               m_strRead;

      overlapped           m_overlapped;

      SECURITY_ATTRIBUTES  m_sa;
      HANDLE               m_hRead;
      HANDLE               m_hWrite;


      pipe();
      virtual ~pipe();


      virtual bool create(bool bBlock = true, bool bInherit = false);


      virtual bool not_inherit_read();
      virtual bool not_inherit_write();

      virtual bool write(const char * psz);
      virtual string read();
      virtual string one_pass_read();


      virtual void readex();


      static void WINAPI read_complete(
         u32 dwErrorCode,
         u32 dwNumberOfBytesTransfered,
         LPOVERLAPPED pOverlapped

         );

   };


} // namespace windows














































