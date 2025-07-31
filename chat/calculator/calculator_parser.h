#pragma once


namespace calculator
{


   class CLASS_DECL_CA2_MATH parser :
      virtual public ::object
   {
   public:


      scanner                          m_scanner;
      pointer_array < ::calculator::matter >       m_elementa;


      parser(::particle * pparticle);
      virtual ~parser();


      ::calculator::matter * parse(const ::scoped_string & scopedstr);

      ::calculator::matter * expr(::calculator::matter * pelement1);
      ::calculator::matter * term(::calculator::matter * pelement1);
      ::calculator::matter * factor();

      void error(const ::scoped_string & scopedstrMessage);
      void syntax_error(const ::scoped_string & scopedstrMessage);
      void expect(char ch);


      ::calculator::matter *new_node();
      int precedence(token::enum_type next, token::enum_type current);
      double parse(::calculator::matter *current_node);
      double node_traverse(::calculator::matter *current_node, double value);
      double apply_traverse_operator(::calculator::matter *current_node, double total);
      double apply_operator(::calculator::matter *current_node, double total, double m_etype);


   };


} // namespace calculator





