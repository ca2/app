#pragma once


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
      __pointer(::aura::library)       m_plibrary;
      LPFN_MULTIMEDIA_NEW_DECODER      m_lpfnNewDecoder;


      decoder_plugin();
      virtual ~decoder_plugin();


      virtual bool Load(const char * pszTitle);
      virtual ::multimedia::decoder * NewDecoder();

      virtual string GetPluginTitle();

   };


} // namespace multimedia




