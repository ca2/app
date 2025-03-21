// From drag_move by camilo on 2022-04-01 11:39 AM <3ThomasBorregaardSorensen
#pragma once


namespace user
{


   class CLASS_DECL_ACME drag_size :
      virtual public ::matter
   {
   public:


      bool                       m_bLButtonDown;
      ::int_point                m_pointLButtonDown;
      ::int_size                 m_sizeLButtonDownOffset;

      bool                       m_bDrag;

      
      drag_size();
      ~drag_size() override;


   };


   class CLASS_DECL_ACME drag_size_client :
      virtual public ::object
   {
   public:


      ::pointer<drag_size>      m_pdragsize;


      drag_size_client();
      ~drag_size_client() override;


      virtual void enable_drag_size();


   };


} // namespace user



