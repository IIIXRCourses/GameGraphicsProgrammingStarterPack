/*+===================================================================
  File:      MAIN.CPP

  Summary:   This application demonstrates creating a Direct3D 11 device

  Origin:    http://msdn.microsoft.com/en-us/library/windows/apps/ff729718.aspx

  Originally created by Microsoft Corporation under MIT License
  © 2022 Kyung Hee University
===================================================================+*/

#include "Common.h"

#include <cstdio>
#include <filesystem>
#include <memory>
#include <source_location>

#include "Cube/Cube.h"
#include "Cube/RotatingCube.h"
#include "Light/RotatingPointLight.h"
#include "Game/Game.h"

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

    std::unique_ptr<library::Game> game = std::make_unique<library::Game>(L"Game Graphics Programming Lab 06: Lighting");

    // Phong
    std::shared_ptr<library::VertexShader> phongVertexShader = std::make_shared<library::VertexShader>(L"Shaders/PhongShaders.fxh", "VSPhong", "vs_5_0");
    if (FAILED(game->GetRenderer()->AddVertexShader(L"PhongShader", phongVertexShader)))
    {
        return 0;
    }
    // Light Cube
    std::shared_ptr<library::VertexShader> lightVertexShader = std::make_shared<library::VertexShader>(L"Shaders/PhongShaders.fxh", "VSLightCube", "vs_5_0");
    if (FAILED(game->GetRenderer()->AddVertexShader(L"LightShader", lightVertexShader)))
    {
        return 0;
    }

    // Phong
    std::shared_ptr<library::PixelShader> phongPixelShader = std::make_shared<library::PixelShader>(L"Shaders/PhongShaders.fxh", "PSPhong", "ps_5_0");
    if (FAILED(game->GetRenderer()->AddPixelShader(L"PhongShader", phongPixelShader)))
    {
        return 0;
    }
    // Light Cube
    std::shared_ptr<library::PixelShader> lightPixelShader = std::make_shared<library::PixelShader>(L"Shaders/PhongShaders.fxh", "PSLightCube", "ps_5_0");
    if (FAILED(game->GetRenderer()->AddPixelShader(L"LightShader", lightPixelShader)))
    {
        return 0;
    }

    XMFLOAT4 color;
    XMStoreFloat4(&color, Colors::White);
    std::shared_ptr<library::PointLight> pointLight = std::make_shared<library::PointLight>(
        XMFLOAT4(-5.77f, 5.77f, -5.77f, 1.0f), 
        color
        );
    if (FAILED(game->GetRenderer()->AddPointLight(0u, pointLight)))
    {
        return 0;
    }

    std::shared_ptr<Cube> lightCube = std::make_shared<Cube>(color);
    lightCube->Translate(XMVectorSet(-5.77f, 5.77f, -5.77f, 0.0f));
    if (FAILED(game->GetRenderer()->AddRenderable(L"LightCube", lightCube)))
    {
        return 0;
    }
    if (FAILED(game->GetRenderer()->SetVertexShaderOfRenderable(L"LightCube", L"LightShader")))
    {
        return 0;
    }
    if (FAILED(game->GetRenderer()->SetPixelShaderOfRenderable(L"LightCube", L"LightShader")))
    {
        return 0;
    }

    XMStoreFloat4(&color, Colors::Red);
    std::shared_ptr<RotatingPointLight> rotatingPointLight = std::make_shared<RotatingPointLight>(
        XMFLOAT4(0.0f, 0.0f, -5.0f, 1.0f),
        color
        );
    if (FAILED(game->GetRenderer()->AddPointLight(1u, rotatingPointLight)))
    {
        return 0;
    }

    std::shared_ptr<RotatingCube> rotatingLightCube = std::make_shared<RotatingCube>(color);
    rotatingLightCube->Translate(XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f));
    if (FAILED(game->GetRenderer()->AddRenderable(L"RotatingLightCube", rotatingLightCube)))
    {
        return 0;
    }
    if (FAILED(game->GetRenderer()->SetVertexShaderOfRenderable(L"RotatingLightCube", L"LightShader")))
    {
        return 0;
    }
    if (FAILED(game->GetRenderer()->SetPixelShaderOfRenderable(L"RotatingLightCube", L"LightShader")))
    {
        return 0;
    }

    std::shared_ptr<Cube> phongCube = std::make_shared<Cube>(L"seafloor.dds");
    if (FAILED(game->GetRenderer()->AddRenderable(L"PhongCube", phongCube)))
    {
        return 0;
    }
    if (FAILED(game->GetRenderer()->SetVertexShaderOfRenderable(L"PhongCube", L"PhongShader")))
    {
        return 0;
    }
    if (FAILED(game->GetRenderer()->SetPixelShaderOfRenderable(L"PhongCube", L"PhongShader")))
    {
        return 0;
    }

    if (FAILED(game->Initialize(hInstance, nCmdShow)))
    {
        return 0;
    }

    return game->Run();
}