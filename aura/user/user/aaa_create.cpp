#include "framework.h"
//#include "base/user/user/_component.h"


namespace user
{


   create::create()
   {

      set_layer(LAYERED_USER_CREATE, this);

      m_bAutoWindowFrame = true;
      m_bWindowFrame = false;
      m_pdocumentCurrent = nullptr;
      m_ptemplateNewDocument = nullptr;
      m_puiLastAccess = nullptr;
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

   //   m_typeNewImpact = pcreate.m_typeNewImpact;
   //   m_pdocumentCurrent = pcreate.m_pdocumentCurrent;
   //   m_ptemplateNewDocument = pcreate.m_ptemplateNewDocument;
   //   m_puiLastAccess = pcreate.m_puiLastImpact;
   //   m_puiCurrentFrame = pcreate.m_puiCurrentFrame;
   //   m_puiNew = pcreate.m_puiNew;

   //   return *this;

   //}


} // namespace aura





