#include "Scene/Scene.h"

#include "Shader/SkyMapVertexShader.h"

namespace library
{
    FLOAT Scene::GetPerlin2d(FLOAT x, FLOAT y, FLOAT frequency, UINT uDepth)
    {
        FLOAT xa = x * frequency;
        FLOAT ya = y * frequency;
        FLOAT amp = 1.0f;
        FLOAT fin = 0.0f;
        FLOAT div = 0.0f;

        for (UINT i = 0; i < uDepth; ++i)
        {
            div += 256.0f * amp;
            fin += getNoise2d(xa, ya) * amp;
            amp /= 2.0f;
            xa *= 2.0f;
            ya *= 2.0f;
        }

        return fin / div;
    }

    Scene::Scene(const std::filesystem::path& filePath)
        : m_filePath(filePath)
        , m_voxels()
        , m_renderables()
        , m_aPointLights{ nullptr, nullptr }
        , m_vertexShaders()
        , m_pixelShaders()
        , m_skyBox()
    {
        std::ifstream inputFile;
        inputFile.open(m_filePath.string());

        std::string trash;
        UINT aDimension[4] = { 0u, };
        UINT uDimensionIdx = 0u;
        while (!inputFile.eof() && uDimensionIdx < ARRAYSIZE(aDimension))
        {
            inputFile >> aDimension[uDimensionIdx];

            if (inputFile.fail())
            {
                if (inputFile.eof())
                {
                    break;
                }
                inputFile.clear();
                inputFile >> trash;
            }
            else
            {
                ++uDimensionIdx;
            }
        }

        UINT uColorIdx = 0u;
        XMFLOAT4 color;
        while (!inputFile.eof() && uColorIdx < aDimension[3])
        {
            inputFile >> color.x >> color.y >> color.z;

            if (inputFile.fail())
            {
                if (inputFile.eof())
                {
                    break;
                }
                inputFile.clear();
                inputFile >> trash;
            }
            else
            {
                color.w = 1.0f;
                m_voxels.push_back(std::make_shared<Voxel>(color));
                ++uColorIdx;
            }
        }

        std::vector<std::vector<InstanceData>> aInstanceData;
        aInstanceData.reserve(m_voxels.size());
        for (UINT renderableIdx = 0u; renderableIdx < m_voxels.size(); ++renderableIdx)
        {
            aInstanceData.push_back(std::vector<InstanceData>());
            aInstanceData.back().reserve(
                static_cast<size_t>(aDimension[0]) * static_cast<size_t>(aDimension[1]) * static_cast<size_t>(aDimension[2])
            );
        }

        UINT uDepthIdx = 0u;
        UINT uWidthIdx = 0u;
        CHAR voxelType;
        FLOAT height;
        while (!inputFile.eof())
        {
            inputFile >> voxelType >> height;

            if (inputFile.fail())
            {
                if (inputFile.eof())
                {
                    break;
                }
                inputFile.clear();
                inputFile >> trash;
            }
            else if (static_cast<CHAR>(eBlockType::GRASSLAND) <= voxelType && voxelType < static_cast<CHAR>(eBlockType::COUNT))
            {
                for (UINT heightIdx = 0; heightIdx < static_cast<UINT>(static_cast<float>(aDimension[1]) * height); ++heightIdx)
                {
                    aInstanceData[static_cast<size_t>(voxelType) - static_cast<size_t>(eBlockType::GRASSLAND)].push_back(
                        InstanceData
                        {
                            .Transformation = XMMatrixTranslation(
                                2.0f * (static_cast<FLOAT>(uWidthIdx) - static_cast<FLOAT>(aDimension[0]) / 2.0f),
                                2.0f * (static_cast<FLOAT>(heightIdx) - static_cast<FLOAT>(aDimension[1])) + (static_cast<FLOAT>(aDimension[1]) * 0.75f),
                                2.0f * (static_cast<FLOAT>(uDepthIdx) - static_cast<FLOAT>(aDimension[2]) / 2.0f)
                                )
                        }
                    );
                }
                ++uWidthIdx;
                if (uWidthIdx >= aDimension[0])
                {
                    uWidthIdx -= aDimension[0];
                    ++uDepthIdx;

                    if (uDepthIdx >= aDimension[2])
                    {
                        uDepthIdx -= aDimension[2];
                    }
                }
            }
        }

        inputFile.close();

        UINT uVoxelIdx = 0u;
        auto it = m_voxels.begin();
        while (it != m_voxels.end())
        {
            if (aInstanceData[uVoxelIdx].size() <= 0)
            {
                it = m_voxels.erase(it);
            }
            else
            {
                (*it)->SetInstanceData(std::move(aInstanceData[uVoxelIdx]));
                ++it;
            }
            ++uVoxelIdx;
        }
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::Initialize

      Summary:  Initializes the voxels, shaders, renderables, models, 
                and skybox

      Args:     ID3D11Device* pDevice
                  The Direct3D device to create the buffers
                ID3D11DeviceContext* pImmediateContext
                  The Direct3D context to set buffers
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Scene::Initialize definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::AddVoxel

      Summary:  Add a voxel object

      Args:     const std::shared_ptr<Voxel>& voxel
                  Shared pointer to the voxel object

      Modifies: [m_renderables].

      Returns:  HRESULT
                  Status code.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    HRESULT Scene::AddVoxel(_In_ const std::shared_ptr<Voxel>& voxel)
    {
        m_voxels.push_back(voxel);

        return S_OK;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::AddRenderable

      Summary:  Add a renderable object

      Args:     PCWSTR pszRenderableName
                  Key of the renderable object
                const std::shared_ptr<Renderable>& renderable
                  Shared pointer to the renderable object

      Modifies: [m_renderables].

      Returns:  HRESULT
                  Status code.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    HRESULT Scene::AddRenderable(_In_ PCWSTR pszRenderableName, _In_ const std::shared_ptr<Renderable>& renderable)
    {
        if (m_renderables.contains(pszRenderableName))
        {
            return E_FAIL;
        }

        m_renderables[pszRenderableName] = renderable;

        return S_OK;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::AddModel

      Summary:  Add a model object

      Args:     PCWSTR pszModelName
                  Key of the renderable object
                const std::shared_ptr<Model>& model
                  Shared pointer to the model object

      Modifies: [m_models].

      Returns:  HRESULT
                  Status code.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    HRESULT Scene::AddModel(_In_ PCWSTR pszModelName, _In_ const std::shared_ptr<Model>& pModel)
    {
        if (m_models.contains(pszModelName))
        {
            return E_FAIL;
        }

        m_models[pszModelName] = pModel;

        return S_OK;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::AddPointLight

      Summary:  Add a point light object

      Args:     size_t index
                  Index of the point light
                const std::shared_ptr<PointLight>& pointLight
                  Shared pointer to the point light object

      Modifies: [m_aPointLights].

      Returns:  HRESULT
                  Status code.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    HRESULT Scene::AddPointLight(_In_ size_t index, _In_ const std::shared_ptr<PointLight>& pPointLight)
    {
        HRESULT hr = S_OK;

        if (index >= NUM_LIGHTS)
        {
            return E_FAIL;
        }

        m_aPointLights[index] = pPointLight;

        return hr;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::AddVertexShader

      Summary:  Add the vertex shader into the renderer

      Args:     PCWSTR pszVertexShaderName
                  Key of the vertex shader
                const std::shared_ptr<VertexShader>&
                  Vertex shader to add

      Modifies: [m_vertexShaders].

      Returns:  HRESULT
                  Status code
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    HRESULT Scene::AddVertexShader(_In_ PCWSTR pszVertexShaderName, _In_ const std::shared_ptr<VertexShader>& vertexShader)
    {
        if (m_vertexShaders.contains(pszVertexShaderName))
        {
            return E_FAIL;
        }

        m_vertexShaders[pszVertexShaderName] = vertexShader;

        return S_OK;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::AddPixelShader

      Summary:  Add the pixel shader into the renderer

      Args:     PCWSTR pszPixelShaderName
                  Key of the pixel shader
                const std::shared_ptr<PixelShader>&
                  Pixel shader to add

      Modifies: [m_pixelShaders].

      Returns:  HRESULT
                  Status code
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    HRESULT Scene::AddPixelShader(_In_ PCWSTR pszPixelShaderName, _In_ const std::shared_ptr<PixelShader>& pixelShader)
    {
        if (m_pixelShaders.contains(pszPixelShaderName))
        {
            return E_FAIL;
        }

        m_pixelShaders[pszPixelShaderName] = pixelShader;

        return S_OK;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::AddSkyBox

      Summary:  Add the skybox

      Args:     const std::shared_ptr<Skybox>&
                  Skybox to use

      Modifies: [m_skyBox].

      Returns:  HRESULT
                  Status code
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Scene::AddSkyBox definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::Update

      Summary:  Update the renderables, models, point lights, skybox 
                each frame

      Args:     FLOAT deltaTime
                  Time difference of a frame
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Scene::Update definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::GetVoxels

      Summary:  Returns the vector of voxels

      Returns:  std::vector<std::shared_ptr<Voxel>>&
                  Voxels
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    std::vector<std::shared_ptr<Voxel>>& Scene::GetVoxels()
    {
        return m_voxels;
    }


    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::GetRenderables

      Summary:  Returns the vector of renderables

      Returns:  std::unordered_map<std::wstring, std::shared_ptr<Renderable>>&
                  Renderables
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    std::unordered_map<std::wstring, std::shared_ptr<Renderable>>& Scene::GetRenderables()
    {
        return m_renderables;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::GetModels

      Summary:  Returns the vector of models

      Returns:  std::unordered_map<std::wstring, std::shared_ptr<Model>>&
                  Models
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    std::unordered_map<std::wstring, std::shared_ptr<Model>>& Scene::GetModels()
    {
        return m_models;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::GetPointLight

      Summary:  Returns a point light according to the given index

      Args:     size_t index
                  Index of the point light

      Returns:  std::shared_ptr<PointLight>&
                  Point light
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    std::shared_ptr<PointLight>& Scene::GetPointLight(_In_ size_t index)
    {
        assert(index < NUM_LIGHTS);

        return m_aPointLights[index];
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::GetVertexShaders

      Summary:  Returns a hash map of vertex shaders

      Returns:  std::unordered_map<std::wstring, std::shared_ptr<VertexShader>>&
                  Vertex shaders
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    std::unordered_map<std::wstring, std::shared_ptr<VertexShader>>& Scene::GetVertexShaders()
    {
        return m_vertexShaders;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::GetPixelShaders

      Summary:  Returns a hash map of pixel shaders

      Returns:  std::unordered_map<std::wstring, std::shared_ptr<PixelShader>>&
                  Pixel shaders
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    std::unordered_map<std::wstring, std::shared_ptr<PixelShader>>& Scene::GetPixelShaders()
    {
        return m_pixelShaders;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::GetSkyBox

      Summary:  Returns a sky box

      Returns:  std::shared_ptr<Skybox>&
                  Sky box
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: Scene::GetSkyBox definition (remove the comment)
    --------------------------------------------------------------------*/

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::GetFilePath

      Summary:  Returns the file path to the height map

      Returns:  const std::filesystem::path&
                  File path to the height map
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    const std::filesystem::path& Scene::GetFilePath() const
    {
        return m_filePath;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::GetFileName

      Summary:  Returns the file name of the height map

      Returns:  PCWSTR
                  File name of the height map
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    PCWSTR Scene::GetFileName() const
    {
        return m_filePath.c_str();
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::SetVertexShaderOfRenderable

      Summary:  Sets the vertex shader for a renderable

      Args:     PCWSTR pszRenderableName
                  Key of the renderable
                PCWSTR pszVertexShaderName
                  Key of the vertex shader

      Modifies: [m_renderables].

      Returns:  HRESULT
                  Status code
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    HRESULT Scene::SetVertexShaderOfRenderable(_In_ PCWSTR pszRenderableName, _In_ PCWSTR pszVertexShaderName)
    {
        if (!m_renderables.contains(pszRenderableName) || !m_vertexShaders.contains(pszVertexShaderName))
        {
            return E_FAIL;
        }

        m_renderables[pszRenderableName]->SetVertexShader(m_vertexShaders[pszVertexShaderName]);

        return S_OK;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::SetPixelShaderOfRenderable

      Summary:  Sets the pixel shader for a renderable

      Args:     PCWSTR pszRenderableName
                  Key of the renderable
                PCWSTR pszPixelShaderName
                  Key of the pixel shader

      Modifies: [m_renderables].

      Returns:  HRESULT
                  Status code
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    HRESULT Scene::SetPixelShaderOfRenderable(_In_ PCWSTR pszRenderableName, _In_ PCWSTR pszPixelShaderName)
    {
        if (!m_renderables.contains(pszRenderableName) || !m_pixelShaders.contains(pszPixelShaderName))
        {
            return E_FAIL;
        }

        m_renderables[pszRenderableName]->SetPixelShader(m_pixelShaders[pszPixelShaderName]);

        return S_OK;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::SetVertexShaderOfModel

      Summary:  Sets the vertex shader for a model

      Args:     PCWSTR pszModelName
                  Key of the renderable
                PCWSTR pszVertexShaderName
                  Key of the vertex shader

      Modifies: [m_models].

      Returns:  HRESULT
                  Status code
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    HRESULT Scene::SetVertexShaderOfModel(_In_ PCWSTR pszModelName, _In_ PCWSTR pszVertexShaderName)
    {
        if (!m_models.contains(pszModelName) || !m_vertexShaders.contains(pszVertexShaderName))
        {
            return E_FAIL;
        }

        m_models[pszModelName]->SetVertexShader(m_vertexShaders[pszVertexShaderName]);

        return S_OK;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::SetPixelShaderOfModel

      Summary:  Sets the pixel shader for a model

      Args:     PCWSTR pszModelName
                  Key of the renderable
                PCWSTR pszPixelShaderName
                  Key of the pixel shader

      Modifies: [m_models].

      Returns:  HRESULT
                  Status code
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    HRESULT Scene::SetPixelShaderOfModel(_In_ PCWSTR pszModelName, _In_ PCWSTR pszPixelShaderName)
    {
        if (!m_models.contains(pszModelName) || !m_pixelShaders.contains(pszPixelShaderName))
        {
            return E_FAIL;
        }

        m_models[pszModelName]->SetPixelShader(m_pixelShaders[pszPixelShaderName]);

        return S_OK;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::SetVertexShaderOfScene

      Summary:  Sets the vertex shader for the voxels in a scene

      Args:     PCWSTR pszSceneName
                  Key of the scene
                PCWSTR pszVertexShaderName
                  Key of the vertex shader

      Modifies: [m_scenes].

      Returns:  HRESULT
                  Status code
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    HRESULT Scene::SetVertexShaderOfVoxel(_In_ PCWSTR pszVertexShaderName)
    {
        if (!m_vertexShaders.contains(pszVertexShaderName))
        {
            return E_FAIL;
        }

        for (std::shared_ptr<Voxel>& voxel : m_voxels)
        {
            voxel->SetVertexShader(m_vertexShaders[pszVertexShaderName]);
        }

        return S_OK;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Scene::SetPixelShaderOfScene

      Summary:  Sets the pixel shader for the voxels in a scene

      Args:     PCWSTR pszRenderableName
                  Key of the renderable
                PCWSTR pszPixelShaderName
                  Key of the pixel shader

      Modifies: [m_renderables].

      Returns:  HRESULT
                  Status code
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    HRESULT Scene::SetPixelShaderOfVoxel(_In_ PCWSTR pszPixelShaderName)
    {
        if (!m_pixelShaders.contains(pszPixelShaderName))
        {
            return E_FAIL;
        }

        for (std::shared_ptr<Voxel>& voxel : m_voxels)
        {
            voxel->SetPixelShader(m_pixelShaders[pszPixelShaderName]);
        }

        return S_OK;
    }

    FLOAT Scene::getNoise2(UINT x, UINT y)
    {
        UINT temp = ms_aHashes[y % 256u];

        return static_cast<FLOAT>(ms_aHashes[(temp + x) % 256u]);
    }

    FLOAT Scene::getNoise2d(FLOAT x, FLOAT y)
    {
        UINT uX = static_cast<UINT>(x);
        UINT uY = static_cast<UINT>(y);
        FLOAT xFrac = x - static_cast<FLOAT>(uX);
        FLOAT yFrac = y - static_cast<FLOAT>(uY);

        UINT s = static_cast<UINT>(getNoise2(uX, uY));
        UINT t = static_cast<UINT>(getNoise2(uX + 1u, uY));
        UINT u = static_cast<UINT>(getNoise2(uX, uY + 1u));
        UINT v = static_cast<UINT>(getNoise2(uX + 1u, uY + 1u));

        FLOAT low = smoothLerp(static_cast<FLOAT>(s), static_cast<FLOAT>(t), xFrac);
        FLOAT high = smoothLerp(static_cast<FLOAT>(u), static_cast<FLOAT>(v), xFrac);

        return smoothLerp(low, high, yFrac);
    }

    FLOAT Scene::lerp(FLOAT x, FLOAT y, FLOAT s)
    {
        return x + s * (y - x);
    }

    FLOAT Scene::smoothLerp(FLOAT x, FLOAT y, FLOAT s)
    {
        return lerp(x, y, s * s * (3.0f - 2.0f * s));
    }
}