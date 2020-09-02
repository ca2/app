#pragma once


namespace datetime
{

   class element;

   class CLASS_DECL_CA2_TIME parser :
      virtual public ::object
   {
   public:

      
      scanner                       m_scanner;
      spa(::datetime::element)      m_elementa;


      parser(::aura::application * papp, ::aura::str_context * pcontext);
      virtual ~parser();


      ::datetime::element * parse(const char * psz);

      ::datetime::element * expr(::datetime::element * pelement1);
      ::datetime::element * term(::datetime::element * pelement1);
      ::datetime::element * factor();


      void error(const char * pszMessage);
      void syntax_error(const char * pszMessage);
      void expect(char ch);


      ::datetime::element *new_node();
      int32_t precedence(token::e_type next, token::e_type current);
      double parse(::datetime::element *current_node);
      double node_traverse(::datetime::element *current_node, double value);
      double apply_traverse_operator(::datetime::element *current_node, double total);
      double apply_operator(::datetime::element *current_node, double total, double m_etype);

      
   };



} // namespace datetime