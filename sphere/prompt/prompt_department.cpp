#include "framework.h"


namespace prompt
{


   department::department(::particle * pparticle) :
      ::acme::department(pparticle)
   {

   }


   department::~department()
   {

   }


   void department::construct()
   {

      //m_strAppName            = _strdup("command");
      //m_strBaseSupportId      = "ca2_command";
      //m_eexclusiveinstance    = ::e_exclusive_instance_local;

   }


   bool department::init_instance()
   {

      add_factory_item <prompt::document >();
      add_factory_item <prompt::frame >();
      add_factory_item <prompt::impact >();
      add_factory_item <prompt::pane_impact >();
      add_factory_item <prompt::primary_impact >();

      if (!::acme::department::init_instance())
      {

         return false;

      }

      puser->filemanager()->m_strLevelUp = "levelup";

//      if(m_strId == "command")
      {

         ::user::single_document_template* pDocTemplate;
         pDocTemplate = memory_new ::user::single_document_template(
         this,
         "system/form",
         __type(prompt::document),
         __type(prompt::frame),
         __type(prompt::pane_impact));
         papp->add_document_template(pDocTemplate);
         m_ptemplateCommandMain = pDocTemplate;

         m_ptemplateCommandMain->open_new_document(get_app());

      }

      return true;

   }


   void department::term_instance()
   {

      apex::department::term_instance();

   }


   //void department::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   //{

   //   ::acme::department::route_command(pcommand);

   //}


   void department::OnFileManagerOpenFile(::filemanager::data * pdata, ::file::item_array & itema)
   {
      __UNREFERENCED_PARAMETER(pdata);
      if(itema.get_size() > 0)
      {
         pcontext->m_papexcontext->os().file_open(this, itema[0]->m_filepathFinal, "", itema[0]->m_filepathFinal.folder());
//#ifdef WINDOWS_DESKTOP
//
//         ::ShellExecuteW(
//         nullptr,
//         L"open",
//         utf8_to_unicode(itema[0]->m_filepathFinal),
//         nullptr,
//         utf8_to_unicode(itema[0]->m_filepathFinal.folder()),
//         e_display_normal);
//
//#else
//
//         throw ::exception(todo);
//
//#endif

      }

   }

} // namespace prompt



