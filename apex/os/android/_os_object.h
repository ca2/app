#pragma once


class CLASS_DECL_APEX os_object :
   virtual public ::element
{
public:


   jobject     m_jobject;
   jclass      m_jclass;


   os_object(jobject jobject);
   virtual ~os_object();


   jfieldID field_str(const char *psz);
   jfieldID field_b(const char* psz);
   jfieldID field_uch(const char* psz);
   jfieldID field_ch(const char* psz);
   jfieldID field_sh(const char* psz);
   jfieldID field_i(const char* psz);
   jfieldID field_l(const char* psz);
   jfieldID field_f(const char* psz);
   jfieldID field_d(const char* psz);


   void set_str(jfieldID jfieldid, const char* psz);

   string get_str(jfieldID jfieldid);

   void set_b(jfieldID jfieldid, bool b);

   bool get_b(jfieldID jfieldid);

   void set_uch(jfieldID jfieldid, byte b);

   byte get_uch(jfieldID jfieldid);

   void set_ch(jfieldID jfieldid, char ch);

   char get_ch(jfieldID jfieldid);

   void set_sh(jfieldID jfieldid, short sh);

   short get_sh(jfieldID jfieldid);

   void set_i(jfieldID jfieldid, int i);

   int get_i(jfieldID jfieldid);

   void set_l(jfieldID jfieldid, long long ll);

   long long get_l(jfieldID jfieldid);

   void set_f(jfieldID jfieldid, float f);

   float get_f(jfieldID jfieldid);

   void set_d(jfieldID jfieldid, double d);

   double get_d(jfieldID jfieldid);

   void set_str(const char* pszField, const char* psz);

   string get_str(const char* pszField);

   void set_b(const char* pszField, bool boolean);

   bool get_b(const char* pszField);

   void set_uch(const char* pszField, byte b);

   byte get_uch(const char* pszField);

   void set_ch(const char* pszField, char ch);

   char get_ch(const char* pszField);

   void set_sh(const char* pszField, short sh);

   short get_sh(const char* pszField);

   void set_i(const char* pszField, int i);

   int get_i(const char* pszField);

   void set_l(const char* pszField, long long ll);

   long long get_l(const char* pszField);

   void set_f(const char* pszField, float f);

   float get_f(const char* pszField);

   void set_d(const char* pszField, double f);

   double get_d(const char* pszField);


};


#define JX(type, name) \
jfieldID m_fid##name = field_##type("m_" # type # name); \
template < typename T > \
inline void set##name(T && t) { set_##type(m_fid##name, t); } \
inline auto get##name() { return get_##type(m_fid##name); }

