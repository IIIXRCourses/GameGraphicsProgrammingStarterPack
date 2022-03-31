/*+===================================================================
  File:      SHADER.H

  Summary:   Shader header file contains declarations of Shader
             class used for the lab samples of Game Graphics
             Programming course.

  Classes: Shader

  � 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

namespace library
{
    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    PixelShader

      Summary:  Pixel shader

      Methods:  Initialize
                  Pure virtual function that initializes the shader
                GetFileName
                  Returns the name of the shader file to be compiled
                compile
                  Compiles the given shader file
                Game
                  Constructor.
                ~Game
                  Destructor.
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    class Shader
    {
    public:
        Shader() = delete;
        Shader(_In_ PCWSTR pszFileName, _In_ PCSTR pszEntryPoint, _In_ PCSTR pszShaderModel);
        Shader(const Shader& other) = delete;
        Shader(Shader&& other) = delete;
        Shader& operator=(const Shader& other) = delete;
        Shader& operator=(Shader&& other) = delete;
        virtual ~Shader() = default;

        virtual HRESULT Initialize(_In_ ID3D11Device* pDevice) = 0;
        PCWSTR GetFileName() const;

    protected:
        HRESULT compile(_Outptr_ ID3DBlob** ppOutBlob);

        PCWSTR m_pszFileName;
        PCSTR m_pszEntryPoint;
        PCSTR m_pszShaderModel;
    };
}