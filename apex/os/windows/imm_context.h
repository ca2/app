#pragma once


#ifdef WINDOWS_DESKTOP


class CLASS_DECL_APEX imm_context
{
public:


   HIMC                                m_himc;
   __pointer(::user::interaction)      m_pinteraction;


   imm_context(::user::interaction * pinteraction);
   ~imm_context();


   operator HIMC () const { return m_himc; }

   bool close();

   bool is_opened() const;

   bool close_candidate(index iIndex = 0);

   string get_string(int iStr = GCS_COMPSTR);

   string _get_candidate(int iList);

   string get_candidate();


};


#endif



