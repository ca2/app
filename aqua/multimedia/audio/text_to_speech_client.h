//
//  text_to_speech_client.hpp
//  aqua
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 25/11/21. 22:48
//  Copyright © 2021 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


namespace text_to_speech
{


   class CLASS_DECL_AQUA client :
      virtual public ::object
   {
   public:

      
      __pointer(::text_to_speech::speaker)         m_ptexttospeechspeaker;
      
      
      client();
      ~client() override;
      
      
      virtual void initialize_tts_speaker();
      
      
      virtual __pointer(::text_to_speech::speaker) speaker();
      

   };


} // namespace text_to_speech



