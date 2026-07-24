// From aura/platform/draw2d_context2.h by camilo 2026-07-22 19:54 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once



namespace aura
{

   template<typename TYPE>
   class simple_chain : virtual public ::particle
   {
   public:


      TYPE *m_pnext;


      simple_chain() { simple_chain<TYPE>::m_pnext = nullptr; }

      void chain(TYPE *p)
      {
         if (simple_chain<TYPE>::m_pnext == nullptr)
         {
            simple_chain<TYPE>::m_pnext = p;
         }
         else
         {
            simple_chain<TYPE>::m_pnext->simple_chain<TYPE>::chain(p);
         }
      }
      void unchain(TYPE *p)
      {
         if (simple_chain<TYPE>::m_pnext == p)
         {
            simple_chain<TYPE>::m_pnext = simple_chain<TYPE>::m_pnext->simple_chain<TYPE>::m_pnext;
         }
         else
         {
            simple_chain<TYPE>::m_pnext->simple_chain<TYPE>::unchain(p);
         }
      }

      TYPE *get_last()
      {
         TYPE *plast = simple_chain<TYPE>::m_pnext;
         if (plast == nullptr)
            return nullptr;
         while (plast->simple_chain<TYPE>::m_pnext != nullptr)
         {
            plast = plast->simple_chain<TYPE>::m_pnext;
         }
         return plast;
      }
   };


} // namespace aura
