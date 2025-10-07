#include "framework.h"

#include "aura/windowing/windowing.h"
#include "experience.h"
#include "berg/platform/session.h"
#include "berg/user/user/user.h"
#include "frame_001.h"
#include "frame_002.h"
#include "frame_005.h"
#include "frame_008.h"
#include "frame_011.h"
#include "frame_022.h"
#include "frame_Minimal001.h"


namespace experience_core
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

//#if !defined(CUBE)
//      fork([this]()
//         {
//
//            
//
//            auto puser = user();
//
//            auto pwindowing = system()->windowing();
//
//            pwindowing->set_cursor_set_from_matter(this, "cursor/antialiased-classic");
//
//         });
//#endif

      //return ::success;

   }


   experience::~experience()
   {
   }


   void experience::update()
   {
   }

   void experience::get_frame_list(string_array_base & stra)
   {

      stra.add("001");
      stra.add("002");
      stra.add("005");
      stra.add("008");
      stra.add("011");
      stra.add("022");
      stra.add("Minimal001");

   }


   ::pointer < ::experience::frame > experience::frame_experience(const ::scoped_string & scopedstrFrameSchema)
   {

      string strSchema(scopedstrFrameSchema);

      if(strSchema == "001")
      {

         return øcreate_new< ::experience_core::frame_001 >();

      }
      else if(strSchema == "002")
      {
               
         return øcreate_new< ::experience_core::frame_002 >();

      }
      else if(strSchema == "005")
      {
               
         return øcreate_new< ::experience_core::frame_005 >();

      }
      else if(strSchema == "008")
      {
               
         return øcreate_new< ::experience_core::frame_008 >();

      }
      else if(strSchema == "011")
      {
               
         return øcreate_new< ::experience_core::frame_011 >();

      }
      else if (strSchema == "022")
      {

         return øcreate_new < ::experience_core::frame_022>();

      }
      else if(strSchema == "Minimal001")
      {

         return øcreate_new< ::experience_core::frame_Minimal001 >();

      }

      return nullptr;

   }


} // namespace experience_core



