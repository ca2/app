#include "framework.h"


namespace process
{


   process::process()
   {

      m_bPiped = false;
      m_iPid = 0;

   }


   process::~process()
   {


   }


   bool process::create_child_process(const ::string & strCmdLine, bool bPiped, const ::string & strDir, ::enum_priority epriority)
   {

      if(bPiped)
      {

         if(!m_pipe.create(false, true))
            return false;

      }

      m_bPiped = bPiped;

      return true;

   }


   bool process::write(const ::string & str)
   {

      return m_pipe.m_ppipeIn->write(str);

   }


   string process::read(bool bUntilExit)
   {

      __UNREFERENCED_PARAMETER(bUntilExit);

      return m_pipe.m_ppipeOut->read();

   }


   void process::wait_until_exit(i32 iWaitMax)
   {
auto tickStart = ::millis::now();

      i32 i = 1;

      while(true)
      {

         if(has_exited())
         {

            break;

         }

         if(iWaitMax >= 0 && tickStart.elapsed() > iWaitMax)
         {

            break;

         }

         sleep(100_ms);

         i++;

      }

   }


   bool process::has_exited()
   {

      return true;

   }


   bool process::synch_elevated(const ::string & strCmdLine,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut)
   {

      return false;

   }


   bool process::kill()
   {

      return false;

   }


   

} // namespace process




