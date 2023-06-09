//Created by camilo on 2021-03-26 00:44 BRT <3ThomasBS_
#include "framework.h"
#include "context.h"
//#include "acme/filesystem/file/file.h"
#include "acme/parallelization/counter.h"
#include "acme/parallelization/fork.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
//#include "acme/primitive/primitive/payload.h"
#include "acme/primitive/text/data.h"
#include "acme/primitive/text/text.h"
#include "acme/primitive/text/translator.h"


namespace acme
{

   
   context::context()
   {


      m_pcontext = this;

      m_papexcontext = nullptr;
      m_pauracontext = nullptr;


      m_pacmeapplication = nullptr;
      m_pacmesession = nullptr;
      m_pacmesystem = nullptr;
      m_pacmenode = nullptr;
      
//      m_ptexttranslator = memory_new ::text::translator();
//
//      m_ptexttranslator->m_pcontext = this;

   }


   context::~context()
   {

      //::release(m_ptexttranslator);

   }


   void context::initialize(::particle * pparticle)
   {

      ::task::initialize(pparticle);

      if(!m_pacmesystem)
      {

         m_pacmesystem = pparticle->m_pcontext->m_pacmesystem;

      }

      if(!m_pacmesession)
      {

         m_pacmesession = pparticle->m_pcontext->m_pacmesession;

      }

      if(!m_pacmeapplication)
      {

         m_pacmeapplication = pparticle->m_pcontext->m_pacmeapplication;

      }

      if (!m_pacmenode)
      {

         m_pacmenode = pparticle->m_pcontext->m_pacmenode;

      }

      m_pcontext = this;

   }


   void context::initialize_context()
   {

      __construct_new(m_ptexttranslator);

   }


   void context::initialize_context_1()
   {


   }


   ::dir_system * context::dirsystem()
   {

      return m_pacmesystem->m_pdirsystem;

   }


   ::file_system * context::filesystem()
   {

      return m_pacmesystem->m_pfilesystem;

   }


   void context::translate_text_data(::text::data * ptextdata)
   {

      bool bSet = false;

      if (ptextdata->m_atom.is_text())
      {

         if (ptextdata->m_atom.m_str.begins("text://"))
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


   ::acme_file* context::acmefile() { return m_pacmesystem->m_pacmefile; }
   ::acme_path* context::acmepath() { return m_pacmesystem->m_pacmepath; }
   ::acme_directory* context::acmedirectory() { return m_pacmesystem->m_pacmedirectory; }
   ::acme::node* context::acmenode() { return m_pacmesystem->node(); }



   ::payload context::file_payload(const ::payload & payloadFile)
   {

      return payloadFile;

   }


//   file_pointer context::get_file(const ::payload& payloadFile, ::file::e_open eopen)
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


   void context::fork_count(::count iCount, const ::function < void(index, index, index, index) > & function, const ::procedure & procedureCompletion, index iStart)
   {

      int iAffinityOrder = acmenode()->get_current_process_affinity_order();

      if (::get_task() != nullptr && ::get_task()->m_bAvoidProcedureFork)
      {

         iAffinityOrder = 1;

      }

      ::count cScan = maximum(1, minimum(iCount - iStart, iAffinityOrder));

      auto pcounter = __new(::counter(cScan, procedureCompletion));

      auto ptask = ::get_task();

      for (index iOrder = 0; iOrder < cScan; iOrder++)
      {

         auto ppredtask = __new(forking_count_task(this, iOrder, iOrder + iStart, cScan, iCount, function));

         //if (::is_set(ptask))
         //{

         //   ptask->add_reference(ppredtask);

         //}

         ppredtask->m_pcounter = pcounter;

         ppredtask->branch();

      }

      //return pcounter;

   }


} // namespace acme



