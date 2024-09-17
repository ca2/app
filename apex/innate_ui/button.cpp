// Created by camilo on 2024-09-13 00:34 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "button.h"


namespace innate_ui
{


   button::button()
   {
   }


   button::~button()
   {

   }

   void button::set_callback_on_click(const ::procedure & callbackOnClick)
   {

         if (!callbackOnClick)
         {
            throw ::exception(error_bad_argument);

         }
         m_callbackOnClick = callbackOnClick;

   }

   void button::call_on_click()
   {

      m_callbackOnClick();
   }


} // namespace innate_ui

