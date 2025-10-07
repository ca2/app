#pragma once


namespace regular_expression_pcre2
{


   class CLASS_DECL_AXIS context :
      virtual public ::regular_expression::context
   {
   public:


      pcre_context_impl * m_pimpl;


      context();
      virtual ~context();


      //static ::pointer<pcre_context>

      //create_context(int iSizeData);

      virtual ::regular_expression_pointer compile(const ::scoped_string & scopedstr) override;


//      protected:
//
//
//      pcre_context(::particle * pparticle);


   };


} // namespace regular_expression_pcre2



