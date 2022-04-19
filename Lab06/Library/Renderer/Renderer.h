/*+===================================================================
  File:      RENDERER.H

  Summary:   Renderer header file contains declarations of Renderer 
             class used for the lab samples of Game Graphics 
             Programming course.

  Classes: Renderer

  © 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Camera/Camera.h"
#include "Light/PointLight.h"
#include "Renderer/DataTypes.h"
#include "Renderer/Renderable.h"
#include "Shader/PixelShader.h"
#include "Shader/VertexShader.h"
#include "Window/MainWindow.h"

namespace library
{
    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    Renderer

      Summary:  Renderer initializes Direct3D, and renders renderable
                data onto the screen

      Methods:  Initialize
                  Creates Direct3D device and swap chain
                AddRenderable
                  Add a renderable object and initialize the object
                AddVertexShader
                  Add the vertex shader into the renderer
                AddPixelShader
                  Add the pixel shader into the renderer
                GetVertexLayout
                  Returns the vertex input layout
                GetVertexBuffer
                  Returns the vertex buffer
                GetIndexBuffer
                  Returns the index buffer
                GetConstantBuffer
                  Returns the constant buffer
                GetWorldMatrix
                  Returns the world matrix
                GetTextureResourceView
                  Returns the texture resource view
                GetSamplerState
                  Returns the sampler state
                GetOutputColor
                  Returns the output color
                HasTexture
                  Returns whether texture
                HandleInput
                  Handles the keyboard / mouse input
                Update
                  Update the renderables each frame
                Render
                  Renders the frame
                SetVertexShaderOfRenderable
                  Sets the vertex shader for a renderable
                SetPixelShaderOfRenderable
                  Sets the pixel shader for a renderable
                GetDriverType
                  Returns the Direct3D driver type
                Renderer
                  Constructor.
                ~Renderer
                  Destructor.
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    class Renderable
    {
    public:
        Renderable(_In_ const std::filesystem::path& textureFilePath);
        Renderable(_In_ const XMFLOAT4& outputColor);
        Renderable(const Renderable& other) = delete;
        Renderable(Renderable&& other) = delete;
        Renderable& operator=(const Renderable& other) = delete;
        Renderable& operator=(Renderable&& other) = delete;
        virtual ~Renderable() = default;

        virtual HRESULT Initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext) = 0;
        virtual void Update(_In_ FLOAT deltaTime) = 0;

        void SetVertexShader(_In_ const std::shared_ptr<VertexShader>& vertexShader);
        void SetPixelShader(_In_ const std::shared_ptr<PixelShader>& pixelShader);

        ComPtr<ID3D11VertexShader>& GetVertexShader();
        ComPtr<ID3D11PixelShader>& GetPixelShader();
        ComPtr<ID3D11InputLayout>& GetVertexLayout();
        ComPtr<ID3D11Buffer>& GetVertexBuffer();
        ComPtr<ID3D11Buffer>& GetIndexBuffer();
        ComPtr<ID3D11Buffer>& GetConstantBuffer();
        const XMMATRIX& GetWorldMatrix() const;
        ComPtr<ID3D11ShaderResourceView>& GetTextureResourceView();
        ComPtr<ID3D11SamplerState>& GetSamplerState();
        const XMFLOAT4& GetOutputColor() const;
        BOOL HasTexture() const;

        void RotateX(_In_ FLOAT angle);
        void RotateY(_In_ FLOAT angle);
        void RotateZ(_In_ FLOAT angle);
        void RotateRollPitchYaw(_In_ FLOAT roll, _In_ FLOAT pitch, _In_ FLOAT yaw);
        void Scale(_In_ FLOAT scaleX, _In_ FLOAT scaleY, _In_ FLOAT scaleZ);
        void Translate(_In_ const XMVECTOR& offset);

        virtual UINT GetNumVertices() const = 0;
        virtual UINT GetNumIndices() const = 0;
    protected:
        const virtual SimpleVertex* getVertices() const = 0;
        virtual const WORD* getIndices() const = 0;
        HRESULT initialize(
            _In_ ID3D11Device* pDevice,
            _In_ ID3D11DeviceContext* pImmediateContext
            );

        ComPtr<ID3D11Buffer> m_vertexBuffer;
        ComPtr<ID3D11Buffer> m_indexBuffer;
        ComPtr<ID3D11Buffer> m_constantBuffer;
        ComPtr<ID3D11ShaderResourceView> m_textureRV;
        ComPtr<ID3D11SamplerState> m_samplerLinear;
        std::shared_ptr<VertexShader> m_vertexShader;
        std::shared_ptr<PixelShader> m_pixelShader;
        std::filesystem::path m_textureFilePath;
        XMFLOAT4 m_outputColor;
        BOOL m_bHasTextures;
        XMMATRIX m_world;
    };
}