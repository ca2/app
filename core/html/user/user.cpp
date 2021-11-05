#include "framework.h"
#include "_user.h"
#include "core/html/html/data.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif



namespace core
{


   ::e_status user::initialize_html()
   {


      m_typeHtmlDocument = typeid(html_document);
      m_typeHtmlView = typeid(html_view);

      create_factory < html_document >();
      create_factory < html_view >();
      create_factory < ::html::core_data::image >();

      auto ptemplate = __new(::user::multiple_document_template(
         "system/form",
         __type(html_document),
         get_simple_child_frame_type_info(),
         __type(html_view)));

      m_ptemplateHtmlChildForm1 = ptemplate;

      add_document_template(ptemplate);

      return ::success;

   }


} // namespace userex



