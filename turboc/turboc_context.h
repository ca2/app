#pragma once

namespace turboc
{



   class CLASS_DECL_TURBOC action_context:
      virtual public ::object
   {
   public:



/*      ::image::image_pointer           m_pimage;
/*      image_array         m_pimagea;

      ::i32 m_iDriver;
      ::i32 m_iActivePage;
      ::i32 m_iVisualPage;

      array <RgbStruct > m_rgbset;



      action_context(::particle * pparticle);
      virtual ~action_context();

      bool gok();

      void werase();
      void wrefresh();

      void defer_synch();


/*      ::image::image_pointer & aimage() { return *m_pimagea[m_iActivePage]; }
/*      ::draw2d::graphics & ag() { return *aimage().get_graphics(); }

/*      image_array & Pixmaps() { return m_pimagea; }
      array <RgbStruct > & Colors() { return m_rgbset; }

      void resize(::i32 x,::i32 y);

   };

   CLASS_DECL_TURBOC void set_context(::turboc::action_context * pcontext);

} // namespace turboc

