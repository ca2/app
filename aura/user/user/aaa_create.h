#pragma once


namespace user
{


   class CLASS_DECL_AURA create :
      virtual public object
   {
   public:



      //bool                           m_bAutoWindowFrame;
      boolean                          m_bWindowFrame;
      ::type_atom                      m_typeatomNewImpact;
      //::user::document *             m_pdocumentCurrent;
      ::object *                       m_pdocumentCurrent;
      ::user::prototype *              m_puiNew;

      // multiple document interface children
      //::user::impact_system *          m_ptemplateNewDocument;
      ::object *                       m_ptemplateNewDocument;

      // original impact/frame
      ::user::prototype *              m_puiLastImpact;
      ::user::prototype *              m_puiCurrentFrame;
      //::pointer<impact_data>        m_pimpactdata;
      ::pointer<::matter>             m_pimpactdata;


      create();
      virtual ~create();


   };


} // namespace user


