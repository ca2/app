#include "framework.h"
#include "experience.h"
#include "base/platform/session.h"


namespace experience
{


   experience::experience()
   {

   }


   experience::~experience()
   {

   }


   ::base::application * experience::get_app() const
   {
      
      return m_pcontext ? m_pcontext->m_pbaseapplication : nullptr; 
   
   }


   ::base::session * experience::get_session() const 
   {
      
      return m_pcontext ? m_pcontext->m_pbasesession : nullptr; 
   
   }


   ::base::system * experience::get_system() const 
   {
      
      return m_psystem ? m_psystem->m_pbasesystem : nullptr; 
   
   }


   ::base::user * experience::user() const 
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



