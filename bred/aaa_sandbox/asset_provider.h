#pragma once
//#include <vulkan/vulkan.h>
//////#include <stdexcept>
//#include <memory>
//#include "SceneFoundry/sandbox_renderer/gltf.h"

namespace graphics3d
{


    class IAssetProvider :
        virtual public ::particle
    {
    public:
        // virtual VkDescriptorImageInfo getCubemapDescriptor(const ::scoped_string & name) const = 0;
        //
        //    virtual VkDescriptorImageInfo getBRDFLUTDescriptor()    const = 0;
        //    virtual VkDescriptorImageInfo getIrradianceDescriptor() const = 0;
        //    virtual VkDescriptorImageInfo getPrefilteredDescriptor() const = 0;
        //
        //    virtual VkDescriptorImageInfo getTextureDescriptor(const ::scoped_string & name) const = 0;

        virtual ::array_base<::string> listTextureNames()    const = 0;
        virtual ::pointer<::graphics3d::IModel> getGLTFmodel(const ::scoped_string & name) const = 0;

    };


} // namespace graphics3d

