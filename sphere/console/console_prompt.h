#pragma once


namespace console
{


   class CLASS_DECL_SPHERE prompt :
      virtual public object
   {
   public:


      ::user::single_document_template * m_pimpactsystem;

      
      prompt(::particle * pparticle);


      prompt_impact & impact(bool bShow = true, bool bCreateMini = true);
      

      int getch();
      void ungetch(int c);


   };



} // namespace console
