#pragma once


class CLASS_DECL_BASE impact_update :
   virtual public ::update
{
public:


   bool                                m_bOk;
   ::user::control_event *             m_pusercontrolevent;
   ::user::interaction *               m_puserinteraction;
   ::user::enum_key                       m_ekey;
   bool                                m_bEnterKeyPressed;
   ::payload                                 m_payloadFile;
   e_impact                            m_epaneimpact;
   string                              m_strImpact;
   __pointer_array(::user::impact)     m_viewaAttachable;
   __pointer(::user::impact)           m_pviewTopic;
   __pointer(::user::document)         m_pdocTopic;
   bool                                m_bFullScreen;
   __pointer(::data::data)             m_pdataTopic;
   ::i64                               m_iTime;

   
   impact_update();
   virtual ~impact_update();


};



