#pragma once


//#include "acme/prototype/prototype/matter.h"


namespace user
{


   class place_holder;


   class CLASS_DECL_BASE impact_data :
      virtual public ::matter
   {
   public:


      huge_integer                            m_iId;
      ::collection::index                          m_iIndex;
      ::pointer<interaction>          m_puserinteraction;
      ::pointer<place_holder>         m_pplaceholder;
      ::pointer<document>             m_pdocument;
      atom                             m_atomSplit;
      bool                             m_bTabSplitSwap;
      int                              m_iExtendOnParent;
      e_flag                           m_eflag;
      ::string                         m_strTitle;
      void *                           m_pimpactdata;
      bool                             m_bOk;

      
      impact_data();
      impact_data(const ::atom & atom);
      virtual ~impact_data();

      void impact_data_common_construct();


   };



   class CLASS_DECL_BASE impact_data_map :
      public atom_map < ::pointer<impact_data >>
   {
   public:


   };



} // namespace user


CLASS_DECL_BASE ::user::impact_data * __impact_data(::user::system * pusersystem);


CLASS_DECL_BASE ::user::impact_data * __impact_data(::message::create * pmessagecreate);



