#pragma once


namespace write_text
{


   class CLASS_DECL_AURA font_enumeration :
      virtual public ::manager
   {
   public:


      bool                                            m_bRaster : 1;
      bool                                            m_bTrueType : 1;
      bool                                            m_bOther : 1;
      int                                             m_iUpdateId;
      __pointer(font_enumeration_item_array)          m_pfontenumerationitema;
      bool                                            m_bUpdating;
      manual_reset_event                              m_eventReady;


      font_enumeration();
      virtual ~font_enumeration();


      virtual void initialize(::object * pobject) override;


      //void signal(::signal * psignal) override;
      void handle(::subject * psubject, ::context * pcontext) override;


      virtual void check_need_update(::subject * psubject);
      //virtual bool update(::subject * psubject);
      virtual void update();


      virtual void enumerate_fonts();

   protected:
      virtual void sort_fonts();


      virtual void on_enumerate_fonts();

   public:

      //bool similar_font(char sz[256], const ::string & psz);
      //void default_font_name(char sz[256]);
      //double font_similarity(const ::string & pszSystem, const ::string & pszUser);


      virtual __pointer(font_enumeration_item) similar_font(const ::string & psz);
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


      //double font_similarity(const ::string & pszSystem, const ::string & pszUser)
      //{

      //   if (!strcmp(pszSystem, pszUser))
      //   {

      //      return 1.0;

      //   }

      //   return 0.0;

      //}
   };


} // namespace write_text




