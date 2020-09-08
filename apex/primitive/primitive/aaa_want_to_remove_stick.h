#pragma once


class CLASS_DECL_APEX stick :
   virtual public context_object
{
public:

   
   sticker        m_sticker;


   stick(const char * psz = nullptr) :
      m_sticker(psz)
   {

      m_psticker = &m_sticker;

   }

};



