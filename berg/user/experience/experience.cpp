#include "framework.h"
#include "experience.h"
#include "acme/platform/system.h"
#include "berg/platform/session.h"


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


   // ::berg::application * experience::get_app()
   // {
   //
   //    auto papplication = application();
   //
   //    return ::is_set(papplication) ? papplication : nullptr;
   //
   // }
   //
   //
   // ::berg::session * experience::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return ::is_set(pacmesession) ? pacmesession : nullptr;
   //
   // }
   //
   //
   // ::berg::system * experience::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }
   //
   //
   // ::base::user * experience::user()
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


   ::pointer < ::experience::frame > experience::frame_experience(const ::scoped_string & scopedstrFrameSchema)
   {

      __UNREFERENCED_PARAMETER(scopedstrFrameSchema);

      return nullptr;

   }


} // namespace experience



