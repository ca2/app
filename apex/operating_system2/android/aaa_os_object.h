#pragma once


class CLASS_DECL_APEX os_object :
   virtual public ::matter
{
public:


   jobject     m_jobject;
   jclass      m_jclass;


   os_object(jobject jobject);
   virtual ~os_object();


   jfieldID field_str(const char *psz);
   jfieldID field_b(const ::scoped_string & scopedstr);
   jfieldID field_uch(const ::scoped_string & scopedstr);
   jfieldID field_ch(const ::scoped_string & scopedstr);
   jfieldID field_sh(const ::scoped_string & scopedstr);
   jfieldID field_i(const ::scoped_string & scopedstr);
   jfieldID field_l(const ::scoped_string & scopedstr);
   jfieldID field_f(const ::scoped_string & scopedstr);
   jfieldID field_d(const ::scoped_string & scopedstr);


   void set_str(jfieldID jfieldid, const ::scoped_string & scopedstr);

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

   void set_str(const ::scoped_string & scopedstrField, const ::scoped_string & scopedstr);

   string get_str(const ::scoped_string & scopedstrField);

   void set_b(const ::scoped_string & scopedstrField, bool boolean);

   bool get_b(const ::scoped_string & scopedstrField);

   void set_uch(const ::scoped_string & scopedstrField, byte b);

   byte get_uch(const ::scoped_string & scopedstrField);

   void set_ch(const ::scoped_string & scopedstrField, char ch);

   char get_ch(const ::scoped_string & scopedstrField);

   void set_sh(const ::scoped_string & scopedstrField, short sh);

   short get_sh(const ::scoped_string & scopedstrField);

   void set_i(const ::scoped_string & scopedstrField, int i);

   int get_i(const ::scoped_string & scopedstrField);

   void set_l(const ::scoped_string & scopedstrField, long long ll);

   long long get_l(const ::scoped_string & scopedstrField);

   void set_f(const ::scoped_string & scopedstrField, float f);

   float get_f(const ::scoped_string & scopedstrField);

   void set_d(const ::scoped_string & scopedstrField, double f);

   double get_d(const ::scoped_string & scopedstrField);


};


#define JX(type, name) \
jfieldID m_fid##name = field_##type("m_" # type # name); \
template < typename T > \
inline void set##name(T && t) { set_##type(m_fid##name, t); } \
inline auto get##name() { return get_##type(m_fid##name); }

