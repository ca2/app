// Created by camilo on 2026-03-25 18:27 <3ThomasBorregaardSørensen!!
#pragma once


namespace console
{

   enum enum_response
   {

      e_response_no = -1,
      e_response_cancel = 0,
      e_response_yes = 1,

   };

   class console:
      virtual public ::particle
   {
   public:




      console();
      ~console() override;


      virtual void defer_non_root();

      virtual void start_input();

      virtual int getch(void);

      virtual int get_thoughtful_character();

      virtual enum_response yes_no(const char * pszPrompt);
      virtual enum_response yes_no_default_yes(const char * pszPrompt);


   };


} // namespace console



