//
//  account_storage_client.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//


namespace account
{
   
   
   class CLASS_DECL_AURA storage_client :
      virtual public ::object
   {
   public:
      
      
      storage *         m_pstorage;
      string            m_strToken;
      
      
      storage_client();
      virtual ~storage_client();
      
      
      virtual ::estatus initialize_account_storage_client(storage * pstorage);

      
      virtual ::estatus get(string strKey, string & strValue);
      virtual bool set(string strKey, string strValue);

      
   };
   
   
} // namespace account



