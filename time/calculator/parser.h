#pragma once


namespace datetime
{

   class element;

   class CLASS_DECL_CA2_TIME parser :
      virtual public ::object
   {
   public:

      
      scanner                                   m_scanner;
      __pointer_array(::datetime::element)      m_elementa;


      parser(const ::apex::str_context * pcontext);
      virtual ~parser();


      ::datetime::element * parse(const char * psz);

      ::datetime::element * expr(::datetime::element * pelement1);
      ::datetime::element * term(::datetime::element * pelement1);
      ::datetime::element * factor();


      void error(const char * pszMessage);
      void syntax_error(const char * pszMessage);
      void expect(char ch);


      ::datetime::element *new_node();
      int32_t precedence(enum_token next, enum_token current);
      ::datetime::result parse(::datetime::element *current_node);
      ::datetime::result node_traverse(::datetime::element *current_node, double value);
      ::datetime::result apply_traverse_operator(::datetime::element *current_node, double total);
      ::datetime::result apply_operator(::datetime::element *current_node, double total, double m_etype);

      
   };



} // namespace datetime