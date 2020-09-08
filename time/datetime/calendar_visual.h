#pragma once


namespace html
{


   class file;


} // namespace html


namespace datetime
{


   namespace calendar
   {


      class CLASS_DECL_CA2_TIME visual :
         virtual public calendar
      {
      public:


         point          m_point;
         size           m_size;
         int32_t        m_iColWidth;
         int32_t        m_iLineHeight;


         visual();
         virtual ~visual();


         virtual ::estatus initialize(::object* pobjectContext) override;


         virtual void _001GetHtml(::html::file* pfile);






      };


   } // namespace calendar


} // namespace datetime



