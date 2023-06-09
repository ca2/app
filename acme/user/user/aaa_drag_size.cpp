// From drag_move by camilo on 2022-04-01 11:43 AM <3ThomasBorregaardSorensen
#include "framework.h"
#include "drag_size.h"


namespace user
{


   drag_size::drag_size()
   {

      m_bDrag = false;

      m_bLButtonDown = false;

   }


   drag_size::~drag_size()
   {


   }
      
      
   drag_size_client::drag_size_client()
   {


   }


   drag_size_client::~drag_size_client()
   {


   }


   void drag_size_client::enable_drag_size()
   {

      __construct_new(m_pdragsize);

   }


} // namespace user



