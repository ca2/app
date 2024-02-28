#pragma once


struct CLASS_DECL_ACME action_item_exchange
{

   int m_iIndex;
   char * m_pszName;
   char * m_pszId;
   char * m_pszLabel;
   char * m_pszAccelerator;
   char * m_pszDescription;

   action_item_exchange(int iIndex, const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrId, const ::scoped_string & scopedstrLabel, const ::scoped_string & scopedstrAccelerator, const ::scoped_string & scopedstrDescription)
   {

      m_iIndex = iIndex;
      m_pszName = strdup(pszName);
      m_pszId = strdup(pszId);
      m_pszLabel = strdup(pszLabel);
      m_pszAccelerator = strdup(pszAccelerator);
      m_pszDescription = strdup(pszDescription);

   }


   action_item_exchange(action_item_exchange && e)
   {

      memcpy(this, &e, sizeof(action_item_exchange));
      memset(&e, 0, sizeof(action_item_exchange));

   }


   ~action_item_exchange()
   {

      ::acme::free(m_pszName);
      ::acme::free(m_pszId);
      ::acme::free(m_pszLabel);
      ::acme::free(m_pszAccelerator);
      ::acme::free(m_pszDescription);

   }

};



