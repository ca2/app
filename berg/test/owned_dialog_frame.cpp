#include "berg/platform.h"
#include "berg/user/user/impact_system.h"
#include "berg/user/user/multiple_document_template.h"
#include "berg/user/user/impact.h"
#include "berg/user/user/frame_window.h"
#include "aura/user/user/interaction_array.h"
#include "aura/user/user/system.h"
#include "acme/handler/request.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/factory.h"

namespace
{
   class test_frame : public ::user::frame_window
   {
   public:
      void initialize(::particle * context) override { m_papplication = context->m_papplication; }
      ::user::interaction * m_ownerAtCreation = nullptr;
      bool m_bSatelliteAtCreation = false;
      bool LoadFrame(const ::scoped_string &, ::u32, ::user::interaction *, ::user::system *) override
      {
         m_ownerAtCreation = owner_interaction();
         m_bSatelliteAtCreation = m_ewindowflag.has(e_window_flag_satellite_window);
         return true; // Record policy at the native-creation boundary without creating a window.
      }
   };

}

int main()
{
   ::platform::system runtime;
   ::pointer < ::platform::application > app(allocate_t{});
   app->m_papplication = app;
   ::pointer < test_frame > owner(allocate_t{});
   owner->m_papplication = app;
   app->factory()->add_factory_item<test_frame, ::user::frame_window>();
   ::pointer < ::user::multiple_document_template > system(allocate_t{}, "test/dialog", ::type<::user::document>(),
      ::type<::user::frame_window>(), ::type<::user::impact>());
   system->m_papplication = app;
   ::pointer < ::request > request(allocate_t{});
   request->m_papplication = app;
   request->m_payloadArguments["dialog_owner"] = owner;
   auto frame = system->create_new_frame(nullptr, nullptr, request);
   ::cast < test_frame > created = frame;
   if (!created || created->m_ownerAtCreation != owner.get()
      || !created->m_bSatelliteAtCreation || frame->m_bAppWindow) return 1;
   if (owner->m_puserinteractionpointeraOwned) owner->m_puserinteractionpointeraOwned->erase_interaction(frame);
   ::cast < ::user::system > state = request->m_pmatterUserPayload;
   state->m_prequest.release();
   request->m_pmatterUserPayload.release();

   request->m_payloadArguments["dialog_owner"].unset();
   frame = system->create_new_frame(nullptr, nullptr, request);
   created = frame;
   if (!created || created->m_ownerAtCreation || created->m_bSatelliteAtCreation) return 2;
   state = request->m_pmatterUserPayload;
   state->m_prequest.release();
   request->m_pmatterUserPayload.release();
   return 0;
}
