#pragma once


namespace database
{


   class CLASS_DECL_AQUA key
   {
   public:


      string      m_strDataKey;

      bool        m_bLocalData;


      key();
      key(const std::initializer_list < var > & list);

      key(string strDataKey, bool bLocalData = false)
      {

         m_strDataKey = strDataKey;

         m_bLocalData = bLocalData;

      }


      key(const char * pszDataKey, bool bLocalData = false)
      {

         m_strDataKey = pszDataKey;

         m_bLocalData = bLocalData;

      }

      key(const id & idDataKey, bool bLocalData = false)
      {

         m_strDataKey = __str(idDataKey);

         m_bLocalData = bLocalData;

      }


      key(const key & key, bool bLocalData = false)
      {

         m_strDataKey = key.m_strDataKey;

         m_bLocalData = key.m_bLocalData || bLocalData;

      }


      key & operator = (const key & key)
      {

         m_strDataKey = key.m_strDataKey;

         m_bLocalData = key.m_bLocalData;

         return *this;

      }


      key & operator = (const char * pszDataKey)
      {

         m_strDataKey = pszDataKey;

         return *this;

      }


      bool operator == (const key & key) const
      {

         return m_strDataKey == key.m_strDataKey;

      }


      key & operator +=(const key & key)
      {

         if (m_strDataKey.is_empty())
         {

            m_strDataKey = key.m_strDataKey;

         }
         else if (key.m_strDataKey.has_char())
         {

            m_strDataKey += "/" + key.m_strDataKey;

         }

         m_bLocalData = m_bLocalData || key.m_bLocalData;

         return *this;

      }


      key operator + (const key & key) const
      {

         ::database::key keyAdd(*this);

         keyAdd += key;

         return keyAdd;

      }


      key & operator +=(const string & strDataKey)
      {

         if (m_strDataKey.is_empty())
         {

            m_strDataKey = strDataKey;

         }
         else if (strDataKey.has_char())
         {

            m_strDataKey += "/" + strDataKey;

         }

         return *this;

      }


      key operator + (const string & strDataKey) const
      {

         ::database::key keyAdd(*this);

         keyAdd += strDataKey;

         return keyAdd;

      }


      bool is_empty() const
      {

         return m_strDataKey.is_empty();

      }


      void set_local_data(bool bLocalData = true)
      {

         m_bLocalData = bLocalData;

      }

   };


} // namespace dabase


namespace str
{

   inline string & assign(string & str, const ::database::key & key)
   {

      return str = key.m_strDataKey;

   }


} // namespace str
