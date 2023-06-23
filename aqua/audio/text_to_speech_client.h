//
//  text_to_speech_client.hpp
//  aqua
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 25/11/21. 22:48
//  Copyright (c) 2021 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


////#include "acme/primitive/primitive/object.h"


namespace text_to_speech
{


   class CLASS_DECL_AQUA client :
      virtual public ::object
   {
   public:

      
      ::pointer<::text_to_speech::speaker>        m_ptexttospeechspeaker;
      
      
      client();
      ~client() override;
      
      
      virtual void initialize_tts_speaker();
      
      
      virtual ::pointer<::text_to_speech::speaker>speaker();
      

   };


} // namespace text_to_speech



