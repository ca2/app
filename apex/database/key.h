#pragma once


#include "acme/primitive/string/string.h"


namespace database
{


   class CLASS_DECL_APEX key
   {
   public:


      string      m_strDataKey;

      bool        m_bLocalData;


      key();
      key(const std::initializer_list < ::payload > & list);

      key(string strDataKey, bool bLocalData = false);


      key(const char * pszDataKey, bool bLocalData = false);

      key(const atom & idDataKey, bool bLocalData = false);

      key(const key & key, bool bLocalData = false);
      key & operator = (const key & key);
      key & operator = (const char * pszDataKey);


      bool operator == (const key & key) const;


      key & operator +=(const key & key);
    

      key operator + (const key & key) const;
      

      key & operator +=(const ::string & strDataKey);
     
      key operator + (const ::string & strDataKey) const;
    

      bool is_empty() const;
 

      void set_local_data(bool bLocalData = true);

   };


} // namespace dabase


//namespace str
//{

   inline string & assign(string & str, const ::database::key & key)
   {

      return str = key.m_strDataKey;

   }

//
//} // namespace str
