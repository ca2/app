#pragma once


namespace calculator
{


   class CLASS_DECL_CA2_MATH parser :
      virtual public ::object
   {
   public:


      scanner                          m_scanner;
      __pointer_array(::calculator::matter)       m_elementa;


      parser(::object * pobject);
      virtual ~parser();


      ::calculator::matter * parse(const ::string & psz);

      ::calculator::matter * expr(::calculator::matter * pelement1);
      ::calculator::matter * term(::calculator::matter * pelement1);
      ::calculator::matter * factor();

      void error(const ::string & pszMessage);
      void syntax_error(const ::string & pszMessage);
      void expect(char ch);


      ::calculator::matter *new_node();
      i32 precedence(token::enum_type next, token::enum_type current);
      double parse(::calculator::matter *current_node);
      double node_traverse(::calculator::matter *current_node, double value);
      double apply_traverse_operator(::calculator::matter *current_node, double total);
      double apply_operator(::calculator::matter *current_node, double total, double m_etype);


   };


} // namespace calculator





