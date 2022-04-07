#pragma once


namespace opengl
{


   class CLASS_DECL_GPU_OPENGL context :
      virtual public ::gpu::context
   {
   public:


      itask_t									m_itaskGpu;


      unsigned int                     m_VAO;
      unsigned int                     m_VBO;

      GLuint                           m_gluTextureBitmap1;
      int                              m_iLastBitmap1Scan;
      ::size_i32                       m_sizeBitmap1;

      memory                           m_memorySwap;

      /*enum enum_mode
      {
         e_mode_none,
         e_mode_system,
         e_mode_egl,
         e_mode_glx,
      };

      enum_mode                        m_emode;

      ::size_i32                           m_sizeNew;
      ::size_i32                           m_size;
      float                            m_z;
      point_i32                            m_pointTranslate;
      __pointer(::gpu::buffer)         m_pbuffer;
      __pointer(::gpu::program)        m_pprogram;
      unsigned int                     m_VAO;
      unsigned int                     m_VBO;
*/

      context();
      ~context() override;


      //virtual void initialize(::object * pobject) override;

      virtual string _001GetIntroProjection() override;
      virtual string _001GetIntroFragment() override;

      virtual void draw() override;
      virtual void start() override;
      virtual void render() override;


      void set_bitmap_1(::image * pimage) override;

      virtual void swap_buffers();

      //virtual void create_offscreen_buffer(const ::size_i32& size);
      //virtual void _create_offscreen_buffer(const ::size_i32& size);

      //virtual void resize_offscreen_buffer(const ::size_i32& size);
      //virtual void destroy_offscreen_buffer();

   /*   virtual void translate_shader(string & str);

      virtual void _translate_shader(string_array& stra);*/

      //virtual void make_current();

      // virtual string load_fragment(const ::string & pszPath, enum_shader_source& eshadersource);

      //virtual string get_shader_version_text();


   };


} // namespace gpu



