#include "framework.h"
#include "process.h"


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


   bool process::create_child_process(const ::scoped_string & scopedstrCmdLine, bool bPiped, const ::scoped_string & scopedstrDir, ::enum_priority epriority)
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


   bool process::write(const ::scoped_string & scopedstr)
   {

      return m_pipe.m_ppipeIn->write(str);

   }


   string process::read(bool bUntilExit)
   {

      __UNREFERENCED_PARAMETER(bUntilExit);

      return m_pipe.m_ppipeOut->read();

   }


   void process::wait_until_exit(const class time & timeWait)
   {
      
      auto start = ::time::now();

      while(true)
      {

         if(has_exited())
         {

            break;

         }

         if(timeWait > 0_s)
         {

            auto waitNow = minimum(timeWait - start.elapsed(), 100_ms);

            if (waitNow <= 0_s)
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


   bool process::synch_elevated(const ::scoped_string & scopedstrCmdLine,int iShow,const class time & timeTimeOut,bool * pbTimeOut)
   {

      return false;

   }


   bool process::kill()
   {

      return false;

   }



} // namespace operating_system



