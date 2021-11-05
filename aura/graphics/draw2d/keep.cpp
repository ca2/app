#include "framework.h"


namespace draw2d
{


   //keep::keep(graphics * pgraphics, bool bSave)
   //{

   //   m_bSave = false;

   //   if (pgraphics == nullptr)
   //   {

   //      m_pgraphics = nullptr;

   //      return;

   //   }

   //   m_pgraphics = pgraphics;

   //   if (bSave)
   //   {

   //      save();

   //   }

   //}


   //keep::~keep()
   //{

   //   if(m_bSave)
   //   {

   //      restore();

   //   }

   //}



   //void keep::save()
   //{

   //   if(m_pgraphics == nullptr)
   //   {

   //      return;

   //   }

   //   if(m_bSave)
   //   {

   //      return;

   //   }

   //   m_iSave = m_pgraphics->SaveDC();

   //   m_bSave = true;

   //}


   //void keep::restore()
   //{

   //   if(m_pgraphics == nullptr)
   //   {

   //      return;

   //   }

   //   if(!m_bSave)
   //   {

   //      return;

   //   }

   //   m_pgraphics->RestoreDC(m_iSave);

   //   m_bSave = false;

   //}


   //void keep::pulse()
   //{

   //   restore();

   //   save();

   //}


} // namespace draw2d



