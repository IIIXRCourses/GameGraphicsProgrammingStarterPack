#pragma once

#include "Common.h"

#include "Shader/PixelShader.h"

namespace library
{
    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    PointLight

      Summary:  Point light that emits a light from a single point to 
                every direction

      Methods:  GetPosition
                  Returns the position of the light
                GetColor
                  Returns the color of the light
                Update
                  Updates the light
                PointLight
                  Constructor.
                ~PointLight
                  Destructor.
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    class PointLight
    {
    public:
        PointLight() = delete;
        PointLight(_In_ const XMFLOAT4& position, _In_ const XMFLOAT4& color);
        PointLight(const PointLight& other) = default;
        PointLight(PointLight&& other) = default;
        PointLight& operator=(const PointLight& other) = default;
        PointLight& operator=(PointLight&& other) = default;
        virtual ~PointLight() = default;

        const XMFLOAT4& GetPosition() const;
        const XMFLOAT4& GetColor() const;

        virtual void Update(_In_ FLOAT deltaTime);
    protected:
        XMFLOAT4 m_position;
        XMFLOAT4 m_color;
    };
}