#include "framework.h"
#include "trace.h"
#include "log.h"
#include "acme/constant/message.h"
#include "acme/parallelization/task.h"
#include "acme/platform/system.h"
#include "acme/_operating_system.h"


thread_local ::thread_local_pointer<logger>  t_plogger;


void logger::t_construct(::acme::context * pcontext)
{

   pcontext->__construct(t_plogger);

}


void logger::t_release()
{

   ::release(t_plogger);

}



trace::trace()
{

   //m_pobject = pparticle;

}


trace::~trace()
{

}



trace_category::trace_category()
{

   m_etracelevelMinimum    = e_trace_level_information;
   m_etracecategory        = e_trace_category_general;
   m_bEnabled              = true;

}


trace_category::~trace_category()
{

}






tracer& tracer::operator << (const exception& exception)
{

   m_str += exception.m_strMessage  + " (" + __string(exception.m_estatus) + ")";

   return *this;

}


tracer& tracer::operator << (const e_status& estatus)
{

   m_str += __string(estatus);

   return *this;

}


tracer& tracer::operator << (const enum_status& estatus)
{

   m_str += __string(estatus);

   return *this;

}


tracer & tracer::operator << (const string & str)
{

   m_str += str;

   return *this;

}


tracer & tracer::operator << (const char * psz)
{

   m_str += string(psz);

   return *this;

}


tracer & tracer::operator << (enum_flush)
{

   flush();

   return *this;

}


//void tracer::print(const ::string & str)
//{
//
//   m_str += str;
//
//}


tracer & tracer::operator << (const integral_byte & memsize)
{

   if (memsize < 1_kb)
   {

      return format_output("%d bytes", memsize);

   }
   else if (memsize < 1_mb)
   {

      return format_output("%0.2f kb", (double)memsize / (double)(1_kb));

   }
   else if (memsize < 1_gb)
   {

      return format_output("%0.2f MB", (double)memsize / (double)(1_mb));

   }
   else
   {

      return format_output("%0.2f GB", (double)memsize / (double)(1_gb));

   }

}


void tracer::flush()
{

   auto plogger = ::is_set(m_plogger) ? m_plogger : t_plogger.m_p;

   if(::is_null(plogger))
   {

      ::logger::t_construct(m_pcontext);

      plogger = t_plogger.m_p;

   }

   if (::is_set(plogger))
   {

      plogger->print(m_etracelevel, m_etracecategory, m_pszFunction, m_pszFile, m_iLine, m_str);

   }

}

