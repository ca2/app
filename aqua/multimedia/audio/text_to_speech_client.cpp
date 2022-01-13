//
//  text_to_speech_client.cpp
//  aqua
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 25/11/21. 22:48
//  Copyright © 2021 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "text_to_speech_client.h"


namespace text_to_speech
{


   client::client()
   {
   
   
   }


   client::~client()
   {
      
      
   }


   void client::initialize_tts_speaker()
   {

      auto psystem = m_psystem->m_paquasystem;

      psystem->defer_audio();

      auto paudio = psystem->audio();

      m_ptexttospeechspeaker = paudio->create_text_to_speech_speaker();

   }


   __pointer(::text_to_speech::speaker) client::speaker()
   {
   
      if(!m_ptexttospeechspeaker)
      {
         
         initialize_tts_speaker();
         
      }
      
      return m_ptexttospeechspeaker;
   
   }


} // namespace text_to_speech



