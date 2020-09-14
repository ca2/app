#include "framework.h"


namespace experience
{


   namespace tranquillum
   {


      experience::experience()
      {



      }


      experience::~experience()
      {

      }


         ::estatus experience::initialize(::layered * pobjectContext)
         {

            auto estatus = ::experience::experience::initialize(pobjectContext);

            if (!estatus)
            {

               return estatus;

            }

#if !defined(CUBE)
            fork([this]()
               {

                  System.draw2d().set_cursor_set_from_matter("cursor/tranquillum");

               });
#endif

            return ::success;

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


      ::experience::frame * experience::experience_get_frame(const char * pszSchema)
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


   } // namespace tranquillum


} // namespace experience



