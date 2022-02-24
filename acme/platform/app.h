//
// Created by camilo on 22/02/2022. 01:19 <3ThomasBorregaardSorensen!!
//
#pragma once


class CLASS_DECL_ACME app :
   virtual public ::app_core,
   virtual public ::acme::context,
   virtual public ::task
{
public:


   static app *    g_p;

   int               m_iExitCode;


   app();
   ~app() override;


   virtual bool is_application() const;

   virtual bool is_system() const;
   virtual bool is_session() const;

   virtual bool is_service() const;
   virtual bool is_user_service() const;

   void set_args(int argc, char * argv[], char * envp[]);

   int main_loop();


};


