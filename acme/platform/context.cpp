//Created by camilo on 2021-03-26 00:44 BRT <3ThomasBS_
#include "framework.h"
#include "context.h"
#include "acme/filesystem/file/file.h"
#include "acme/primitive/primitive/payload.h"
#include "acme/primitive/text/data.h"
#include "acme/primitive/text/text.h"
#include "acme/primitive/text/translator.h"


namespace acme
{

   
   context::context()
   {


      m_pcontext = this;


      m_pacmeapplication = nullptr;
      m_papexapplication = nullptr;
      m_paquaapplication = nullptr;
      m_pauraapplication = nullptr;
      m_paxisapplication = nullptr;
      m_pbaseapplication = nullptr;
      m_pbredapplication = nullptr;
      m_pcoreapplication = nullptr;
      m_papexcontext = nullptr;
      m_pauracontext = nullptr;
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
      
//      m_ptexttranslator = memory_new ::text::translator();
//
//      m_ptexttranslator->m_pcontext = this;

   }


   context::~context()
   {

      //::release(m_ptexttranslator);

   }


   void context::initialize_context()
   {

      __construct_new(m_ptexttranslator);

   }


   void context::initialize_context_1()
   {


   }

   
   void context::translate_text_data(::text::data * ptextdata)
   {

      bool bSet = false;

      if (ptextdata->m_atom.is_text())
      {

         if (::str().begins(ptextdata->m_atom.m_str, "text://"))
         {

            auto psz = ansi_rchr(ptextdata->m_atom.m_str.c_str() + 7, '/');

            if (psz)
            {

               ptextdata->m_str = psz + 1;

               return;

            }

         }

      }

      ptextdata->m_str = ptextdata->m_atom;

   }


   ::text::text context::__text(const ::atom& atom)
   {

      return m_ptexttranslator->create_text_data(atom);

   }


   ::payload context::file_payload(const ::payload & payloadFile)
   {

      return payloadFile;

   }


//   file_pointer context::get_file(const ::payload& payloadFile, const ::file::e_open& eopen)
//   {
//
//      auto pfile = __create < ::file::file >();
//
//      auto path = payloadFile.file_path();
//
//      pfile->open(path, eopen);
//
//      return pfile;
//
//   }


   ::file::path context::defer_process_path(::file::path path)
   {

      return path;

   }


} // namespace acme



