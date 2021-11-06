#pragma once


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE line :
         virtual public __pointer_array(box)
      {
      public:


         double   m_dLeft;
         double   m_dLeftDevice;

         double   m_xOffset;


         line();
         virtual ~line();


      };



   } // namespace rich_text


} // namespace user



