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


   ::base::application * experience::get_app()
   {

      auto pacmeapplication = acmeapplication();
      
      return ::is_set(pacmeapplication) ? pacmeapplication->m_pbaseapplication : nullptr;
   
   }


   ::base::session * experience::get_session()
   {
      
      auto pacmesession = acmesession();

      return ::is_set(pacmesession) ? pacmesession->m_pbasesession : nullptr;

   }


   ::base::system * experience::get_system()
   {
      
      auto pacmesystem = acmesystem();

      return ::is_set(pacmesystem) ? pacmesystem->m_pbasesystem : nullptr;

   }


   ::base::user * experience::user()
   {

      auto psession = get_session();
      
      return ::is_set(psession) ? psession->user() : nullptr; 
   
   }


   void experience::update()
   {

   }


   void experience::get_frame_list(string_array & stra)
   {

      UNREFERENCED_PARAMETER(stra);

   }


   ::experience::frame * experience::frame_experience(const ::string & strFrameSchema)
   {

      UNREFERENCED_PARAMETER(strFrameSchema);

      return nullptr;

   }


} // namespace experience



