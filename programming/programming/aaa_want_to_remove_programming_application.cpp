#include "framework.h"


namespace programming
{


   application::application() :
      m_semCompiler(maximum(1, ::get_processor_count()), maximum(1, ::get_processor_count()))
   {

   }


   application::~application()
   {

   }


   void application::on_application_signal(::message::message * pmessage)
   {

      __pointer(::aura::application_message) psignal(pmessage);

      if (psignal->m_esignal == ::aura::application_message_process_init)
      {

      }
      else if (psignal->m_esignal == ::aura::application_message_init1)
      {

      }
      else  if (psignal->m_esignal == ::aura::application_message_term_instance)
      {

      }

   }


   void application::on_request(::create * pcreate)
   {


      if (pcreate->m_pcommandline->m_varQuery.has_property("introj"))
      {

         auto pcompiler  = __create_new < ::introjection::compiler >();

         bool bNew = true;

         __pointer(::apex::library) lib = pcompiler->compile(::dir::system() / "config\\xmpp_resident\\room\\ca2@livecoding.tv\\xmpp_bot.cpp", bNew);

         if (lib->m_pca2library == nullptr)
         {

            return;


         }

         __pointer(object) p = lib->alloc(get_context_application(), "plugin", this);

         if (p.is_null())
            return;

///         m_p = p.cast < plugin >();

      }



   }


   string application::get_visual_studio_build()
   {

      ::file::path path = dir::config() / "programming/vs_build.txt";

      string strBuild = Context.file().as_string(path);

      strBuild.trim();

      return strBuild;

   }


} // namespace programming


#ifdef MACOS
int get_processor_count()
{
   return 1;
}
#endif



