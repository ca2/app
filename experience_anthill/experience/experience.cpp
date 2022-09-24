#include "framework.h"
#include "experience.h"
#include "frame_001.h"
#include "frame_002.h"
#include "frame_005.h"
#include "frame_008.h"
#include "frame_011.h"
#include "frame_013.h"
#include "frame_Minimal001.h"


namespace experience_anthill
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

      //fork([this]()
      //   {

      //      //pdraw2d->set_cursor_set_from_matter("cursor/polar");

      //   });

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

      if (strSchema == "001")
      {
         return new ::experience_anthill::frame_001;
      }
      else if (strSchema == "002")
      {
         return new ::experience_anthill::frame_002;
      }
      else if (strSchema == "005")
      {
         return new ::experience_anthill::frame_005;
      }
      else if (strSchema == "008")
      {
         return new ::experience_anthill::frame_008;
      }
      else if (strSchema == "011")
      {
         return new ::experience_anthill::frame_011;
      }
      else if (strSchema == "013")
      {
         return new ::experience_anthill::frame_013;
      }
      else if (strSchema == "Minimal001")
      {
         return new ::experience_anthill::frame_Minimal001;
      }

      return nullptr;

   }


} // namespace experience_anthill




