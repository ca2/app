// Created by camilo on 2022-06-28 02:05 <3ThomasBorregaardSorensen!! ThomasLikesNumber5 (Mummi and bilbo sleeping in bedroom above)
#pragma once


#include "acme/primitive/primitive/element.h"


class CLASS_DECL_ACME main_hold_base :
   virtual public ::element
{
public:


   ::pointer<::acme::application>        m_pacmeapplication;


   static tristate is_audio_enabled();

   static void enable_audio(bool bEnable = true);


};



