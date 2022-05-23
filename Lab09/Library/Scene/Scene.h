/*+===================================================================
  File:      V0XEL.H

  Summary:   Voxel header file contains declarations of Voxel class
             used for the lab samples of Game Graphics Programming
             course.

  Classes: Voxel

  ?2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include <fstream>

#include "Model/Model.h"
#include "Light/PointLight.h"
#include "Renderer/Renderable.h"
#include "Scene/Voxel.h"

namespace library
{
    class Scene
    {
    public:
        static FLOAT GetPerlin2d(FLOAT x, FLOAT y, FLOAT frequency, UINT uDepth);

        Scene() = delete;
        Scene(const std::filesystem::path& filePath);
        Scene(const Scene& other) = delete;
        Scene(Scene&& other) = delete;
        Scene& operator=(const Scene& other) = delete;
        Scene& operator=(Scene&& other) = delete;
        virtual ~Scene() = default;

        virtual HRESULT Initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext);

        HRESULT AddVoxel(_In_ const std::shared_ptr<Voxel>& voxel);
        HRESULT AddRenderable(_In_ PCWSTR pszRenderableName, _In_ const std::shared_ptr<Renderable>& renderable);
        HRESULT AddModel(_In_ PCWSTR pszModelName, _In_ const std::shared_ptr<Model>& pModel);
        HRESULT AddPointLight(_In_ size_t index, _In_ const std::shared_ptr<PointLight>& pPointLight);
        HRESULT AddVertexShader(_In_ PCWSTR pszVertexShaderName, _In_ const std::shared_ptr<VertexShader>& vertexShader);
        HRESULT AddPixelShader(_In_ PCWSTR pszPixelShaderName, _In_ const std::shared_ptr<PixelShader>& pixelShader);
        HRESULT AddMaterial(_In_ const std::shared_ptr<Material>& material);

        void Update(_In_ FLOAT deltaTime);

        std::vector<std::shared_ptr<Voxel>>& GetVoxels();
        std::unordered_map<std::wstring, std::shared_ptr<Renderable>>& GetRenderables();
        std::unordered_map<std::wstring, std::shared_ptr<Model>>& GetModels();
        std::shared_ptr<PointLight>& GetPointLight(_In_ size_t index);
        std::unordered_map<std::wstring, std::shared_ptr<VertexShader>>& GetVertexShaders();
        std::unordered_map<std::wstring, std::shared_ptr<PixelShader>>& GetPixelShaders();
        std::unordered_map<std::wstring, std::shared_ptr<Material>>& GetMaterials();

        const std::filesystem::path& GetFilePath() const;
        PCWSTR GetFileName() const;

        HRESULT SetVertexShaderOfRenderable(_In_ PCWSTR pszRenderableName, _In_ PCWSTR pszVertexShaderName);
        HRESULT SetPixelShaderOfRenderable(_In_ PCWSTR pszRenderableName, _In_ PCWSTR pszPixelShaderName);

        HRESULT SetVertexShaderOfModel(_In_ PCWSTR pszModelName, _In_ PCWSTR pszVertexShaderName);
        HRESULT SetPixelShaderOfModel(_In_ PCWSTR pszModelName, _In_ PCWSTR pszPixelShaderName);

        HRESULT SetVertexShaderOfVoxel(_In_ PCWSTR pszVertexShaderName);
        HRESULT SetPixelShaderOfVoxel(_In_ PCWSTR pszPixelShaderName);
        HRESULT SetMaterialOfVoxel(_In_ PCWSTR pszMaterialName);


    private:
        static FLOAT getNoise2(UINT x, UINT y);
        static FLOAT getNoise2d(FLOAT x, FLOAT y);
        static FLOAT lerp(FLOAT x, FLOAT y, FLOAT s);
        static FLOAT smoothLerp(FLOAT x, FLOAT y, FLOAT s);

    private:
        static constexpr const UINT ms_aHashes[] =
        {
            208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
            185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
            9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
            70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
            203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
            164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
            228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
            232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
            193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
            101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
            135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
            114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219
        };

    private:
        std::filesystem::path m_filePath;
        std::vector<std::shared_ptr<Voxel>> m_voxels;
        std::unordered_map<std::wstring, std::shared_ptr<Renderable>> m_renderables;
        std::unordered_map<std::wstring, std::shared_ptr<Model>> m_models;
        std::shared_ptr<PointLight> m_aPointLights[NUM_LIGHTS];
        std::unordered_map<std::wstring, std::shared_ptr<VertexShader>> m_vertexShaders;
        std::unordered_map<std::wstring, std::shared_ptr<PixelShader>> m_pixelShaders;
        std::unordered_map<std::wstring, std::shared_ptr<Material>> m_materials;
    };
}