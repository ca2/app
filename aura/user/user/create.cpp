#include "framework.h" // previously aura/user/user.h


namespace user
{


   create::create()
   {

      m_bAutoWindowFrame = true;
      m_bWindowFrame = false;
      m_pdocumentCurrent = nullptr;
      m_ptemplateNewDocument = nullptr;
      m_puiLastView = nullptr;
      m_puiCurrentFrame = nullptr;
      m_puiNew = nullptr;

   }

   //create::create(const create & pcreate)
   //{

   //   operator =(pcreate);

   //}

   create::~create()
   {

   }

   //create & create::operator=(const create & pcreate)
   //{

   //   if (this == &pcreate)
   //      return *this;

   //   m_typeNewView = pcreate.m_typeNewView;
   //   m_pdocumentCurrent = pcreate.m_pdocumentCurrent;
   //   m_ptemplateNewDocument = pcreate.m_ptemplateNewDocument;
   //   m_puiLastView = pcreate.m_puiLastView;
   //   m_puiCurrentFrame = pcreate.m_puiCurrentFrame;
   //   m_puiNew = pcreate.m_puiNew;

   //   return *this;

   //}


} // namespace aura





