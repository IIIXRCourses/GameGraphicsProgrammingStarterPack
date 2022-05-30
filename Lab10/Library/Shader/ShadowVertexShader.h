/*+===================================================================
  File:      SHADOWVERTEXSHADER.H

  Summary:   ShadowVertexShader header file contains declarations of
             ShadowVertexShader class used for the lab samples of Game
             Graphics Programming course.

  Classes: ShadowVertexShader

  ?2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Shader/VertexShader.h"

namespace library
{
    class ShadowVertexShader : public VertexShader
    {
    public:
        ShadowVertexShader() = delete;
        ShadowVertexShader(_In_ PCWSTR pszFileName, _In_ PCSTR pszEntryPoint, _In_ PCSTR pszShaderModel);
        ShadowVertexShader(const ShadowVertexShader& other) = delete;
        ShadowVertexShader(ShadowVertexShader&& other) = delete;
        ShadowVertexShader& operator=(const ShadowVertexShader& other) = delete;
        ShadowVertexShader& operator=(ShadowVertexShader&& other) = delete;
        virtual ~ShadowVertexShader() = default;

        virtual HRESULT Initialize(_In_ ID3D11Device* pDevice) override;
    };
}