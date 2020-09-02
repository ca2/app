#pragma once


namespace datetime
{

   #define INITIALIZE_TABLE(table, function) if(table[0] == 0) function(table)

   /*
   var:
   a(ad)*
   a = a-z, A-Z, _
   d = 0-9
   operators:
   + -
   * /
   =
   numbers:
   0-9
   */


   
   CLASS_DECL_CA2_TIME bool check_end_expression(const char * input, const char * & scanner);
   CLASS_DECL_CA2_TIME bool check_expression_separator(const char * input, const char * & scanner);
   CLASS_DECL_CA2_TIME string check_unit(::aura::str_context * pcontext, const char * input, const char * & scanner);
   CLASS_DECL_CA2_TIME string check_month(const char * input, const char * & scanner);
   CLASS_DECL_CA2_TIME string check_lang_date(const char * input, const char * & scanner);
   CLASS_DECL_CA2_TIME string check_natural(const char * input, const char * & scanner);
   CLASS_DECL_CA2_TIME string check_lang_offset(const char * input, const char * & scanner);
   CLASS_DECL_CA2_TIME string check_natural_separator(const char * input, const char * & scanner);
   CLASS_DECL_CA2_TIME string check_date(const char * input, const char * & scanner);
   CLASS_DECL_CA2_TIME string check_offset(::aura::str_context * pcontext, const char * input, const char * & scanner);
   CLASS_DECL_CA2_TIME string consume_date_expression(::aura::str_context * pcontext, const char * & input);


   class CLASS_DECL_CA2_TIME scanner :
      virtual public ::object
   {
   public:
      
      
      const char *            input;
      const char *            next_input;

      class token *           m_ptoken;
      ::aura::str_context *   m_pstrcontext;


      scanner(::aura::application * papp, ::aura::str_context * pstrcontext);
      virtual ~scanner();

      void initialize(const char * psz);
      void peek();
      void next();
      token * look_ahead();

   };


} // namespace calculator