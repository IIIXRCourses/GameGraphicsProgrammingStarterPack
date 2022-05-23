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
struct aiAnimation;
struct aiBone;
struct aiNode;
struct aiNodeAnim;

namespace Assimp
{
    class Importer;
}

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

        ComPtr<ID3D11Buffer>& GetAnimationBuffer();
        ComPtr<ID3D11Buffer>& GetSkinningConstantBuffer();

        virtual UINT GetNumVertices() const override;
        virtual UINT GetNumIndices() const override;

        std::vector<XMMATRIX>& GetBoneTransforms();
        const std::unordered_map<std::string, UINT>& GetBoneNameToIndexMap() const;

    protected:
        struct VertexBoneData
        {
            VertexBoneData()
                : aBoneIds{ 0u, }
                , aWeights{ 0.0f, }
                , uNumBones(0u)
            {
                ZeroMemory(aBoneIds, ARRAYSIZE(aBoneIds) * sizeof(aBoneIds[0]));
                ZeroMemory(aWeights, ARRAYSIZE(aWeights) * sizeof(aWeights[0]));
            }

            void AddBoneData(_In_ UINT uBoneId, _In_ FLOAT weight)
            {
                assert(uNumBones < ARRAYSIZE(aBoneIds));

                aBoneIds[uNumBones] = uBoneId;
                aWeights[uNumBones] = weight;

                static CHAR szDebugMessage[256];
                sprintf_s(szDebugMessage, "\t\t\tBone %d, weight: %f, index %u\n", uBoneId, weight, uNumBones);
                OutputDebugStringA(szDebugMessage);

                ++uNumBones;
            }

            UINT aBoneIds[MAX_NUM_BONES_PER_VERTEX];
            FLOAT aWeights[MAX_NUM_BONES_PER_VERTEX];
            UINT uNumBones;
        };

        struct BoneInfo
        {
            BoneInfo() = default;
            BoneInfo(const XMMATRIX& Offset)
                : OffsetMatrix(Offset)
                , FinalTransformation()
            {
            }

            XMMATRIX OffsetMatrix;
            XMMATRIX FinalTransformation;
        };

        void countVerticesAndIndices(_Inout_ UINT& uOutNumVertices, _Inout_ UINT& uOutNumIndices, _In_ const aiScene* pScene);
        const aiNodeAnim* findNodeAnimOrNull(_In_ const aiAnimation* pAnimation, _In_ PCSTR pszNodeName);
        UINT findPosition(_In_ FLOAT animationTimeTicks, _In_ const aiNodeAnim* pNodeAnim);
        UINT findRotation(_In_ FLOAT animationTimeTicks, _In_ const aiNodeAnim* pNodeAnim);
        UINT findScaling(_In_ FLOAT animationTimeTicks, _In_ const aiNodeAnim* pNodeAnim);
        UINT getBoneId(_In_ const aiBone* pBone);
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
        void initMeshBones(_In_ UINT uMeshIndex, _In_ const aiMesh* pMesh);
        void initMeshSingleBone(_In_ UINT uBoneIndex, _In_ const aiBone* pBone);
        void initSingleMesh(_In_ UINT uMeshIndex, _In_ const aiMesh* pMesh);
        void interpolatePosition(_Inout_ XMFLOAT3& outTranslate, _In_ FLOAT animationTimeTicks, _In_ const aiNodeAnim* pNodeAnim);
        void interpolateRotation(_Inout_ XMVECTOR& outQuaternion, _In_ FLOAT animationTimeTicks, _In_ const aiNodeAnim* pNodeAnim);
        void interpolateScaling(_Inout_ XMFLOAT3& outScale, _In_ FLOAT animationTimeTicks, _In_ const aiNodeAnim* pNodeAnim);
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
        HRESULT loadNormalTexture(
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
        void readNodeHierarchy(_In_ FLOAT animationTimeTicks, _In_ const aiNode* pNode, _In_ const XMMATRIX& parentTransform);
        void reserveSpace(_In_ UINT uNumVertices, _In_ UINT uNumIndices);

    protected:
        static std::unique_ptr<Assimp::Importer> sm_pImporter;

    protected:
        std::filesystem::path m_filePath;

        ComPtr<ID3D11Buffer> m_animationBuffer;
        ComPtr<ID3D11Buffer> m_skinningConstantBuffer;

        std::vector<SimpleVertex> m_aVertices;
        std::vector<AnimationData> m_aAnimationData;
        std::vector<WORD> m_aIndices;
        std::vector<VertexBoneData> m_aBoneData;
        std::vector<BoneInfo> m_aBoneInfo;
        std::vector<XMMATRIX> m_aTransforms;
        std::unordered_map<std::string, UINT> m_boneNameToIndexMap;

        const aiScene* m_pScene;

        float m_timeSinceLoaded;

        XMMATRIX m_globalInverseTransform;

        //BYTE m_padding[8];
    };
}