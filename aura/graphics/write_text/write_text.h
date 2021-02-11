// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


namespace write_text
{


   class CLASS_DECL_AURA write_text :
      virtual public ::apex::department
   {
   public:



      __pointer(class font_department)       m_pfontdepartment;



      write_text();
      virtual ~write_text();

      
      class font_department * fonts();


      virtual void finalize() override;
      virtual void term() override;


      //virtual double font_similarity(const char * pszSystem, const char * pszUser);


   };


} // namespace writetext



