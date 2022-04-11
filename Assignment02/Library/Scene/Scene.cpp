#include "Scene/Scene.h"

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

    HRESULT Scene::Initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext)
    {
        for (auto voxel : m_voxels)
        {
            HRESULT hr = voxel->Initialize(pDevice, pImmediateContext);
            if (FAILED(hr))
            {
                return hr;
            }
        }

        return S_OK;
    }
    
    std::vector<std::shared_ptr<Voxel>>& Scene::GetVoxels()
    {
        return m_voxels;
    }
    
    const std::filesystem::path& Scene::GetFilePath() const
    {
        return m_filePath;
    }
    
    PCWSTR Scene::GetFileName() const
    {
        return m_filePath.c_str();
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