#include "framework.h"


namespace write_text
{


   write_text::write_text()
   {


   }


   write_text::~write_text()
   {


   }


   class font_department * write_text::fonts()
   {

      synchronous_lock synchronouslock(mutex());

      if (m_pfontdepartment == nullptr)
      {

         auto estatus = __construct(m_pfontdepartment);

         if (!estatus)
         {

            return nullptr;

         }

         //estatus = m_pfontdepartment->init1();

         //if (!estatus)
         //{

         //   return nullptr;

         //}

         __pointer(::aura::system) psystem = m_psystem;
         
         psystem->process_subject(id_font_enumeration);

      }

      return m_pfontdepartment;

   }


   ::e_status write_text::term()
   {

      try
      {

         if (m_pfontdepartment)
         {

            m_pfontdepartment->finalize();

         }

      }
      catch (...)
      {

      }

      auto estatus = ::acme::department::term();

      return success;

   }


   ::e_status write_text::finalize()
   {

      m_pfontdepartment.release();

      auto estatus = ::acme::department::finalize();

      return estatus;

   }



} // namespace write_text




