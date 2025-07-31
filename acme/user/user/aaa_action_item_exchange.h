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
      m_pszName = strdup(scopedstrName);
      m_pszId = strdup(scopedstrId);
      m_pszLabel = strdup(scopedstrLabel);
      m_pszAccelerator = strdup(scopedstrAccelerator);
      m_pszDescription = strdup(scopedstrDescription);

   }


   action_item_exchange(action_item_exchange && e)
   {

      ::memory_copy(this, &e, sizeof(action_item_exchange));
      ::memory_set(&e, 0, sizeof(action_item_exchange));

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



