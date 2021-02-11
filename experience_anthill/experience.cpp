#include "framework.h"


namespace experience
{


   namespace anthill
   {






         experience::experience()
         {

         }


         experience::~experience()
         {
         }


         ::e_status experience::initialize(::layered * pobjectContext)
         {

            auto estatus = ::experience::experience::initialize(pobjectContext);

            if (!estatus)
            {

               return estatus;

            }

            fork([this]()
               {

                  //System.draw2d()->set_cursor_set_from_matter("cursor/polar");

               });

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
               return new ::experience::anthill::frame_001;
            }
            else if(strSchema == "002")
            {
               return new ::experience::anthill::frame_002;
            }
            else if(strSchema == "005")
            {
               return new ::experience::anthill::frame_005;
            }
            else if(strSchema == "008")
            {
               return new ::experience::anthill::frame_008;
            }
            else if(strSchema == "011")
            {
               return new ::experience::anthill::frame_011;
            }
            else if(strSchema == "013")
            {
               return new ::experience::anthill::frame_013;
            }
            else if(strSchema == "Minimal001")
            {
               return new ::experience::anthill::frame_Minimal001;
            }

            return nullptr;

         }



   } // namespace anthill


} // namespace experience




