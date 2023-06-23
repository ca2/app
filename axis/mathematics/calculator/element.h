#pragma once


#include "acme/primitive/primitive/particle.h"


namespace calculator
{


   class token;


   class CLASS_DECL_AXIS element:
      virtual public ::particle
   {
   public:


      element *      m_pparent;

      ::pointer<token>      m_ptoken;
      element *      m_pelement1;
      element *      m_pelement2;
      element *      m_pelement3;


      element();
      ~element() override;


      class result get_result();
      string get_expression();


   };


} // namespace calculator














