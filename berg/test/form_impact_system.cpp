#include "berg/platform.h"
#include "berg/user/user/user.h"
#include "berg/user/user/impact_system.h"
#include "berg/user/form/document.h"
#include "berg/user/form/impact.h"
#include "berg/user/simple/frame_window.h"
#include "berg/user/simple/child_frame.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"

namespace
{
   class form_factory_user : public ::berg::user
   {
   public:
      int m_iHtmlInitializations = 0;
      void initialize_html() override { ++m_iHtmlInitializations; }
   };
}

int main()
{
   ::platform::system testSystem;
   ::pointer < ::platform::application > papplication(allocate_t{});
   papplication->m_papplication = papplication;
   ::pointer < form_factory_user > puser(allocate_t{});
   puser->m_papplication = papplication;

   // create_form requests this exact id; it must not fall through to not_implemented.
   auto pform = puser->create_impact_system("form");
   if (!pform || puser->m_iHtmlInitializations != 1) return 1;
   if (pform->m_typeDocument.name() != ::type < ::form_document >().name()) return 2;
   if (pform->m_typeImpact.name() != ::type < ::user::form_impact >().name()) return 3;
   if (pform->m_typeFrame.name() != ::type < ::simple_frame_window >().name()) return 4;

   auto pchild = puser->create_impact_system("child_form");
   if (!pchild || puser->m_iHtmlInitializations != 2) return 5;
   if (pchild->m_typeFrame.name() != ::type < ::simple_child_frame >().name()) return 6;
   return 0;
}
