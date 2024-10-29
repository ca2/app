#include "framework.h"
#include "experience.h"
#include "acme/platform/system.h"
#include "base/platform/session.h"


namespace experience
{


   experience::experience()
   {

   }


   experience::~experience()
   {

   }


   void experience::destroy()
   {

      m_pfactory.release();

      ::object::destroy();

   }


   // ::base::application * experience::get_app()
   // {
   //
   //    auto papplication = application();
   //
   //    return ::is_set(papplication) ? papplication : nullptr;
   //
   // }
   //
   //
   // ::base::session * experience::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return ::is_set(pacmesession) ? pacmesession->m_pbasesession : nullptr;
   //
   // }
   //
   //
   // ::base::system * experience::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }
   //
   //
   // ::base::user * experience::baseuser()
   // {
   //
   //
   //
   //    return ::is_set(psession) ? user() : nullptr;
   //
   // }


   void experience::update()
   {

   }


   void experience::get_frame_list(string_array & stra)
   {

      __UNREFERENCED_PARAMETER(stra);

   }


   ::pointer < ::experience::frame > experience::frame_experience(const ::string & strFrameSchema)
   {

      __UNREFERENCED_PARAMETER(strFrameSchema);

      return nullptr;

   }


} // namespace experience



