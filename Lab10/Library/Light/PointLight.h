/*+===================================================================
  File:      POINTLIGHT.H

  Summary:   Light header file contains declarations of the
             point light.

  Classes: PointLight

  ?2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Shader/PixelShader.h"

namespace library
{
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
        const XMMATRIX& GetViewMatrix() const;
        const XMMATRIX& GetProjectionMatrix() const;

        virtual void Initialize(_In_ UINT uWidth, _In_ UINT uHeight);
        virtual void Update(_In_ FLOAT deltaTime);
    protected:
        XMFLOAT4 m_position;
        XMFLOAT4 m_color;
        XMVECTOR m_eye;
        XMVECTOR m_at;
        XMVECTOR m_up;
        XMMATRIX m_view;
        XMMATRIX m_projection;

        static constexpr const XMVECTORF32 DEFAULT_UP = { 0.0f, 1.0f, 0.0f, 0.0f };
    };
}