/*+===================================================================
  File:      RENDERER.H

  Summary:   Renderer header file contains declarations of Renderer 
             class used for the lab samples of Game Graphics 
             Programming course.

  Classes: Renderer

  © 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include <vector>

#include "Window/MainWindow.h"

namespace library
{
    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Struct:    SimpleVertex

      Summary:  Simple vertex structure containing a single field of the
                type XMFLOAT3
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    struct SimpleVertex
    {
        XMFLOAT3 Postion;
    };

    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    Renderer

      Summary:  Renderer initializes Direct3D, and renders renderable
                data onto the screen

      Methods:  Initialize
                  Creates Direct3D device and swap chain
                Render
                  Renders the frame
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
        void Render();

    private:
        HRESULT compileShaderFromFile(_In_ PCWSTR pszFileName, _In_ PCSTR pszEntryPoint, _In_ PCSTR szShaderModel, _Outptr_ ID3DBlob** ppBlobOut);

        D3D_DRIVER_TYPE m_driverType;
        D3D_FEATURE_LEVEL m_featureLevel;
        ComPtr<ID3D11Device> m_d3dDevice;
        ComPtr<ID3D11Device1> m_d3dDevice1;
        ComPtr<ID3D11DeviceContext> m_immediateContext;
        ComPtr<ID3D11DeviceContext1> m_immediateContext1;
        ComPtr<IDXGISwapChain> m_swapChain;
        ComPtr<IDXGISwapChain1> m_swapChain1;
        ComPtr<ID3D11RenderTargetView> m_renderTargetView;
        ComPtr<ID3D11VertexShader> m_vertexShader;
        ComPtr<ID3D11PixelShader> m_pixelShader;
        ComPtr<ID3D11InputLayout> m_vertexLayout;
        ComPtr<ID3D11Buffer> m_vertexBuffer;
    };
}