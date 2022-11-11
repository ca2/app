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
      
      return m_pcontext ? m_pcontext->m_pbaseapplication : nullptr; 
   
   }


   ::base::session * experience::get_session()
   {
      
      return m_pcontext ? m_pcontext->m_pbasesession : nullptr; 
   
   }


   ::base::system * experience::get_system()
   {
      
      return acmesystem() ? acmesystem()->m_pbasesystem : nullptr; 
   
   }


   ::base::user * experience::user()
   {
      
      return get_session() ? get_session()->user() : nullptr; 
   
   }


   void experience::update()
   {

   }


   void experience::get_frame_list(string_array & stra)
   {

      __UNREFERENCED_PARAMETER(stra);

   }


   ::experience::frame * experience::frame_experience(const ::string & strFrameSchema)
   {

      __UNREFERENCED_PARAMETER(strFrameSchema);

      return nullptr;

   }


} // namespace experience



