#pragma once


namespace datetime
{


   class CLASS_DECL_CA2_TIME element :
      virtual public ::generic
   {
   public:

      element();
      ~element();

      token *     m_ptoken;
      element *   m_pparent;
      element *   m_pelement1;
      element *   m_pelement2;
      element *   m_pelement3;


      ::datetime::value get_value(const ::apex::str_context * pcontext, int32_t & iPath, int32_t & iPathCount) const;
      string get_expression(const ::apex::str_context * pcontext, int32_t & iPath, int32_t & iPathCount) const;


   };


} // namespace calculator



