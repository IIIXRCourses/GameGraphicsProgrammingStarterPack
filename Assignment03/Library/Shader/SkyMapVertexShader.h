/*+===================================================================
  File:      SKYMAPVERTEXSHADER.H

  Summary:   SkyMapVertexShader header file contains declarations of 
             SkyMapVertexShader class used for the lab samples of 
             Game Graphics Programming course.

  Classes: SkyMapVertexShader

  ?2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Shader/VertexShader.h"

namespace library
{
    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    SkyMapVertexShader

      Summary:  Sky map vertex shader

      Methods:  Initialize
                  Initializes the vertex shader and the input layout
                SkyMapVertexShader
                  Constructor.
                ~SkyMapVertexShader
                  Destructor.
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    class SkyMapVertexShader : public VertexShader
    {
    public:
        SkyMapVertexShader() = delete;
        SkyMapVertexShader(_In_ PCWSTR pszFileName, _In_ PCSTR pszEntryPoint, _In_ PCSTR pszShaderModel);
        SkyMapVertexShader(const SkyMapVertexShader& other) = delete;
        SkyMapVertexShader(SkyMapVertexShader&& other) = delete;
        SkyMapVertexShader& operator=(const SkyMapVertexShader& other) = delete;
        SkyMapVertexShader& operator=(SkyMapVertexShader&& other) = delete;
        virtual ~SkyMapVertexShader() = default;

        virtual HRESULT Initialize(_In_ ID3D11Device* pDevice) override;
    };
}