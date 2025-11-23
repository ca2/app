#pragma once


namespace user
{


   class CLASS_DECL_AURA create :
      virtual public object
   {
   public:



      //bool                           m_bAutoWindowFrame;
      boolean                          m_bWindowFrame;
      ::type                      m_typeNewImpact;
      //::user::document *             m_pdocumentCurrent;
      ::object *                       m_pdocumentCurrent;
      ::user::interaction_base *              m_puiNew;

      // multiple document interface children
      //::user::impact_system *          m_ptemplateNewDocument;
      ::object *                       m_ptemplateNewDocument;

      // original impact/frame
      ::user::interaction_base *              m_puiLastImpact;
      ::user::interaction_base *              m_puiCurrentFrame;
      //::pointer<impact_data>        m_pimpactdata;
      ::pointer<::matter>             m_pimpactdata;


      create();
      virtual ~create();


   };


} // namespace user


