#pragma once



class CLASS_DECL_AURA draw_text :
   virtual public text_out
{
public:


   ::rectangle_i32            m_rectangle;
   ::e_align                  m_ealign;
   ::e_draw_text              m_edrawtext;


   draw_text() {  }


};



