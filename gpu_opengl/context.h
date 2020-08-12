#pragma once


namespace opengl
{


   class CLASS_DECL_GPU_OPENGL context :
      virtual public ::gpu::context
   {
   public:


      /*enum enum_mode
      {
         e_mode_none,
         e_mode_system,
         e_mode_egl,
         e_mode_glx,
      };

      enum_mode                        m_emode;

      ::size                           m_sizeNew;
      ::size                           m_size;
      float                            m_z;
      point                            m_pointTranslate;
      __pointer(::gpu::buffer)         m_pbuffer;
      __pointer(::gpu::program)        m_pprogram;
      unsigned int                     m_VAO;
      unsigned int                     m_VBO;
*/

      context();
      virtual ~context();


      //virtual ::estatus initialize(::object* pobjectContext) override;

      virtual string _001GetIntroProjection() override;
      virtual string _001GetIntroFragment() override;

      virtual ::estatus draw() override;
      virtual ::estatus start() override;
      virtual ::estatus render() override;

      //virtual ::estatus create_offscreen_buffer(const ::size& size);
      //virtual ::estatus _create_offscreen_buffer(const ::size& size);

      //virtual ::estatus resize_offscreen_buffer(const ::size& size);
      //virtual ::estatus destroy_offscreen_buffer();

   /*   virtual void translate_shader(string & str);

      virtual void _translate_shader(string_array& stra);*/

      //virtual ::estatus make_current();

      // virtual string load_fragment(const char* pszPath, enum_shader_source& eshadersource);

      //virtual string get_shader_version_text();


   };


} // namespace gpu



