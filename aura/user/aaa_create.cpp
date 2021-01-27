#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{


   create::create()
   {

      set_layer(LAYERED_USER_CREATE, this);

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





