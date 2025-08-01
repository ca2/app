#include "framework.h"





   namespace experience
   {


      namespace lite

      {


         experience::experience(::particle * pparticle) :
            object(pparticle),
            ::experience::experience(pparticle)
         {

            fork([&]()
            {

               pdraw2d->set_cursor_set_from_matter("cursor/polar");

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


         ::pointer<::experience::frame>experience::get_frame(const ::scoped_string & scopedstrSchema)
         {

            string strSchema(scopedstrSchema);

            if(strSchema == "001")
            {
               return  __allocate ::experience::experience_lite::frame_001(this);
            }
            else if(strSchema == "002")
            {
               return  __allocate ::experience::experience_lite::frame_002(this);
            }
            else if(strSchema == "005")
            {
               return  __allocate ::experience::experience_lite::frame_005(this);
            }
            else if(strSchema == "008")
            {
               return  __allocate ::experience::experience_lite::frame_008(this);
            }
            else if(strSchema == "011")
            {
               return  __allocate ::experience::experience_lite::frame_011(this);
            }
            else if(strSchema == "013")
            {
               return  __allocate ::experience::experience_lite::frame_013(this);
            }
            else if(strSchema == "Minimal001")
            {
               return  __allocate ::experience::experience_lite::frame_Minimal001(this);
            }

            return nullptr;

         }


      } // namespace experience


   } // namespace experience







