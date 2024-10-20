#include "framework.h"
#include "experience.h"
#include "frame_001.h"
#include "frame_002.h"
#include "frame_005.h"
#include "frame_008.h"
#include "frame_011.h"
#include "frame_022.h"
#include "frame_Minimal001.h"


namespace experience_anthill
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
      stra.add("022");
      stra.add("Minimal001");

   }


   ::pointer < ::experience::frame > experience::frame_experience(const ::string & pszSchema)
   {

      string strSchema(pszSchema);

      if (strSchema == "001")
      {
         return ___new ::experience_anthill::frame_001 ();
      }
      else if (strSchema == "002")
      {
         return ___new ::experience_anthill::frame_002 ();
      }
      else if (strSchema == "005")
      {
         return ___new ::experience_anthill::frame_005 ();
      }
      else if (strSchema == "008")
      {
         return ___new ::experience_anthill::frame_008 ();
      }
      else if (strSchema == "011")
      {
         return ___new ::experience_anthill::frame_011 ();
      }
      else if (strSchema == "022")
      {
         return ___new ::experience_anthill::frame_022 ();
      }
      else if (strSchema == "Minimal001")
      {
         return ___new ::experience_anthill::frame_Minimal001 ();
      }

      return nullptr;

   }


} // namespace experience_anthill




