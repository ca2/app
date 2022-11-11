#include "framework.h"
#include "exit_status.h"


namespace operating_system
{


   exit_status::exit_status()
   {

      m_iExitCode = 0;
      m_iExitSignal = 0;
      m_iExitStop = 0;

   }


} // namespace operating_system



