// From third_winrt.h on 2023-07-14 22:44 <3ThomasBorregaardSørensen!!
#pragma once


//#include "aqua/audio/text_to_speech_client.h"


namespace integration { class context; }


namespace console_integration
{


   class third :
      virtual public ::particle
    //   virtual public ::text_to_speech::client
   {
   public:




      ::pointer < ::integration::context > m_pcontext;


      third();
      ~third() override;


      void initialize(::particle* pparticle);


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



