#include "framework.h"
#include "key.h"
//#include "acme/prototype/prototype/payload.h"


//namespace database
//{
//
//
//   key::key()
//   {
//
//      //m_bLocalData = false;
//
//   }
//
//
//   key::key(const ::scoped_string & scopedstr) :
//      m_strDataKey(scopedstr)
//   {
//
//      //m_bLocalData = false;
//
//   }
//
//
////   key::key(const std::initializer_list < ::payload > & list)
////   {
////
////      m_bLocalData = false;
////
////      for (auto & payload : list)
////      {
////
////         if (payload.get_type() == e_type_bool)
////         {
////
////            m_bLocalData = payload.get_bool();
////
////         }
////         else
////         {
////
////            m_strDataKey = payload;
////
////         }
////
////      }
////
////   }
////
////
////   key::key(const ::scoped_string & scopedstrDataKey, bool bLocalData)
////   {
////
////      m_strDataKey = strDataKey;
////
////      m_bLocalData = bLocalData;
////
////   }
////
////
////   key::key(const_char_pointer pszDataKey, bool bLocalData)
////   {
////
////      m_strDataKey = pszDataKey;
////
////      m_bLocalData = bLocalData;
////
////   }
////
////
////   key::key(const atom & idDataKey, bool bLocalData)
////   {
////
////      m_strDataKey = idDataKey;
////
////      m_bLocalData = bLocalData;
////
////   }
////
////
////   key::key(const key & key, bool bLocalData)
////   {
////
////      m_strDataKey = key.m_strDataKey;
////
////      m_bLocalData = key.m_bLocalData || bLocalData;
////
////   }
//
//
//   key & key::operator = (const key & key)
//   {
//
//      m_strDataKey = key.m_strDataKey;
//
//      //m_bLocalData = key.m_bLocalData;
//
//      return *this;
//
//   }
//
//
//   key & key::operator = (const ::scoped_string & scopedstrDataKey)
//   {
//
//      m_strDataKey = scopedstrDataKey;
//
//      return *this;
//
//   }
//
//
//   bool key::operator == (const key & key) const
//   {
//
//      return m_strDataKey == key.m_strDataKey;
//
//   }
//
//
//   key & key::operator +=(const key & key)
//   {
//
//      if (m_strDataKey.is_empty())
//      {
//
//         m_strDataKey = key.m_strDataKey;
//
//      }
//      else if (key.m_strDataKey.has_character())
//      {
//
//         m_strDataKey += "/" + key.m_strDataKey;
//
//      }
//
//      //m_bLocalData = m_bLocalData || key.m_bLocalData;
//
//      return *this;
//
//   }
//
//
//   key key::operator + (const key & key) const
//   {
//
//      ::string strDataKeyAdd(*this);
//
//      keyAdd += key;
//
//      return keyAdd;
//
//   }
//
//
//   key & key::operator +=(const ::scoped_string & scopedstrDataKey)
//   {
//
//      if (m_strDataKey.is_empty())
//      {
//
//         m_strDataKey = strDataKey;
//
//      }
//      else if (strDataKey.has_character())
//      {
//
//         m_strDataKey += "/" + strDataKey;
//
//      }
//
//      return *this;
//
//   }
//
//
//   key key::operator + (const ::scoped_string & scopedstrDataKey) const
//   {
//
//      ::string strDataKeyAdd(*this);
//
//      keyAdd += strDataKey;
//
//      return keyAdd;
//
//   }
//
//
//   bool key::is_empty() const
//   {
//
//      return m_strDataKey.is_empty();
//
//   }
//
////
////   void key::set_local_data(bool bLocalData )
////   {
////
////      m_bLocalData = bLocalData;
////
////   }
//
//
//} // namespace database
//
//
//
