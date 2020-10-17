#pragma once


namespace calculator
{


   class CLASS_DECL_AXIS element:
      virtual public ::matter
   {
   public:


      element *      m_pparent;

      __pointer(token)      m_ptoken;
      element *      m_pelement1;
      element *      m_pelement2;
      element *      m_pelement3;


      element();
      virtual ~element();


      class value get_value();
      string get_expression();

   };


} // namespace calculator














