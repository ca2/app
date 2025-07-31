#pragma once


#include "acme/platform/department.h"
#include "acme/prototype/collection/string_map.h"

#include "acme/exception/status.h"


inline status < ::color::color > __indexed_color(unsigned int u32Index)
{

   ::color::color color;

   color.m_ui = u32Index;

	return status < ::color::color >(color, ::success_color_index);

}



namespace html
{


   using string_to_color = string_map < status < ::color::color > >;


   using named_color = string_to_color;


   class CLASS_DECL_AXIS html:
      public ::acme::department
   {
   public:



      ::color::color                         m_clrInvalid;   // an invalid color
      unsigned short                                    m_percentMax;   // maximum allowable percentage value
      named_color                            m_namedcolor;   // collection of named colors
      ::pointer<LiteHTMLEntityResolver>      m_pentitysolver;


      html();
      ~html() override;


      virtual void initialize(::particle * pparticle) override;


      string special_chars(const ::scoped_string & scopedstr);
      string entities(const ::scoped_string & scopedstr);
      string htmlpre(const ::scoped_string & scopedstr);
      int resolve_entity(const ::scoped_string & scopedstrEntity,string & strChar);

      string resolve_entities(const ::scoped_string & scopedstr);


      e_tag tag_name_to_id(atom idTag);
      edisplay display_name_to_id(const ::payload & varDisplay,e_tag e_tag);
      edisplay tag_to_display(e_tag etag);
      atom concat(atom id1,atom id2);

      virtual bool defer_get_html(string& strHtml, ::file::path& pathHtml, ::object* pparticle, const ::payload & payload);

      static bool tag_visible(e_tag etag);

   };


} // namespace html



