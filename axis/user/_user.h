#pragma once


#include "aura/user/user/_user.h"


namespace user
{


   using style_pointer = __pointer(style);


} // namespace user


//#include "still.h"

//#include "button.h"


//#include "check_box.h"


#include "combo_box.h"
#include "list_box.h"

#include "slider.h"


#include "user.h"




namespace axis
{


   inline ::axis::user* session::user() 
   {
      
      return m_puser ? m_puser.cast < ::axis::user >() : nullptr; 
   
   }


} // namespace axis


