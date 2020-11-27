#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA font_enumeration :
      virtual public ::object
   {
   public:


      int                                             m_iUpdateId;
      __pointer(::draw2d::font_enum_item_array)       m_pitema;
      bool                                            m_bUpdating;


      font_enumeration();
      virtual ~font_enumeration();


      virtual ::estatus initialize(::layered* pobjectContext) override;


      virtual void on_subject(::promise::subject * psubject) override;
      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;


      virtual void check_need_update(::promise::subject * psubject);
      virtual bool update(::promise::subject * psubject);


      //bool similar_font(char sz[256], const char* psz);
      //void default_font_name(char sz[256]);
      //double font_similarity(const char* pszSystem, const char* pszUser);


      virtual __pointer(::draw2d::font_enum_item) similar_font(const char* psz);
      virtual void adapt_font_name(string & str);
      virtual bool has_font_name(const string& str);

      //void adapt_font_name(string& str)
      //{

      //   char sz[256];

      //   if (!similar_font(sz, str))
      //   {

      //      default_font_name(sz);

      //   }

      //   str = sz;

      //}


      //double font_similarity(const char* pszSystem, const char* pszUser)
      //{

      //   if (!strcmp(pszSystem, pszUser))
      //   {

      //      return 1.0;

      //   }

      //   return 0.0;

      //}
   };


} // namespace draw2d



