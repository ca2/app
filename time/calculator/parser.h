#pragma once


//#include "acme/prototype/collection/pointer_array.h"
#include "acme/prototype/datetime/result.h"

//#include "acme/prototype/prototype/pointer.h"


namespace datetime
{

   
   class element;


   class CLASS_DECL_CA2_TIME parser :
      virtual public ::particle
   {
   public:

      
      ::pointer<scanner>                       m_pscanner;
      pointer_array < ::datetime::element >      m_elementa;


      parser();
      ~parser() override;


      virtual void initialize_datetime_parse(::text::context * pcontext);


      ::datetime::element * parse(const ::scoped_string & scopedstr);

      ::datetime::element * expr(::datetime::element * pelement1);
      ::datetime::element * term(::datetime::element * pelement1);
      ::datetime::element * factor();


      void error(const ::scoped_string & scopedstrMessage);
      void syntax_error(const ::scoped_string & scopedstrMessage);
      void expect(char ch);


      ::datetime::element *new_node();
      int32_t precedence(enum_token next, enum_token current);
      ::datetime::result parse(::datetime::element *current_node);
      ::datetime::result node_traverse(::datetime::element *current_node, double value);
      ::datetime::result apply_traverse_operator(::datetime::element *current_node, double total);
      ::datetime::result apply_operator(::datetime::element *current_node, double total, double m_etype);

      
   };



} // namespace datetime
