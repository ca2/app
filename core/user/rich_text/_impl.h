#pragma once

namespace user
{


   namespace rich_text
   {

      
      inline ::pointer<format> span::fork_format()
      { 
         
      
         return __new(class format(*m_pformat));
      
      }




   }  // namespace rich_text


} // namespace user

