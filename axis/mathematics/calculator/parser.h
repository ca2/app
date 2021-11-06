#pragma once


namespace calculator
{


   class CLASS_DECL_AXIS parser :
      virtual public ::object
   {
   public:


      scanner                                      m_scanner;
      __pointer_array(::calculator::element)       m_elementa;


      parser();
      virtual ~parser();


      ::calculator::element * parse(const ::string & psz);

      ::calculator::element * expr(::calculator::element* pelement1);
      ::calculator::element * term(::calculator::element* pelement1);
      ::calculator::element * factor();

      void error(const ::string & pszMessage);
      void syntax_error(const ::string & pszMessage);
      void expect(char ch);


      ::calculator::element*new_node();
      i32 precedence(token::enum_type next, token::enum_type current);
      double parse(::calculator::element*current_node);
      double node_traverse(::calculator::element*current_node, double value);
      double apply_traverse_operator(::calculator::element*current_node, double total);
      double apply_operator(::calculator::element*current_node, double total, double m_etype);


   };


} // namespace calculator





