//Created by camilo on 2021-03-26 00:44 BRT <3ThomasBS_
#include "framework.h"
#include "acme/primitive/text/_.h"


namespace acme
{

   
   context::context()
   {

      m_pcontext = this;
      m_papexcontext = nullptr;
      m_pauracontext = nullptr;
      m_papexapplication = nullptr;
      m_paquaapplication = nullptr;
      m_pauraapplication = nullptr;
      m_paxisapplication = nullptr;
      m_pbaseapplication = nullptr;
      m_pbredapplication = nullptr;
      m_pcoreapplication = nullptr;
      m_papexsession = nullptr;
      m_paquasession = nullptr;
      m_paurasession = nullptr;
      m_paxissession = nullptr;
      m_pbasesession = nullptr;
      m_pbredsession = nullptr;
      m_pcoresession = nullptr;
      m_pacmesystem = nullptr;
      m_papexsystem = nullptr;
      m_paquasystem = nullptr;
      m_paurasystem = nullptr;
      m_paxissystem = nullptr;
      m_pbasesystem = nullptr;
      m_pbredsystem = nullptr;
      m_pcoresystem = nullptr;
      m_pacmenode = nullptr;
      m_papexnode = nullptr;
      m_pauranode = nullptr;
      
      m_ptexttranslator = new ::text::translator();

      m_ptexttranslator->m_pcontext = this;

   }


   context::~context()
   {

      ::release(m_ptexttranslator);

   }


   ::e_status context::initialize_context()
   {

      return ::success;

   }

   
   void context::translate_text_data(::text::data * ptextdata)
   {

      bool bSet = false;

      if (ptextdata->m_id.is_text())
      {

         if (::str::begins(ptextdata->m_id.m_psz, "text://"))
         {

            auto psz = ansi_rchr(ptextdata->m_id.m_psz + 7, '/');

            if (psz)
            {

               ptextdata->m_str = psz + 1;

               return;

            }

         }

      }

      ptextdata->m_str = ptextdata->m_id;

   }


   ::text::text context::__text(const ::id& id)
   {

      return m_ptexttranslator->create_text_data(id);

   }


   ::payload context::file_payload(const ::payload & payloadFile)
   {

      return payloadFile;

   }


   file_transport context::get_file(const ::payload& varFile, const ::file::e_open& eopen)
   {

      __pointer(::file::file) pfile;

      auto estatus = __construct(pfile);

      if (!estatus)
      {

         return estatus;

      }

      auto path = varFile.get_file_path();
      
      estatus = pfile->open(path, eopen);

      if (!estatus)
      {

         return estatus;

      }

      return pfile;

   }


} // namespace acme



