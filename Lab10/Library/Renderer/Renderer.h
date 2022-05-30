/*+===================================================================
  File:      RENDERER.H

  Summary:   Renderer header file contains declarations of Renderer
             class used for the lab samples of Game Graphics
             Programming course.

  Classes: Renderer

  ?2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Camera/Camera.h"
#include "Light/PointLight.h"
#include "Model/Model.h"
#include "Renderer/DataTypes.h"
#include "Renderer/Renderable.h"
#include "Scene/Scene.h"
#include "Shader/PixelShader.h"
#include "Shader/VertexShader.h"
#include "Window/MainWindow.h"
#include "Texture/RenderTexture.h"
#include "Shader/ShadowVertexShader.h"

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
                Update
                  Update the renderables each frame
                Render
                  Renders the frame
                GetDriverType
                  Returns the Direct3D driver type
                Renderer
                  Constructor.
                ~Renderer
                  Destructor.
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    class Renderer final
    {
    public:
        Renderer();
        Renderer(const Renderer& other) = delete;
        Renderer(Renderer&& other) = delete;
        Renderer& operator=(const Renderer& other) = delete;
        Renderer& operator=(Renderer&& other) = delete;
        ~Renderer() = default;

        HRESULT Initialize(_In_ HWND hWnd);

        HRESULT AddScene(_In_ PCWSTR pszSceneName, _In_ const std::shared_ptr<Scene>& scene);
        std::shared_ptr<Scene> GetSceneOrNull(_In_ PCWSTR pszSceneName);
        HRESULT SetMainScene(_In_ PCWSTR pszSceneName);
        void SetShadowMapShaders(_In_ std::shared_ptr<ShadowVertexShader> vertexShader, _In_ std::shared_ptr<PixelShader> pixelShader);

        void HandleInput(_In_ const DirectionsInput& directions, _In_ const MouseRelativeMovement& mouseRelativeMovement, _In_ FLOAT deltaTime);
        void Update(_In_ FLOAT deltaTime);
        void Render();
        void RenderSceneToTexture();

        D3D_DRIVER_TYPE GetDriverType() const;

    private:
        D3D_DRIVER_TYPE m_driverType;
        D3D_FEATURE_LEVEL m_featureLevel;
        ComPtr<ID3D11Device> m_d3dDevice;
        ComPtr<ID3D11Device1> m_d3dDevice1;
        ComPtr<ID3D11DeviceContext> m_immediateContext;
        ComPtr<ID3D11DeviceContext1> m_immediateContext1;
        ComPtr<IDXGISwapChain> m_swapChain;
        ComPtr<IDXGISwapChain1> m_swapChain1;
        ComPtr<ID3D11RenderTargetView> m_renderTargetView;
        ComPtr<ID3D11Texture2D> m_depthStencil;
        ComPtr<ID3D11DepthStencilView> m_depthStencilView;
        ComPtr<ID3D11Buffer> m_cbChangeOnResize;
        ComPtr<ID3D11Buffer> m_cbLights;
        ComPtr<ID3D11Buffer> m_cbShadowMatrix;
        PCWSTR m_pszMainSceneName;
        BYTE m_padding[8];
        Camera m_camera;
        XMMATRIX m_projection;

        std::unordered_map<std::wstring, std::shared_ptr<Scene>> m_scenes;
        std::shared_ptr<Texture> m_invalidTexture;
        std::shared_ptr<RenderTexture> m_shadowMapTexture;
        std::shared_ptr<ShadowVertexShader> m_shadowVertexShader;
        std::shared_ptr<PixelShader> m_shadowPixelShader;
    };
}