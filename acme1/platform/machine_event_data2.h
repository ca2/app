#pragma once


class CLASS_DECL_ACME blob
{
public:

   memsize   m_sizet;
   char *   m_pchData;


   blob();
   ~blob();
   
   void read(FILE * file);
   void write(FILE * file);
   
   blob & operator = (const char * psz);
   
   
};


class CLASS_DECL_ACME machine_event_data
{
public:
   
   class CLASS_DECL_ACME fixed
   {
   public:
      
      
      bool  m_bRequestCloseApplication;
      bool  m_bSpaUpgrade;
      
      
      fixed();
      
   };
   
   
   fixed    m_fixed;
   blob     m_blobCommand;

   void read(FILE * file);
   void write(FILE * file);
   
   
};



