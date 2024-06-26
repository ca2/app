// From x264.h on 2023-06-22 16:38 <3ThomasBorregaardSørensen!!
#pragma once


//#include "aqua/audio/text_to_speech_client.h"


namespace integration { class context; }


namespace console_integration
{


   class third_winrt :
      virtual public ::particle
      //virtual public ::text_to_speech::client
   {
   public:



      ::pointer < ::integration::context > m_pcontext;


      third_winrt();
      ~third_winrt() override;


      void initialize(::particle* pparticle) override;


      void build();

      void clean();

      void prepare();

      void download();

      void configure();

      void compile();

      void install();

      void speak(::index iIndex, ::index iCount, const ::scoped_string& scopedstrText, int iExitCode);


   };


} // namespace console_integration



