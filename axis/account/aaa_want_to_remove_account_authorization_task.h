//
//  account_login_task.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 11/12/18.
//


namespace account
{
   
   
   class CLASS_DECL_AXIS http_execute:
   virtual public object
   {
   public:
      
      
      string                  m_strUrl;
      property_set            m_propertysetPost;
      property_set            m_propertysetHeaders;
      string                  m_strResponse;
      
      
   };
   
   
   class CLASS_DECL_AXIS http_execute_array:
   public pointer_array < http_execute >
   {
      
   };

   
   class CLASS_DECL_AXIS authorization_task :
      virtual public ::object
   {
   public:
    
      
      
      
      authorization_task(::particle * pparticle);
      virtual ~authorization_task();
      

      
   };


} // namespace account



