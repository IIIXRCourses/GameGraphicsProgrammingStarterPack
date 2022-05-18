/*+===================================================================
  File:      SKYBOX.H

  Summary:   Skybox header file contains declarations of Skybox class
             used for the lab samples of Game Graphics Programming
             course.

  Classes: Skybox

  © 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Model/Model.h"

namespace library
{
    class Skybox : public Model
    {
    public:
        Skybox(_In_ const std::filesystem::path& cubeMapFilePath, _In_ FLOAT scale);
        Skybox(const Skybox& other) = delete;
        Skybox(Skybox&& other) = delete;
        Skybox& operator=(const Skybox& other) = delete;
        Skybox& operator=(Skybox&& other) = delete;
        ~Skybox() = default;

        virtual HRESULT Initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext) override;
        //virtual void Update(_In_ FLOAT deltaTime, _In_ const XMVECTOR& lightPosition);

        const std::shared_ptr<Texture>& GetSkyboxTexture() const;

    protected:
        virtual void initSingleMesh(_In_ UINT uMeshIndex, _In_ const aiMesh* pMesh) override;

    protected:
        std::filesystem::path m_cubeMapFileName;
        FLOAT m_scale;
    };
}