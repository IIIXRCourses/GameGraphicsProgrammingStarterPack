/*+===================================================================
  File:      VERTEXSHADER.H

  Summary:   VertexShader header file contains declarations of 
             VertexShader class used for the lab samples of Game 
             Graphics Programming course.

  Classes: VertexShader

  � 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Shader/Shader.h"

namespace library
{
    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    VertexShader

      Summary:  Vertex shader

      Methods:  Initialize
                  Initializes the vertex shader and the input layout
                GetVertexShader
                  Returns the vertex shader
                GetVertexLayout
                  Returns the vertex input layout
                Game
                  Constructor.
                ~Game
                  Destructor.
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    class VertexShader : public Shader
    {
    public:
        VertexShader() = delete;
        VertexShader(_In_ PCWSTR pszFileName, _In_ PCSTR pszEntryPoint, _In_ PCSTR pszShaderModel);
        VertexShader(const VertexShader& other) = delete;
        VertexShader(VertexShader&& other) = delete;
        VertexShader& operator=(const VertexShader& other) = delete;
        VertexShader& operator=(VertexShader&& other) = delete;
        virtual ~VertexShader() = default;

        virtual HRESULT Initialize(_In_ ID3D11Device* pDevice) override;

        ComPtr<ID3D11VertexShader>& GetVertexShader();
        ComPtr<ID3D11InputLayout>& GetVertexLayout();

    protected:
        ComPtr<ID3D11VertexShader> m_vertexShader;
        ComPtr<ID3D11InputLayout> m_vertexLayout;
    };
}