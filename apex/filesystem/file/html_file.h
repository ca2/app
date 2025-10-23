#pragma once


class CLASS_DECL_APEX html_file:
   virtual public ::particle
{
public:


   string                              m_strOptions;
   string                              m_strStyle;
   ::pointer<::text::context>          m_ptextcontext;


   html_file();
   ~html_file() override;


   virtual const ::text::context * textcontext();

   virtual void print(const ::scoped_string & scopedstr);

   virtual void raw_print(const ::scoped_string & scopedstr);

   void trace(void *,const ::scoped_string & scopedstr);

   template<typename... Args>
   void print_format(::std::format_string<Args...> fmt, Args&&... args)
   {

      auto s = std::format(fmt, std::forward<Args>(args)...);

      this->print({ s.c_str(), (character_count) s.size() });

   }


   virtual void dprint(const ::scoped_string & scopedstr);


};



