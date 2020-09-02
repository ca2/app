#pragma once


namespace html
{


   class file;


} // namespace html


class CLASS_DECL_CA2_TIME calendar :
   virtual public calendar_interface
{
public:


   point          m_point;
   size           m_size;
   int32_t        m_iColWidth;
   int32_t        m_iLineHeight;



   

   calendar(::aura::application * papp);


   virtual void _001GetHtml(sp(::html::file) pfile);






};



