#pragma once


namespace user
{


   class CLASS_DECL_AURA create :
      virtual public object
   {
   public:



      bool                             m_bAutoWindowFrame;
      bool                             m_bWindowFrame;
      ::type                           m_typeNewView;
      //::user::document *             m_pdocumentCurrent;
      ::object *                       m_pdocumentCurrent;
      ::user::primitive *              m_puiNew;

      // multiple document interface children
      //::user::impact_system *          m_ptemplateNewDocument;
      ::object *                       m_ptemplateNewDocument;

      // original view/frame
      ::user::primitive *              m_puiLastView;
      ::user::primitive *              m_puiCurrentFrame;
      //__pointer(impact_data)         m_pimpactdata;
      __pointer(::generic_object)      m_pimpactdata;


      create();
      virtual ~create();


   };


} // namespace user


