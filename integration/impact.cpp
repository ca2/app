// From impact.cpp on 2023-01-15 09:46 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "impact.h"
#include "application.h"
//#include "render.h"
#include "document.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/platform/node.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"
#include "base/user/user/impact_system.h"
#include "base/user/user/split_impact.h"


namespace app_integration
{


   impact::impact()
   {

      m_flagNonClient.erase(e_non_client_background);

      m_flagNonClient.erase(e_non_client_focus_rect);

   }


   impact::~impact()
   {

   }


   //   void impact::assert_ok() const
   //   {
   //
   //      user::box::assert_ok();
   //
   //   }
   //
   //
   //   void impact::dump(dump_context & dumpcontext) const
   //   {
   //
   //      user::box::dump(dumpcontext);
   //
   //   }


#ifdef _DEBUG


   int64_t impact::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return  ::user::impact::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t impact::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return  ::user::impact::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   void impact::install_message_routing(::channel * psender)
   {

      ::user::impact::install_message_routing(psender);

      MESSAGE_LINK(MESSAGE_CREATE, psender, this, &impact::on_message_create);
      MESSAGE_LINK(MESSAGE_DESTROY, psender, this, &impact::on_message_destroy);

   }

   //% comspec % / k "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"


   void impact::on_message_create(::message::message * pmessage)
   {

      m_pathIntegration = acmedirectory()->module() / "shared_console_integration.exe";

      payload(FONTSEL_IMPACT) = true;

      ::pointer<::message::create> pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      {

         auto psignal = get_app()->get_signal("simple_checkbox");

         psignal->add_handler(this);

      }

      {

         auto psignal = get_app()->get_signal("no_client_frame");

         psignal->add_handler(this);

      }

      //auto estatus = 

      //__construct_new(m_prender);

      //if(!estatus)
      //{

      //   pcreate->set_fail();

      //   return;

      //}

      //m_prender->m_pimpact = this;

      auto pdocument = get_document();

      auto pimpactsystem = pdocument->m_pimpactsystem;

      string strId = pimpactsystem->m_atom;

      string strText;

      if (get_typed_parent<::user::split_impact>() != nullptr)
      {

         if (get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact") != nullptr)
         {

            auto pinteraction = get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact");

            pinteraction->_001SetText(strText, ::e_source_initialize);

         }

      }

   }


   //::file::path impact::get_path()
   //{

   //   return m_strName / m_strRelease / m_strPlatform / m_strConfiguration;

   //}


   void impact::on_message_destroy(::message::message * pmessage)
   {

   }


   void impact::fill()
   {

      add_platform("Win32");

      add_platform("x64");

   }


   void impact::add_platform(const ::scoped_string & scopedstrPlatform)
   {

      add_configuration(scopedstrPlatform, "Debug");

      add_configuration(scopedstrPlatform, "Release");

      add_configuration(scopedstrPlatform, "StaticDebug");

      add_configuration(scopedstrPlatform, "StaticRelease");


   }


   void impact::add_configuration(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration)
   {

      m_straName.add(m_strName + " " + scopedstrPlatform + " " + scopedstrConfiguration);

   }


   void impact::prepare()
   {

      for (auto & str : m_straName)
      {

         __construct_new(m_str2aOutput.add_new());

      }

   }


   void impact::start()
   {

      for (index i = 0; i < m_straName.size(); i++)
      {

         auto strName = m_straName[i];

         auto pstraOutput = m_str2aOutput[i];


         fork([strName, pstraOutput, this]()
   {

      int iExitCode = 0;

         acmenode()->command_system(*pstraOutput, iExitCode, m_pathIntegration + " " + strName);

         if (iExitCode == 0)
         {

            pstraOutput->add(strName + " Completed!!");

         }
         else
         {

            pstraOutput->add(strName + " Finished with error exit code: " + ::as_string(iExitCode) + "!");

         }

   });

      }


   }



   void impact::handle(::topic * ptopic, ::context * pcontext)
   {


      if (ptopic->m_atom == "openssl")
      {

         m_strName = "openssl";

         fill();

         prepare();

         start();

      }
      else if (ptopic->m_atom == "ffmpeg")
      {

         m_strName = "ffmpeg";

         fill();

         prepare();

         start();

      }
      else if (ptopic->m_atom == "simple_checkbox"
         || ptopic->m_atom == "no_client_frame")
      {

         set_need_redraw();

         post_redraw();

      }

      ::user::impact::handle(ptopic, pcontext);
   }


   ::user::document * impact::get_document()
   {

      return ::user::impact::get_document();

   }


   void impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (get_app()->application_properties().m_echeckNoClientFrame != ::e_check_checked)
      {

         ::rectangle_i32 rectangle = client_rectangle();

         for (index i = 0; i < 11; i++)
         {

            pgraphics->draw_inset_rectangle(rectangle, argb(180, 80, 80, 80));

            rectangle.deflate(1, 1);

         }

      }
      auto rect = client_rectangle();

      int y = rect.bottom - 50;
      for (int i = m_str2aOutput.get_upper_bound(); i >= 0; i--)
      {
         for (int j = 0; j < minimum(3, m_str2aOutput[i]->size()); j++)
         {


            pgraphics->text_out({ (double)20, (double)y }, m_straName[i] + " > " + m_str2aOutput[i]->last(-j - 1));

            y -= 30;

         }

      }

      //m_prender->_001OnDraw(pgraphics);

   }


   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = client_rectangle();

      if (rectangleClient.is_empty())
      {

         return;

      }

      //m_prender->m_rectangle = rectangleClient;

   }


} // namespace simple_drawing



