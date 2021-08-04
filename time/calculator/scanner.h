#pragma once


namespace datetime
{

   #define INITIALIZE_TABLE(table, function) if(table[0] == 0) function(table)

   /*
   ::payload:
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


   
   CLASS_DECL_CA2_TIME bool check_end_expression(const ::string & input, const char * & scanner);
   CLASS_DECL_CA2_TIME bool check_expression_separator(const ::string & input, const char * & scanner);
   CLASS_DECL_CA2_TIME string check_unit(const ::text::context * pcontext, const ::string & input, const char * & scanner);
   CLASS_DECL_CA2_TIME string check_month(const ::string & input, const char * & scanner);
   CLASS_DECL_CA2_TIME string check_lang_date(const ::string & input, const char * & scanner);
   CLASS_DECL_CA2_TIME string check_natural(const ::string & input, const char * & scanner);
   CLASS_DECL_CA2_TIME string check_lang_offset(const ::string & input, const char * & scanner);
   CLASS_DECL_CA2_TIME string check_natural_separator(const ::string & input, const char * & scanner);
   CLASS_DECL_CA2_TIME string check_date(const ::string & input, const char * & scanner);
   CLASS_DECL_CA2_TIME string check_offset(const ::text::context * pcontext, const ::string & input, const char * & scanner);
   CLASS_DECL_CA2_TIME string consume_date_expression(const ::text::context * pcontext, const char * & input);


   class CLASS_DECL_CA2_TIME scanner :
      virtual public ::object
   {
   public:
      
      
      const char *                  input;
      const char *                  next_input;

      class token *                 m_ptoken;
      const ::text::context *   m_ptextcontext;


      scanner();
      virtual ~scanner();


      virtual ::e_status initialize_datetime_scanner(::text::context* ptextcontext);


      void initialize(const ::string & psz);
      void peek();
      void next();
      token * look_ahead();

   };


} // namespace datetime



