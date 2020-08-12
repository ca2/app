#pragma once


namespace html
{


   class file;


} // namespace html


class CLASS_DECL_CA2_TIME calendar :
   virtual public calendar_interface
{
public:


   ::point          m_point;
   ::size           m_size;
   i32        m_iColWidth;
   i32        m_iLineHeight;



   

   calendar(::object * pobject);


   virtual void _001GetHtml(__pointer(::html::file) pfile);






};



