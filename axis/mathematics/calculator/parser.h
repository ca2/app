#pragma once


//#include "acme/prototype/collection/pointer_array.h"
#include "element.h"
#include "scanner.h"
#include "token.h"


namespace calculator
{


   class CLASS_DECL_AXIS parser :
      virtual public ::particle
   {
   public:


      scanner                                         m_scanner;
      pointer_array < ::calculator::element >         m_elementa;


      parser();
      ~parser() override;


      ::calculator::element * parse(const ::scoped_string & scopedstr);

      ::calculator::element * expr(::calculator::element* pelement1);
      ::calculator::element * term(::calculator::element* pelement1);
      ::calculator::element * factor();

      void error(const ::scoped_string & scopedstrMessage);
      void syntax_error(const ::scoped_string & scopedstrMessage);
      void expect(::i8 ch);


      ::calculator::element*new_node();
      ::i32 precedence(token::enum_type next, token::enum_type current);
      ::f64 parse(::calculator::element*current_node);
      ::f64 node_traverse(::calculator::element*current_node, ::f64 value);
      ::f64 apply_traverse_operator(::calculator::element*current_node, ::f64 total);
      ::f64 apply_operator(::calculator::element*current_node, ::f64 total, ::f64 m_etype);


   };


} // namespace calculator





