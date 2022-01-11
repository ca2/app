//
//  account_credentials.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//


namespace account
{

   
   class CLASS_DECL_AXIS authenticator :
      virtual public ::object
   {
   public:
      
      
      authenticator();
      virtual ~authenticator();
      
      virtual void  pre_authenticate(credentials * pcredentials);
      
      virtual void  authenticate(credentials * pcredentials);
      

   };


} // namespace account



