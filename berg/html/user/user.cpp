#include "framework.h"
#include "axis/html/html/data.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "berg/user/userex/_userex.h"
//#endif
#include "axis/html/html/core_data.h"
#include "berg/user/user/user.h"
#include "document.h"
#include "impact.h"
#include "berg/user/user/multiple_document_template.h"


namespace berg
{

   void user::initialize_html()
   {


      m_typeHtmlDocument = ::type<html_document>();
      m_typeHtmlImpact = ::type<html_impact>();

      factory()->add_factory_item<html_document>();
      factory()->add_factory_item<html_impact>();
      factory()->add_factory_item<::html::core_data::image>();

      // auto ptemplate = __initialize_new ::user::multiple_document_template(
      //    "system/form",
      //    ::type<html_document>(),
      //    get_simple_child_frame_type_info(),
      //    ::type<html_impact>()));

      // m_ptemplateHtmlChildForm1 = ptemplate;

      // add_document_template(ptemplate);

      // return ::success;
   }


} // namespace berg



