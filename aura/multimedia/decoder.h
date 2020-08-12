#pragma once


namespace multimedia
{


   class decoder_plugin;


   class CLASS_DECL_AURA decoder :
      virtual public ::object
   {
   public:


      ::file::path                  m_pathOrigin;
      __pointer(decoder_plugin)     m_pplugin;
      bool                          m_bDecoderDecode;


      decoder();
      virtual ~decoder();


      virtual ::estatus multimedia_open(::file::file * varFile);
      virtual bool multimedia_close();

      virtual ::estatus impl_multimedia_open(::file::file * varFile);
      virtual bool impl_multimedia_close();


      virtual string             multimedia_get_origin_path();
      virtual void               multimedia_set_origin_path(const string & strOriginPath);


      virtual bool multimedia_get_attribute(::e_id attribute, var & var);

      void FillTitleInfo(string_array & wstraFormat, string2a & wstr2aTitle);


   };


} // namespace multimedia



