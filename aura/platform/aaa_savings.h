#pragma once


namespace aura
{


   enum e_resource
   {

      resource_memory = 1 << 0,
      resource_processing = 1 << 1,
      resource_display_bandwidth = 1 << 2,
      resource_blur_background = 1 << 3,
      resource_blurred_text_embossing = 1 << 4,
      resource_translucent_background = 1 << 5,

   };


   class CLASS_DECL_AURA savings :
      virtual public ::object
   {
   public:


      cflag < e_resource > m_eresourceflagsShouldSave;
      cflag < e_resource > m_eresourceflagsWarning;


      savings();
      virtual ~savings();

      virtual ::estatus initialize(::layered * pobjectContext) override;

      virtual void save(e_resource eresource);
      virtual void try_to_save(e_resource eresource);

      virtual void use(e_resource eresource);
      virtual void may_use(e_resource eresource);

      virtual bool should_save(e_resource eresource);
      virtual bool is_trying_to_save(e_resource eresource);

      virtual void warn(e_resource eresource);

      virtual void clear_warning(e_resource eresource);

      virtual bool is_warning(e_resource eresource);


   };


} // namespace aura





