// ICamera.h
#pragma once




namespace graphics3d
{
    class ICamera :
        virtual public ::particle
    {
    public:
        //virtual ~ICamera() = default;

        virtual void updateView() {};

        virtual void updateProjection(::f32 aspectRatio, ::f32 nearZ = 0.1f, ::f32 farZ = 100.f) = 0;

        virtual floating_matrix4 getViewMatrix() const = 0;

        virtual floating_matrix4 getProjectionMatrix() const = 0;

        virtual floating_sequence3 getPosition() const = 0;

        virtual floating_matrix4 getInverseViewMatrix() const = 0;
    };
} // namespace graphics3d

