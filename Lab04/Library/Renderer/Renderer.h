/*+===================================================================
  File:      RENDERER.H

  Summary:   Renderer header file contains declarations of Renderer 
             class used for the lab samples of Game Graphics 
             Programming course.

  Classes: Renderer

  � 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Renderer/DataTypes.h"
#include "Renderer/Renderable.h"
#include "Shader/PixelShader.h"
#include "Shader/VertexShader.h"
#include "Window/MainWindow.h"

namespace library
{
    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    Renderer

      Summary:  Renderer initializes Direct3D, and renders renderable
                data onto the screen

      Methods:  Initialize
                  Creates Direct3D device and swap chain
                AddRenderable
                  Add a renderable object
                AddVertexShader
                  Add a vertex shader object
                AddPixelShader
                  Add a pixel shader object
                Update
                  Update the renderables each frame
                Render
                  Renders the frame
                SetVertexShaderOfRenderable
                  Set vertex shader to the renderable
                SetPixelShaderOfRenderable
                  Set pixel shader to the renderable
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
        HRESULT AddRenderable(_In_ PCWSTR pszRenderableName,_In_ const std::shared_ptr<Renderable>& renderable);
        HRESULT AddVertexShader(_In_ PCWSTR pszVertexShaderName, _In_ const std::shared_ptr<VertexShader>& vertexShader);
        HRESULT AddPixelShader(_In_ PCWSTR pszPixelShaderName, _In_ const std::shared_ptr<PixelShader>& pixelShader);

        void Update(_In_ FLOAT deltaTime);
        void Render();

        HRESULT SetVertexShaderOfRenderable(_In_ PCWSTR pszRenderableName, _In_ PCWSTR pszVertexShaderName);
        HRESULT SetPixelShaderOfRenderable(_In_ PCWSTR pszRenderableName, _In_ PCWSTR pszPixelShaderName);

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
        XMMATRIX m_view;
        XMMATRIX m_projection;

        std::unordered_map<PCWSTR, std::shared_ptr<Renderable>> m_renderables;
        std::unordered_map<PCWSTR, std::shared_ptr<VertexShader>> m_vertexShaders;
        std::unordered_map<PCWSTR, std::shared_ptr<PixelShader>> m_pixelShaders;
    };
}