#include "framework.h"
#include "frame_001.h"
#include "frame_002.h"
#include "frame_005.h"
#include "frame_008.h"
#include "frame_011.h"
#include "frame_013.h"
#include "frame_Minimal001.h"
#include "experience.h"
#include "base/platform/session.h"
#include "base/user/user/user.h"
#include "aura/windowing/windowing.h"


namespace experience_nanoui
{


   experience::experience()
   {



   }


   void experience::initialize(::particle * pparticle)
   {

      //auto estatus = 

      ::experience::experience::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

#if !defined(CUBE)
      fork([this]()
         {

            auto psession = get_session();

            auto puser = psession->user();

            auto pwindowing = system()->windowing();

            pwindowing->set_cursor_set_from_matter(this, "cursor/antialiased-classic");

         });
#endif

      //return ::success;

   }


   experience::~experience()
   {
   }


   void experience::update()
   {
   }

   void experience::get_frame_list(string_array & stra)
   {

      stra.add("001");
      stra.add("002");
      stra.add("005");
      stra.add("008");
      stra.add("011");
      stra.add("013");
      stra.add("Minimal001");

   }


   ::pointer < ::experience::frame > experience::frame_experience(const ::string & strFrameSchema)
   {

      string strSchema(strFrameSchema);

      if (strSchema == "001")
      {

         return __create_new< ::experience_nanoui::frame_001 >();

      }
      else if (strSchema == "002")
      {

         return __create_new< ::experience_nanoui::frame_002 >();

      }
      else if (strSchema == "005")
      {

         return __create_new< ::experience_nanoui::frame_005 >();

      }
      else if (strSchema == "008")
      {

         return __create_new< ::experience_nanoui::frame_008 >();

      }
      else if (strSchema == "011")
      {

         return __create_new< ::experience_nanoui::frame_011 >();

      }
      else if (strSchema == "013")
      {

         return __create_new< ::experience_nanoui::frame_013 >();

      }
      else if (strSchema == "Minimal001")
      {

         return __create_new< ::experience_nanoui::frame_Minimal001 >();

      }

      return nullptr;

   }


} // namespace experience_nanoui



