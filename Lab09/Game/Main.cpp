/*+===================================================================
  File:      MAIN.CPP

  Summary:   This application demonstrates creating a Direct3D 11 device

  Origin:    http://msdn.microsoft.com/en-us/library/windows/apps/ff729718.aspx

  Originally created by Microsoft Corporation under MIT License
  ?2022 Kyung Hee University
===================================================================+*/

#include "Common.h"

#include <cstdio>
#include <fstream>
#include <memory>

#include "Game/Game.h"
#include "Light/RotatingPointLight.h"
#include "Model/Model.h"
#include "Scene/Scene.h"
#include "Scene/Voxel.h"
#include "Cube/Cube.h"
#include "Shader/SkinningVertexShader.h"

/*F+F+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: wWinMain

  Summary:  Entry point to the program. Initializes everything and
            goes into a message processing loop. Idle time is used to
            render the scene.

  Args:     HINSTANCE hInstance
              Handle to an instance.
            HINSTANCE hPrevInstance
              Has no meaning.
            LPWSTR lpCmdLine
              Contains the command-line arguments as a Unicode
              string
            INT nCmdShow
              Flag that says whether the main application window
              will be minimized, maximized, or shown normally

  Returns:  INT
              Status code.
-----------------------------------------------------------------F-F*/
INT WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ INT nCmdShow)
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    std::unique_ptr<library::Game> game = std::make_unique<library::Game>(L"Game Graphics Programming Lab 9: Normal Mapping");

    std::ofstream sceneFile;
    sceneFile.open("HeightMap.txt");
    constexpr const UINT MAP_WIDTH = 256u;
    constexpr const UINT MAP_HEIGHT = 32u;
    constexpr const UINT MAP_DEPTH = 256u;
    XMFLOAT4 aColors[] =
    {
        XMFLOAT4(0.0f,      0.666f, 0.0f,   1.0f),  // GRASSLAND
        XMFLOAT4(1.0f,      1.0f,   1.0f,   1.0f),  // SNOW
        XMFLOAT4(0.0f,      0.0f,   0.666f, 1.0f),  // OCEAN
        XMFLOAT4(1.0f,      0.666f, 0.0f,   1.0f),  // SAND
        XMFLOAT4(0.666f,    0.0f,   0.0f,   1.0f),  // SCORCHED
        XMFLOAT4(0.956f,    0.643f, 0.376f, 1.0f),  // BARE
        XMFLOAT4(0.941f,    0.0f,   1.0f,   1.0f),  // TUNDRA
        XMFLOAT4(0.803f,    0.521f, 0.247f, 1.0f),  // TEMPERATE_DESERT
        XMFLOAT4(0.42f,     0.556f, 0.137f, 1.0f),  // SHRUBLAND
        XMFLOAT4(0.0f,      0.392f, 0.0f,   1.0f),  // TAIGA
        XMFLOAT4(1.0f,      0.55f,  0.0f,   1.0f),  // TEMPERATE_DECIDUOUS_FOREST
        XMFLOAT4(0.0f,      0.5f,   0.0f,   1.0f),  // TEMPERATE_RAIN_FOREST
        XMFLOAT4(0.956f,    0.643f, 0.376f, 1.0f),  // SUBTROPICAL_DESERT
        XMFLOAT4(0.133f,    0.545f, 0.133f, 1.0f),  // TROPICAL_SEASONAL_FOREST
        XMFLOAT4(0.15f,     0.372f, 0.15f,  1.0f),  // TROPICAL_RAIN_FOREST
    };

    sceneFile << MAP_WIDTH << " " << MAP_HEIGHT << " " << MAP_DEPTH << ' ' << ARRAYSIZE(aColors) << '\n';

    for (UINT colorIdx = 0; colorIdx < ARRAYSIZE(aColors); ++colorIdx)
    {
        sceneFile << aColors[colorIdx].x << ' ' <<
            aColors[colorIdx].y << ' ' <<
            aColors[colorIdx].z << '\n';
    }

    for (UINT z = 0u; z < MAP_DEPTH; ++z)
    {
        for (UINT x = 0u; x < MAP_WIDTH; ++x)
        {
            FLOAT height = 0.0f;

            FLOAT frequencySum = 0.0f;
            for (UINT i = 0; i < 4; ++i)
            {
                FLOAT frequency = pow(2.0f, static_cast<FLOAT>(i));
                frequencySum += 1.0f / frequency;
                height += library::Scene::GetPerlin2d(frequency * static_cast<FLOAT>(x), frequency * static_cast<FLOAT>(z), 0.1f, 4u) / frequency;
            }
            height /= frequencySum;
            height = pow(height * 1.2f, 1.25f);

            assert(height >= 0.0f);

            FLOAT moisture = 0.0f;

            frequencySum = 0.0f;
            for (UINT i = 0; i < 4; ++i)
            {
                FLOAT frequency = pow(2.0f, static_cast<FLOAT>(i));
                frequencySum += 1.0f / frequency;
                moisture += library::Scene::GetPerlin2d(frequency * static_cast<FLOAT>(x), frequency * static_cast<FLOAT>(z), 0.1f, 4u) / frequency;
            }
            moisture /= frequencySum;
            moisture = pow(moisture * 1.2f, 1.25f);

            library::eBlockType blockType = library::eBlockType::GRASSLAND;

            if (height < 0.1f)
            {
                blockType = library::eBlockType::OCEAN;
            }
            else if (height < 0.12f)
            {
                blockType = library::eBlockType::SAND;
            }
            else if (height > 0.8f)
            {
                if (moisture < 0.1f)
                {
                    blockType = library::eBlockType::SCORCHED;
                }
                else if (moisture < 0.2f)
                {
                    blockType = library::eBlockType::BARE;
                }
                else if (moisture < 0.5f)
                {
                    blockType = library::eBlockType::TUNDRA;
                }
                else
                {
                    blockType = library::eBlockType::SNOW;
                }
            }
            else if (height > 0.6f)
            {
                if (moisture < 0.33f)
                {
                    blockType = library::eBlockType::TEMPERATE_DESERT;
                }
                else if (moisture < 0.66f)
                {
                    blockType = library::eBlockType::SHRUBLAND;
                }
                else
                {
                    blockType = library::eBlockType::TAIGA;
                }
            }
            else if (height > 0.3f)
            {
                if (moisture < 0.16f)
                {
                    blockType = library::eBlockType::TEMPERATE_DESERT;
                }
                else if (moisture < 0.5f)
                {
                    blockType = library::eBlockType::GRASSLAND;
                }
                else if (moisture < 0.83f)
                {
                    blockType = library::eBlockType::TEMPERATE_DECIDUOUS_FOREST;
                }
                else
                {
                    blockType = library::eBlockType::TEMPERATE_RAIN_FOREST;
                }
            }
            else
            {

                if (moisture < 0.16f)
                {
                    blockType = library::eBlockType::SUBTROPICAL_DESERT;
                }
                else if (moisture < 0.33f)
                {
                    blockType = library::eBlockType::GRASSLAND;
                }
                else if (moisture < 0.66f)
                {
                    blockType = library::eBlockType::TROPICAL_SEASONAL_FOREST;
                }
                else
                {
                    blockType = library::eBlockType::TROPICAL_RAIN_FOREST;
                }
            }

            sceneFile << static_cast<CHAR>(blockType);

            sceneFile << height << ' ';
        }
        sceneFile << '\n';
    }
    sceneFile << std::endl;
    sceneFile.close();

    std::shared_ptr<library::Scene> mainScene = std::make_shared<library::Scene>(L"HeightMap.txt");

    // Phong Skinning
    std::shared_ptr<library::SkinningVertexShader> phongSkinningVertexShader = std::make_shared<library::SkinningVertexShader>(L"Shaders/SkinningShaders.fxh", "VSPhong", "vs_5_0");
    if (FAILED(mainScene->AddVertexShader(L"PhongSkinningShader", phongSkinningVertexShader)))
    {
        return 0;
    }
    // Phong
    std::shared_ptr<library::VertexShader> phongVertexShader = std::make_shared<library::VertexShader>(L"Shaders/PhongShaders.fxh", "VSPhong", "vs_5_0");
    if (FAILED(mainScene->AddVertexShader(L"PhongShader", phongVertexShader)))
    {
        return 0;
    }
    // Voxel
    std::shared_ptr<library::VertexShader> voxelVertexShader = std::make_shared<library::VertexShader>(L"Shaders/VoxelShaders.fxh", "VSVoxel", "vs_5_0");
    if (FAILED(mainScene->AddVertexShader(L"VoxelShader", voxelVertexShader)))
    {
        return 0;
    }

    // Phong Skinning
    std::shared_ptr<library::PixelShader> phongSkinningPixelShader = std::make_shared<library::PixelShader>(L"Shaders/SkinningShaders.fxh", "PSPhong", "ps_5_0");
    if (FAILED(mainScene->AddPixelShader(L"PhongSkinningShader", phongSkinningPixelShader)))
    {
        return 0;
    }
    // Phong
    std::shared_ptr<library::PixelShader> phongPixelShader = std::make_shared<library::PixelShader>(L"Shaders/PhongShaders.fxh", "PSPhong", "ps_5_0");
    if (FAILED(mainScene->AddPixelShader(L"PhongShader", phongPixelShader)))
    {
        return 0;
    }
    // Voxel
    std::shared_ptr<library::PixelShader> voxelPixelShader = std::make_shared<library::PixelShader>(L"Shaders/VoxelShaders.fxh", "PSVoxel", "ps_5_0");
    if (FAILED(mainScene->AddPixelShader(L"VoxelShader", voxelPixelShader)))
    {
        return 0;
    }

    // Load Material
    std::shared_ptr<library::Model> cyborg = std::make_shared<library::Model>(L"Content/cyborg/cyborg.obj");
    cyborg->Translate(XMVectorSet(0.0f, 5.0f, 5.0f, 0.0f));
    if (FAILED(mainScene->AddModel(L"Cyborg", cyborg)))
    {
        return 0;
    }
    if (FAILED(mainScene->SetVertexShaderOfModel(L"Cyborg", L"PhongShader")))
    {
        return 0;
    }
    if (FAILED(mainScene->SetPixelShaderOfModel(L"Cyborg", L"PhongShader")))
    {
        return 0;
    }


    std::shared_ptr<library::Material> voxelMaterial = std::make_shared<library::Material>(L"VoxelMaterial");
    voxelMaterial->pDiffuse = std::make_shared<library::Texture>("Content/Cube/diffuse.png");
    voxelMaterial->pNormal = std::make_shared<library::Texture>("Content/Cube/normal.png");

    if (FAILED(mainScene->AddMaterial(voxelMaterial)))
    {
        return 0;
    }

    if (FAILED(mainScene->SetVertexShaderOfVoxel(L"VoxelShader")))
    {
        return 0;
    }

    if (FAILED(mainScene->SetPixelShaderOfVoxel(L"VoxelShader")))
    {
        return 0;
    }

    if (FAILED(mainScene->SetMaterialOfVoxel(L"VoxelMaterial")))
    {
        return 0;
    }

    XMFLOAT4 color;
    XMStoreFloat4(&color, Colors::White);

    std::shared_ptr<library::PointLight> directionalLight = std::make_shared<library::PointLight>(
        XMFLOAT4(-5.77f, 5.77f, -5.77f, 1.0f),
        color
        );
    if (FAILED(mainScene->AddPointLight(0, directionalLight)))
    {
        return 0;
    }

    XMStoreFloat4(&color, Colors::White);
    std::shared_ptr<RotatingPointLight> rotatingDirectionalLight = std::make_shared<RotatingPointLight>(
        XMFLOAT4(0.0f, 0.0f, -5.0f, 1.0f),
        color
        );

    if (FAILED(mainScene->AddPointLight(1, rotatingDirectionalLight)))
    {
        return 0;
    }

    if (FAILED(game->GetRenderer()->AddScene(L"VoxelMap", mainScene)))
    {
        return 0;
    }

    if (FAILED(game->GetRenderer()->SetMainScene(L"VoxelMap")))
    {
        return 0;
    }

    if (FAILED(game->Initialize(hInstance, nCmdShow)))
    {
        return 0;
    }

    return game->Run();
}