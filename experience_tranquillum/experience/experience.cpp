#include "framework.h"
#include "aura/windowing/windowing.h"
#include "experience.h"
#include "frame_001.h"
#include "frame_002.h"
#include "frame_005.h"
#include "frame_008.h"
#include "frame_011.h"
#include "frame_022.h"
#include "frame_Minimal001.h"
#include "berg/platform/session.h"
#include "berg/user/user/user.h"


namespace experience_tranquillum
{


   experience::experience()
   {



   }


   experience::~experience()
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

            system()->windowing()->set_cursor_set_from_matter(this, "cursor/tranquillum");

         });

#endif

      //return ::success;

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


   ::pointer <::experience::frame > experience::frame_experience(const ::scoped_string & scopedstrSchema)
   {

      string strSchema(scopedstrSchema);

      if(strSchema == "001")
      {

         return  allocateø frame_001();

      }
      else if(strSchema == "002")
      {

         return  allocateø frame_002();

      }
      else if(strSchema == "005")
      {

         return  allocateø frame_005();

      }
      else if(strSchema == "008")
      {

         return  allocateø frame_008();

      }
      else if(strSchema == "011")
      {

         return  allocateø frame_011();

      }
      else if(strSchema == "022")
      {

         return  allocateø frame_022();

      }
      else if(strSchema == "Minimal001")
      {

         return  allocateø frame_Minimal001();

      }

      return nullptr;

   }


} // namespace experience_tranquillum



