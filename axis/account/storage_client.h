//
//  account_storage_client.hpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/12/18.
//


namespace account
{
   
   
   class CLASS_DECL_AXIS storage_client :
      virtual public ::object
   {
   public:
      
      
      storage *         m_pstorage;
      string            m_strToken;
      
      
      storage_client();
      ~storage_client() override;
      
      
      virtual void initialize_account_storage_client(storage * pstorage);

      
      virtual bool get(string strKey, string & strValue);
      virtual void set(string strKey, string strValue);

      
   };
   
   
} // namespace account



