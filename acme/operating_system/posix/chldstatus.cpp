#include "framework.h"
#include "acme/primitive/collection/map.h"
#include "acme/primitive/collection/int_map.h"
#include <sys/types.h>
#include <sys/wait.h>


struct chldstatus
{

   bool m_bRet;
   int  m_iExitCode;

};


typedef iptr_map < chldstatus > chldstatus_map;


critical_section * g_pcsChldStatus = nullptr;


chldstatus_map * g_pchldstatusmap = nullptr;


void init_chldstatus_cs()
{

   g_pcsChldStatus = memory_new critical_section;

   g_pchldstatusmap = memory_new iptr_map < chldstatus >;

}


void term_chldstatus_cs()
{

   ::acme::del(g_pchldstatusmap);

   ::acme::del(g_pcsChldStatus);

}


critical_section * get_chldstatus_cs()
{

   return g_pcsChldStatus;

}


chldstatus get_chldstatus(int iPid)
{

   critical_section_lock synchronouslock(get_chldstatus_cs());

   return g_pchldstatusmap->operator[](iPid);

}


// must be called under get_pid_cs lock
void init_chldstatus(int iPid)
{

   auto & chldstatus = g_pchldstatusmap->operator[](iPid);

   chldstatus.m_bRet = false;

   chldstatus.m_iExitCode = 0;

}


void ansios_sigchld_handler(int sig)
{

   int saved_errno = errno;

   int iExitCode;

   int iPid;

   while((iPid = waitpid(-1, &iExitCode,
                         WUNTRACED
#ifdef WNOHANG
      | WNOHANG
#endif
#ifdef WCONTINUED
      | WCONTINUED
#endif
   )) > 0)
   {

      {

         critical_section_lock synchronouslock(get_chldstatus_cs());

         auto ppair = g_pchldstatusmap->plookup(iPid);

         if(ppair != nullptr)
         {

            ppair->element2().m_bRet = true;

            ppair->element2().m_iExitCode = iExitCode;

         }

      }

   }

   errno = saved_errno;

}

