// Created by camilo on 2021-01-22 06:11 AM <3ThomasBorregaardSørensen
#pragma once


namespace user
{

   class CLASS_DECL_ACME drag_move :
      virtual public ::matter
   {
   public:

      bool                       m_bLButtonDown;
      ::point_i32                m_pointLButtonDown;
      ::size_i32                 m_sizeLButtonDownOffset;

      bool                       m_bDrag;

      
      drag_move();
      ~drag_move() override;


   };


   class CLASS_DECL_ACME drag_move_client :
      virtual public ::object
   {
   public:


      __pointer(drag_move)       m_pdragmove;


      drag_move_client();
      ~drag_move_client() override;


      virtual void enable_drag_move();


   };


} // namespace user



