// Created by camilo on 2022-06-28 02:11 <3ThomasBorregaardSorensen!! (Mummi and bilbo sleeping in bedroom above)
#include "framework.h"
#include "_main_hold_base.h"


static boolean g_bEnableAudio;


boolean main_hold_base::is_audio_enabled()
{

   return g_bEnableAudio;

}


void main_hold_base::enable_audio(bool bEnable)
{

   g_bEnableAudio = bEnable;

}

