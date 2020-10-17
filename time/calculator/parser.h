#pragma once


namespace datetime
{

   class matter;

   class CLASS_DECL_CA2_TIME parser :
      virtual public ::object
   {
   public:

      
      scanner                                   m_scanner;
      __pointer_array(::datetime::matter)      m_elementa;


      parser(const ::apex::str_context * pcontext);
      virtual ~parser();


      ::datetime::matter * parse(const char * psz);

      ::datetime::matter * expr(::datetime::matter * pelement1);
      ::datetime::matter * term(::datetime::matter * pelement1);
      ::datetime::matter * factor();


      void error(const char * pszMessage);
      void syntax_error(const char * pszMessage);
      void expect(char ch);


      ::datetime::matter *new_node();
      int32_t precedence(enum_token next, enum_token current);
      ::datetime::value parse(::datetime::matter *current_node);
      ::datetime::value node_traverse(::datetime::matter *current_node, double value);
      ::datetime::value apply_traverse_operator(::datetime::matter *current_node, double total);
      ::datetime::value apply_operator(::datetime::matter *current_node, double total, double m_etype);

      
   };



} // namespace datetime