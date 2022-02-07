// Created by camilo on 2021-01-22 06:11 AM <3ThomasBorregaardSørensen
#include "framework.h"
#include "drag_move.h"


namespace user
{


   drag_move::drag_move()
   {

      m_bDrag = false;

      m_bLButtonDown = false;

   }


   drag_move::~drag_move()
   {


   }
      
      
   drag_move_client::drag_move_client()
   {


   }


   drag_move_client::~drag_move_client()
   {


   }


   void drag_move_client::enable_drag_move()
   {

      __construct_new(m_pdragmove);

   }


} // namespace user



