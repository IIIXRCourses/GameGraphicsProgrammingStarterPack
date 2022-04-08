/*+===================================================================
  File:      RENDERABLE.H

  Summary:   Renderable header file contains declarations of
             Renderable class used for the lab samples of Game
             Graphics Programming course.

  Classes: Renderable

  � 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Renderer/DataTypes.h"
#include "Shader/PixelShader.h"
#include "Shader/VertexShader.h"

namespace library
{
    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    Renderable

      Summary:  Base class for all renderable classes

      Methods:  Initialize
                  Pure virtual function that initializes the object
                Update
                  Pure virtual function that updates the object each 
                  frame
                GetVertexBuffer
                  Returns the vertex buffer
                GetIndexBuffer
                  Returns the index buffer
                GetConstantBuffer
                  Returns the constant buffer
                GetWorldMatrix
                  Returns the world matrix
                GetNumVertices
                  Pure virtual function that returns the number of 
                  vertices
                GetNumIndices
                  Pure virtual function that returns the number of 
                  indices
                Renderable
                  Constructor.
                ~Renderable
                  Destructor.
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    class Renderable
    {
    public:
        Renderable() = default;
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

        void RotateX(_In_ FLOAT angle);
        void RotateY(_In_ FLOAT angle);
        void RotateZ(_In_ FLOAT angle);
        void RotateRollPitchYaw(_In_ FLOAT roll, _In_ FLOAT pitch, _In_ FLOAT yaw);
        void Scale(_In_ FLOAT scaleX, _In_ FLOAT scaleY, _In_ FLOAT scaleZ);
        void Translate(_In_ const XMVECTOR& offset);

        virtual UINT GetNumVertices() const = 0;
        virtual UINT GetNumIndices() const = 0;
    protected:
        virtual const SimpleVertex* getVertices() const = 0;
        virtual const WORD* getIndices() const = 0;
        HRESULT initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext);

        ComPtr<ID3D11Buffer> m_vertexBuffer;
        ComPtr<ID3D11Buffer> m_indexBuffer;
        ComPtr<ID3D11Buffer> m_constantBuffer;
        std::shared_ptr<VertexShader> m_vertexShader;
        std::shared_ptr<PixelShader> m_pixelShader;
        BYTE m_padding[8];
        XMMATRIX m_world;
    };
}