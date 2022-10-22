#include "framework.h"


namespace operating_system
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

         m_pipe.initialize(this);

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


   void process::wait_until_exit(const class ::wait & wait)
   {
      
      auto start = ::wait::now();

      while(true)
      {

         if(has_exited())
         {

            break;

         }

         if(!wait.is_null())
         {

            auto waitNow = minimum(wait - start.elapsed(), 100_ms);

            if (!waitNow)
            {

               break;

            }

            preempt(waitNow);

         }
         else
         {

            preempt(100_ms);

         }

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


} // namespace operating_system



