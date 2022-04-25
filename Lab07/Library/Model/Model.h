/*+===================================================================
  File:      MODEL.H

  Summary:   Model header file contains declarations of
             Model class used for the lab samples of Game
             Graphics Programming course.

  Classes: Model

  ?2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Renderer/DataTypes.h"
#include "Renderer/Renderable.h"
#include "Shader/PixelShader.h"
#include "Shader/VertexShader.h"
#include "Texture/Material.h"

struct aiScene;
struct aiMesh;
struct aiMaterial;

namespace library
{
    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    Model

      Summary:  Model class is a renderable from model files

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
                Model
                  Constructor.
                ~Model
                  Destructor.
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    class Model : public Renderable
    {
    public:
        Model() = delete;
        Model(_In_ const std::filesystem::path& filePath);
        Model(const Model& other) = delete;
        Model(Model&& other) = delete;
        Model& operator=(const Model& other) = delete;
        Model& operator=(Model&& other) = delete;
        virtual ~Model() = default;

        virtual HRESULT Initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext);
        virtual void Update(_In_ FLOAT deltaTime) override;

        virtual UINT GetNumVertices() const override;
        virtual UINT GetNumIndices() const override;

    protected:
        void countVerticesAndIndices(_Inout_ UINT& uOutNumVertices, _Inout_ UINT& uOutNumIndices, _In_ const aiScene* pScene);
        const virtual SimpleVertex* getVertices() const override;
        virtual const WORD* getIndices() const override;
        void initAllMeshes(_In_ const aiScene* pScene);
        HRESULT initFromScene(
            _In_ ID3D11Device* pDevice,
            _In_ ID3D11DeviceContext* pImmediateContext,
            _In_ const aiScene* pScene,
            _In_ const std::filesystem::path& filePath
            );
        HRESULT initMaterials(
            _In_ ID3D11Device* pDevice,
            _In_ ID3D11DeviceContext* pImmediateContext,
            _In_ const aiScene* pScene,
            _In_ const std::filesystem::path& filePath
            );
        void initSingleMesh(_In_ const aiMesh* pMesh);
        void loadColors(_In_ const aiMaterial* pMaterial, _In_ UINT uIndex);
        HRESULT loadDiffuseTexture(
            _In_ ID3D11Device* pDevice,
            _In_ ID3D11DeviceContext* pImmediateContext,
            _In_ const std::filesystem::path& parentDirectory,
            _In_ const aiMaterial* pMaterial,
            _In_ UINT uIndex
            );
        HRESULT loadSpecularTexture(
            _In_ ID3D11Device* pDevice,
            _In_ ID3D11DeviceContext* pImmediateContext,
            _In_ const std::filesystem::path& parentDirectory,
            _In_ const aiMaterial* pMaterial,
            _In_ UINT uIndex
            );
        HRESULT loadTextures(
            _In_ ID3D11Device* pDevice,
            _In_ ID3D11DeviceContext* pImmediateContext,
            _In_ const std::filesystem::path& parentDirectory,
            _In_ const aiMaterial* pMaterial,
            _In_ UINT uIndex
        );
        void reserveSpace(_In_ UINT uNumVertices, _In_ UINT uNumIndices);

    protected:
        std::filesystem::path m_filePath;

        std::vector<SimpleVertex> m_aVertices;
        std::vector<WORD> m_aIndices;

        BYTE m_padding[8];
    };
}