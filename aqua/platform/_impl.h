#pragma once


namespace aqua
{


   inline ::aqua::system* application::get_system()
   {
      
      return dynamic_cast <::aqua::system*> (m_psystem); 
   
   }


} // namespace aqua