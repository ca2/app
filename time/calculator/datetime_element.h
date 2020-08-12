#pragma once


namespace datetime
{


   class CLASS_DECL_CA2_TIME element :
      virtual public ::object
   {
   public:

      element();
      ~element();

      token *     m_ptoken;
      element *   m_pparent;
      element *   m_pelement1;
      element *   m_pelement2;
      element *   m_pelement3;


      ::datetime::value get_value(::object * pobject, const ::aura::str_context * pcontext, i32 & iPath, i32 & iPathCount) const;
      string get_expression(::object * pobject, const ::aura::str_context * pcontext, i32 & iPath, i32 & iPathCount) const;





   };


} // namespace calculator



