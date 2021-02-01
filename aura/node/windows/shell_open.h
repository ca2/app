#pragma once

#error ""
#include <ddeml.h>


namespace windows
{


   class CLASS_DECL_AURA shell_open :
      virtual public ::shell_open
   {
   public:


      HSZ               m_hszAppName;
      HSZ               m_hszSystemTopic;
      DWORD             m_dwDde;

      shell_open();
      virtual ~shell_open();


      virtual ::e_status initialize(::layered * pobjectContext) override;

      static HDDEDATA CALLBACK DdeCallback(
         u32 uType,
         u32 uFmt,
         HCONV hconv,
         HDDEDATA hsz1,
         HDDEDATA hsz2,
         HDDEDATA hdata,
         HDDEDATA dwData1,
         HDDEDATA dwData2
      );


      virtual ::e_status initialize_shell_open() override;

   };

} // namespace windows



