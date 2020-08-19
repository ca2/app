//
//  account_credentials.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//


namespace account
{

   
   class CLASS_DECL_AURA authenticator :
      virtual public ::object
   {
   public:
      
      
      authenticator(::object * pobject);
      virtual ~authenticator();
      
      virtual ::estatus  pre_authenticate(credentials * pcredentials);
      
      virtual ::estatus  authenticate(credentials * pcredentials);
      

   };


} // namespace account



