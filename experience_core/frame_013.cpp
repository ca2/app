#include "framework.h"

   namespace experience
   {



         namespace core
         {


            frame_013::frame_013()
            {

               m_bHollow = true;

            }


            frame_013::~frame_013()
            {

            }


            ::e_status frame_013::destroy()
            {

               auto estatus = frame_008::destroy();

               return estatus;

            }




         } // namespace core


   } // namespace experience



