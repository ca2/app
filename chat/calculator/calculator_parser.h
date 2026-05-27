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
      void expect(::i8 ch);


      ::calculator::matter *new_node();
      ::i32 precedence(token::enum_type next, token::enum_type current);
      ::f64 parse(::calculator::matter *current_node);
      ::f64 node_traverse(::calculator::matter *current_node, ::f64 value);
      ::f64 apply_traverse_operator(::calculator::matter *current_node, ::f64 total);
      ::f64 apply_operator(::calculator::matter *current_node, ::f64 total, ::f64 m_etype);


   };


} // namespace calculator





