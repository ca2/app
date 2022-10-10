#pragma once


namespace calculator
{


   class CLASS_DECL_AXIS element:
      virtual public ::matter
   {
   public:


      element *      m_pparent;

      ::pointer<token>      m_ptoken;
      element *      m_pelement1;
      element *      m_pelement2;
      element *      m_pelement3;


      element();
      virtual ~element();


      class result get_result();
      string get_expression();

   };


} // namespace calculator














