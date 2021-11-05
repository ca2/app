#pragma once


namespace calculator
{


   class CLASS_DECL_CA2_MATH matter:
      virtual public ::object
   {
   public:


      matter();
      ~matter();


      token *     m_ptoken;
      matter *   m_pparent;
      matter *   m_pelement1;
      matter *   m_pelement2;
      matter *   m_pelement3;


      value get_value();
      string get_expression();

   };


} // namespace calculator














