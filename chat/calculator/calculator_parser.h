#pragma once


namespace calculator
{


   class CLASS_DECL_CA2_MATH parser :
      virtual public ::object
   {
   public:


      scanner                          m_scanner;
      __pointer_array(::calculator::element)       m_elementa;


      parser(::layered * pobjectContext);
      virtual ~parser();


      ::calculator::element * parse(const char * psz);

      ::calculator::element * expr(::calculator::element * pelement1);
      ::calculator::element * term(::calculator::element * pelement1);
      ::calculator::element * factor();

      void error(const char * pszMessage);
      void syntax_error(const char * pszMessage);
      void expect(char ch);


      ::calculator::element *new_node();
      i32 precedence(token::e_type next, token::e_type current);
      double parse(::calculator::element *current_node);
      double node_traverse(::calculator::element *current_node, double value);
      double apply_traverse_operator(::calculator::element *current_node, double total);
      double apply_operator(::calculator::element *current_node, double total, double m_etype);


   };


} // namespace calculator





