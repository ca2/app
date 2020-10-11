#pragma once



class CLASS_DECL_AURA draw_text :
   virtual public text_out
{
public:


   ::rect                        m_rect;
   ::e_align                     m_ealign;
   ::e_draw_text                 m_edrawtext;


   draw_text() {  }


};



