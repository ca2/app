#pragma once


//#include "acme/primitive/primitive/object.h"


enum enum_resource
{

   e_resource_memory = 1 << 0,
   e_resource_processing = 1 << 1,
   e_resource_display_bandwidth = 1 << 2,
   e_resource_blur_background = 1 << 3,
   e_resource_blurred_text_embossing = 1 << 4,
   e_resource_translucent_background = 1 << 5,

};

namespace apex
{




   class CLASS_DECL_APEX savings :
      virtual public ::object
   {
   public:


      enumeration < enum_resource > m_eresourceflagsShouldSave;
      enumeration < enum_resource > m_eresourceflagsWarning;


      savings();
      virtual ~savings();

      virtual void initialize(::particle * pparticle) override;

      virtual void save(enum_resource eresource);
      virtual void try_to_save(enum_resource eresource);

      virtual void use(enum_resource eresource);
      virtual void may_use(enum_resource eresource);

      virtual bool should_save(enum_resource eresource);
      virtual bool is_trying_to_save(enum_resource eresource);

      virtual void warn(enum_resource eresource);

      virtual void clear_warning(enum_resource eresource);

      virtual bool is_warning(enum_resource eresource);


   };


} // namespace apex





