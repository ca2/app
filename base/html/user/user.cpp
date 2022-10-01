#include "framework.h"
#include "axis/html/html/data.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "base/user/userex/_userex.h"
//#endif
#include "axis/html/html/core_data.h"
#include "base/user/user/user.h"
#include "document.h"
#include "impact.h"
#include "base/user/user/multiple_document_template.h"


namespace base
{


   void user::initialize_html()
   {


      m_typeHtmlDocument = typeid(html_document);
      m_typeHtmlImpact = typeid(html_impact);

      ::factory::add_factory_item < html_document >();
      ::factory::add_factory_item < html_impact >();
      ::factory::add_factory_item < ::html::core_data::image >();

      auto ptemplate = __new(::user::multiple_document_template(
         "system/form",
         __type(html_document),
         get_simple_child_frame_type_info(),
         __type(html_impact)));

      m_ptemplateHtmlChildForm1 = ptemplate;

      add_document_template(ptemplate);

      //return ::success;

   }


} // namespace base



