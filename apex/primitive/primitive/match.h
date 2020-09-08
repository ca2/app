#pragma once


namespace match
{


   class CLASS_DECL_APEX item :
      virtual public object
   {
   public:


      item() {}
      virtual ~item() {}


      virtual bool matches(const var& var) const = 0;


   };


   class CLASS_DECL_APEX _and :
      virtual public item
   {
   public:


      item* m_pitem1;
      item* m_pitem2;


      virtual bool matches(const var& var) const;

   };


   class CLASS_DECL_APEX string :
      virtual public item
   {
   public:


      ::string      m_str;


      string(const char* psz = nullptr);


      virtual bool matches(const var& var) const;


   };


   class CLASS_DECL_APEX ci_string :
      virtual public string
   {
   public:


      ci_string(const char* psz = nullptr);


      virtual bool matches(const var& var) const;


   };


   class CLASS_DECL_APEX prefix :
      virtual public string
   {
   public:


      prefix(const char* psz = nullptr);


      virtual bool matches(const var& var) const;


   };


   class CLASS_DECL_APEX ci_prefix :
      virtual public string
   {
   public:


      ci_prefix(const char* psz = nullptr);


      virtual bool matches(const var& var) const;


   };


   class CLASS_DECL_APEX suffix :
      virtual public string
   {
   public:


      suffix(const char* psz = nullptr);


      virtual bool matches(const var& var) const;


   };


   class CLASS_DECL_APEX ci_suffix :
      virtual public string
   {
   public:


      ci_suffix(const char* psz = nullptr);


      virtual bool matches(const var& var) const;

   };


   class CLASS_DECL_APEX any :
      virtual public item
   {
   public:


      HAVE_ARRAY_OF(item, m_itema, item);


      virtual bool matches(const var& var) const;



   };


} // namespace match



