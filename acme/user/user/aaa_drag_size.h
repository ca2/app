// From drag_move by camilo on 2022-04-01 11:39 AM <3ThomasBorregaardSørensen
#pragma once


namespace user
{


   class CLASS_DECL_ACME drag_size :
      virtual public ::matter
   {
   public:


      bool                       m_bLButtonDown;
      ::point_i32                m_pointLButtonDown;
      ::size_i32                 m_sizeLButtonDownOffset;

      bool                       m_bDrag;

      
      drag_size();
      ~drag_size() override;


   };


   class CLASS_DECL_ACME drag_size_client :
      virtual public ::object
   {
   public:


      __pointer(drag_size)       m_pdragsize;


      drag_size_client();
      ~drag_size_client() override;


      virtual void enable_drag_size();


   };


} // namespace user



