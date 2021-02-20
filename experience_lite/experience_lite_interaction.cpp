#include "framework.h"





   namespace experience
   {


      namespace lite

      {


         experience::experience(::layered * pobjectContext) :
            object(pobject),
            ::experience::experience(pobject)
         {

            fork([&]()
            {

               System.draw2d()->set_cursor_set_from_matter("cursor/polar");

            });

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


         __pointer(::experience::frame) experience::get_frame(const char * pszSchema)
         {

            string strSchema(pszSchema);

            if(strSchema == "001")
            {
               return  __new(::experience::experience_lite::frame_001(get_object()));
            }
            else if(strSchema == "002")
            {
               return  __new(::experience::experience_lite::frame_002(get_object()));
            }
            else if(strSchema == "005")
            {
               return  __new(::experience::experience_lite::frame_005(get_object()));
            }
            else if(strSchema == "008")
            {
               return  __new(::experience::experience_lite::frame_008(get_object()));
            }
            else if(strSchema == "011")
            {
               return  __new(::experience::experience_lite::frame_011(get_object()));
            }
            else if(strSchema == "013")
            {
               return  __new(::experience::experience_lite::frame_013(get_object()));
            }
            else if(strSchema == "Minimal001")
            {
               return  __new( ::experience::experience_lite::frame_Minimal001(get_object()));
            }

            return nullptr;

         }


      } // namespace experience


   } // namespace experience







