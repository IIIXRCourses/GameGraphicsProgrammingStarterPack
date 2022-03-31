/*+===================================================================
  File:      PIXELSHADER.H

  Summary:   PixelShader header file contains declarations of
             PixelShader class used for the lab samples of Game
             Graphics Programming course.

  Classes: PixelShader

  � 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Shader/Shader.h"

namespace library
{
    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    PixelShader

      Summary:  Pixel shader

      Methods:  Initialize
                  Initializes and compiles the pixel shader
                GetPixelShader
                  Returns the reference to the D3D11 pixel shader
                Game
                  Constructor.
                ~Game
                  Destructor.
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    class PixelShader : public Shader
    {
    public:
        PixelShader() = delete;
        PixelShader(_In_ PCWSTR pszFileName, _In_ PCSTR pszEntryPoint, _In_ PCSTR pszShaderModel);
        PixelShader(const PixelShader& other) = delete;
        PixelShader(PixelShader&& other) = delete;
        PixelShader& operator=(const PixelShader& other) = delete;
        PixelShader& operator=(PixelShader&& other) = delete;
        virtual ~PixelShader() = default;

        virtual HRESULT Initialize(_In_ ID3D11Device* pDevice) override;

        ComPtr<ID3D11PixelShader>& GetPixelShader();

    protected:
        ComPtr<ID3D11PixelShader> m_pixelShader;
    };
}