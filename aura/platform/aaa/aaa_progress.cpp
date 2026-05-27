#include "framework.h"


void progress_listener::on_progress(::f64 dRate)
{

}


int_progress::int_progress()
{

   m_plistener          = nullptr;
   m_dProgressStart     = 0.0;
   m_dProgressEnd       = 1.0;

}


int_progress::~int_progress()
{

   m_plistener          = nullptr;

}


void int_progress::trace_progress(::i64 iStep)
{

   m_scalar.set(iStep);

}

void int_progress::trace_progress()
{

   if (m_plistener != nullptr)
   {

      m_plistener->on_progress(m_dProgressStart + (m_dProgressEnd - m_dProgressStart) * m_scalar.get_rate());

   }

}

void int_progress::progress_step()
{

   m_scalar++;

   trace_progress();

}



void int_progress::on_set_scalar(int_scalar_source * psource,e_scalar escalar,::i64 iValue,::i32 iFlags)
{

   if (m_scalar.m_psource == psource)
   {

      if (m_scalar.m_escalar == escalar)
      {

         trace_progress();

      }
      else
      {
      }

   }

}


progress_control::progress_control()
{

   defer_create_synchronization();


}


progress_control::~progress_control()
{

}


void progress_control::close_progress()
{

}

void progress_control::on_set_scalar(e_scalar escalar, ::f64 d, ::i32 iFlags)
{

}


void progress_control::get_scalar_minimum(e_scalar escalar, ::f64 & d)
{

   d = 0.0;

}


void progress_control::get_scalar(e_scalar escalar, ::f64 & d)
{

   d = (::f64)m_iStep / (::f64)m_iStepCount;

}


void progress_control::get_scalar_maximum(e_scalar escalar, ::f64 & d)
{

   d = 1.0;

}


void progress_control::redraw()
{




}

void progress_control::format_status(const ::scoped_string & scopedstrFormat)
{

   string strStatus(scopedstrFormat);

   strStatus.replace("%1", as_string(m_iStep));
   strStatus.replace("%2", as_string(m_iStepCount));

   m_strStatus = strStatus;

   redraw();

}

void progress_control::step()
{

   ASSERT(m_iStep + 1 <= m_iStepCount);

   if (m_iStep + 1 > m_iStepCount)
   {

      return;

   }

   m_iStep++;

   redraw();

}

