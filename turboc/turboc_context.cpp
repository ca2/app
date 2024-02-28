#include "framework.h"
//#include "src/turboc.h"


namespace turboc
{


   context::context(::particle * pparticle):
      ::object(pparticle),

      m_pimagea(pparticle)
   {
      m_pimagea->set_size(16);
      m_rgbset.set_size(256);


   }

   context::~context()
   {
   }

   bool context::gok()
   {

/*      return m_pimage->area() > 0;

   }

   void context::werase()
   {

      if(!gok())
         return;


/*      m_pimage->Fill(0,0,0,0);


   }

   void context::wrefresh()
   {

   }

   void context::defer_synch()
   {
      if(m_iActivePage == m_iVisualPage)
      {
/*         m_pimage->copy(m_pimagea[m_iActivePage]);
      }

   }

   void context::resize(int x,int y)
   {

      if(x <= 0 || y <= 0)
         return;

/*      m_pimage = create_image({x, y});

/*      m_pimage->Fill(0,0,0,0);

      forall(m_pimagea)
      {

         item.create(this);

         item->create(x,y);

         item->Fill(0,0,0,0);

      }

   }


} // namespace turboc
