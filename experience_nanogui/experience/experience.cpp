#include "framework.h"


namespace experience_nanogui
{


   experience::experience()
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

            auto puser = psession->user();

            auto pwindowing = puser->windowing1();

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


   ::experience::frame * experience::frame_experience(const ::string & strFrameSchema)
   {

      string strSchema(strFrameSchema);

      if (strSchema == "001")
      {

         return new ::experience_nanogui::frame_001;

      }
      else if (strSchema == "002")
      {

         return new ::experience_nanogui::frame_002;

      }
      else if (strSchema == "005")
      {

         return new ::experience_nanogui::frame_005;

      }
      else if (strSchema == "008")
      {

         return new ::experience_nanogui::frame_008;

      }
      else if (strSchema == "011")
      {

         return new ::experience_nanogui::frame_011;

      }
      else if (strSchema == "013")
      {

         return new ::experience_nanogui::frame_013;

      }
      else if (strSchema == "Minimal001")
      {

         return new ::experience_nanogui::frame_Minimal001;

      }

      return nullptr;

   }


} // namespace experience_nanogui



