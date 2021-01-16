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
      
      
      authenticator(::layered * pobjectContext);
      virtual ~authenticator();
      
      virtual ::e_status  pre_authenticate(credentials * pcredentials);
      
      virtual ::e_status  authenticate(credentials * pcredentials);
      

   };


} // namespace account



