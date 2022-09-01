#include "framework.h"
#include "aura/windowing/windowing.h"
#include "experience.h"
#include "frame_001.h"
#include "frame_002.h"
#include "frame_005.h"
#include "frame_008.h"
#include "frame_011.h"
#include "frame_013.h"
#include "frame_Minimal001.h"
#include "base/platform/session.h"
#include "base/user/user/user.h"


namespace experience_tranquillum
{


   experience::experience()
   {



   }


   experience::~experience()
   {

   }


   void experience::initialize(::object * pobject)
   {

      //auto estatus = 
         
      ::experience::experience::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

#if !defined(CUBE)

      fork([this]()
         {

            auto psession = get_session();

            psession->user()->windowing1()->set_cursor_set_from_matter(this, "cursor/tranquillum");

         });

#endif

      //return ::success;

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


   ::experience::frame * experience::frame_experience(const ::string & pszSchema)
   {

      string strSchema(pszSchema);

      if(strSchema == "001")
      {

         return  new frame_001;

      }
      else if(strSchema == "002")
      {

         return  new frame_002;

      }
      else if(strSchema == "005")
      {

         return  new frame_005;

      }
      else if(strSchema == "008")
      {

         return  new frame_008;

      }
      else if(strSchema == "011")
      {

         return  new frame_011;

      }
      else if(strSchema == "013")
      {

         return  new frame_013;

      }
      else if(strSchema == "Minimal001")
      {

         return  new  frame_Minimal001;

      }

      return nullptr;

   }


} // namespace experience_tranquillum



