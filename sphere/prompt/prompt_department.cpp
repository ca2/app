#include "framework.h"


namespace prompt
{


   department::department(::layered * pobjectContext) :
      ::apex::department(pobject)
   {

   }


   department::~department()
   {

   }


   void department::construct()
   {

      //m_strAppName            = _strdup("command");
      //m_strBaseSupportId      = "ca2_command";
      //m_eexclusiveinstance    = ::ExclusiveInstanceLocal;

   }


   bool department::init_instance()
   {

      create_factory <prompt::document >();
      create_factory <prompt::frame >();
      create_factory <prompt::view >();
      create_factory <prompt::pane_view >();
      create_factory <prompt::primary_view >();

      if (!::apex::department::init_instance())
      {

         return false;

      }

      puser->filemanager()->m_strLevelUp = "levelup";

//      if(m_strId == "command")
      {

         ::user::single_document_template* pDocTemplate;
         pDocTemplate = new ::user::single_document_template(
         this,
         "system/form",
         __type(prompt::document),
         __type(prompt::frame),
         __type(prompt::pane_view));
         Application.add_document_template(pDocTemplate);
         m_ptemplateCommandMain = pDocTemplate;

         m_ptemplateCommandMain->open_new_document(get_context_application());

      }

      return true;

   }


   void department::term_instance()
   {

      apex::department::term_instance();

   }


   //void department::route_command_message(::user::command * pcommand)
   //{

   //   ::apex::department::route_command_message(pcommand);

   //}


   void department::OnFileManagerOpenFile(::filemanager::data * pdata, ::file::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(itema.get_size() > 0)
      {
         Context.os().file_open(this, itema[0]->m_filepathFinal, "", itema[0]->m_filepathFinal.folder());
//#ifdef WINDOWS_DESKTOP
//
//         ::ShellExecuteW(
//         nullptr,
//         L"open",
//         ::str::international::utf8_to_unicode(itema[0]->m_filepathFinal),
//         nullptr,
//         ::str::international::utf8_to_unicode(itema[0]->m_filepathFinal.folder()),
//         e_display_normal);
//
//#else
//
//         __throw(todo());
//
//#endif

      }

   }

} // namespace prompt



