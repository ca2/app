#pragma once


////#include "acme/prototype/prototype/object.h"
//#include "acme/filesystem/filesystem/path.h"


class string_array_array_base;


namespace multimedia
{


   class decoder_plugin;


   class CLASS_DECL_AQUA decoder :
      virtual public ::object
   {
   public:


      ::file::path                  m_pathOrigin;
      ::pointer<decoder_plugin>     m_pplugin;
      bool                          m_bDecoderDecode;


      decoder();
      ~decoder() override;


      virtual void      multimedia_open(::file::file * pfile);
      virtual void      multimedia_close();

      virtual void      impl_multimedia_open(::file::file * payloadFile);
      virtual void      impl_multimedia_close();


      virtual string          multimedia_get_origin_path();
      virtual void            multimedia_set_origin_path(const ::scoped_string & scopedstrOriginPath);


      virtual bool            multimedia_get_attribute(::enum_id attribute, ::payload & payload);

      virtual void            FillTitleInfo(string_array_base & wstraFormat, string_array_array_base & wstr2aTitle);


   };


} // namespace multimedia



