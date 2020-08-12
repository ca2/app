#include "framework.h"


namespace user
{


   namespace experience
   {


      namespace experience_core
      {


         interaction::interaction(::object * pobject) :
            object(pobject),
            ::experience::experience(pobject)
         {

            ::fork(get_context_application(), [&]()
            {

               System.draw2d().set_cursor_set_from_matter("cursor/antialiased-classic");

            });

         }


         interaction::~interaction()
         {
         }


         void interaction::update()
         {
         }

         void interaction::get_frame_list(string_array & stra)
         {

            stra.add("001");
            stra.add("002");
            stra.add("005");
            stra.add("008");
            stra.add("011");
            stra.add("013");
            stra.add("Minimal001");

         }


         __pointer(::experience::frame) interaction::experience_get_frame(const char * pszSchema)
         {

            string strSchema(pszSchema);

            if(strSchema == "001")
            {
               return  __alloc(new ::experience::experience_core::frame_001(get_object()));
            }
            else if(strSchema == "002")
            {
               return  __alloc(new ::experience::experience_core::frame_002(get_object()));
            }
            else if(strSchema == "005")
            {
               return  __alloc(new ::experience::experience_core::frame_005(get_object()));
            }
            else if(strSchema == "008")
            {
               return  __alloc(new ::experience::experience_core::frame_008(get_object()));
            }
            else if(strSchema == "011")
            {
               return  __alloc(new ::experience::experience_core::frame_011(get_object()));
            }
            else if(strSchema == "013")
            {
               return  __alloc(new ::experience::experience_core::frame_013(get_object()));
            }
            else if(strSchema == "Minimal001")
            {
               return  __alloc(new  ::experience::experience_core::frame_Minimal001(get_object()));
            }

            return nullptr;

         }


      } // namespace experience


   } // namespace experience


} // namespace user




