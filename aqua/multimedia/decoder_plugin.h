#pragma once


////#include "acme/prototype/prototype/object.h"


extern "C"
typedef ::multimedia::decoder * MULTIMEDIA_NEW_DECODER();

extern "C"
typedef MULTIMEDIA_NEW_DECODER * LPFN_MULTIMEDIA_NEW_DECODER;


namespace multimedia
{


   class CLASS_DECL_AQUA decoder_plugin :
      virtual public ::object
   {
   public:


      string                           m_strNewDecoder;
      string                           m_strTitle;
      ::factory::factory_pointer       m_pfactory;
      //LPFN_MULTIMEDIA_NEW_DECODER      m_lpfnNewDecoder;


      decoder_plugin();
      ~decoder_plugin() override;


      virtual void Load(const ::scoped_string & scopedstrTitle);
      virtual ::pointer<::multimedia::decoder>NewDecoder();

      virtual string GetPluginTitle();

   };


} // namespace multimedia




