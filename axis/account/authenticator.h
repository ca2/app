//
//  account_credentials.hpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/12/18.
//


namespace account
{

   
   class CLASS_DECL_AXIS authenticator :
      virtual public ::object
   {
   public:
      
      
      authenticator();
      ~authenticator() override;
      
      
      virtual void pre_authenticate(credentials * pcredentials);
      
      virtual void authenticate(credentials * pcredentials);
      

   };


} // namespace account



