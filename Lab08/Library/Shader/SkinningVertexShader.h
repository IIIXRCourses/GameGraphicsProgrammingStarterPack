/*+===================================================================
  File:      SKINNINGVERTEXSHADER.H

  Summary:   SkinningVertexShader header file contains declarations of
             SkinningVertexShader class used for the lab samples of Game
             Graphics Programming course.

  Classes: SkinningVertexShader

  2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Shader/VertexShader.h"

namespace library
{
    class SkinningVertexShader : public VertexShader
    {
    public:
        SkinningVertexShader() = delete;
        SkinningVertexShader(_In_ PCWSTR pszFileName, _In_ PCSTR pszEntryPoint, _In_ PCSTR pszShaderModel);
        SkinningVertexShader(const SkinningVertexShader& other) = delete;
        SkinningVertexShader(SkinningVertexShader&& other) = delete;
        SkinningVertexShader& operator=(const SkinningVertexShader& other) = delete;
        SkinningVertexShader& operator=(SkinningVertexShader&& other) = delete;
        virtual ~SkinningVertexShader() = default;

        virtual HRESULT Initialize(_In_ ID3D11Device* pDevice) override;
    };
}