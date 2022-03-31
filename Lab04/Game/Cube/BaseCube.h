/*+===================================================================
  File:      BASECUBE.H

  Summary:   Base cube header file contains declarations of BaseCube
             class used for the lab samples of Game Graphics
             Programming course.

  Classes: Cube

  � 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Renderer/DataTypes.h"
#include "Renderer/Renderable.h"

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    BaseCube

  Summary:  Base class for renderable 3d cube object

  Methods:  Initialize
              Initializes a basic cube
            Update
              Pure virtual function that updates the cube every frame
            GetNumVertices
              Returns the number of vertices in the cube
            GetNumIndices
              Returns the number of indices in the cube
            getVertices
              Returns the pointer to the vertices data
            getIndices
              Returns the pointer to the indices data
            BaseCube
              Constructor.
            ~BaseCube
              Destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class BaseCube : public library::Renderable
{
public:
    BaseCube() = default;
    BaseCube(const BaseCube& other) = delete;
    BaseCube(BaseCube&& other) = delete;
    BaseCube& operator=(const BaseCube& other) = delete;
    BaseCube& operator=(BaseCube&& other) = delete;
    ~BaseCube() = default;

    virtual HRESULT Initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext) override;
    virtual void Update(_In_ FLOAT deltaTime) = 0;

    UINT GetNumVertices() const override;
    UINT GetNumIndices() const override;
protected:
    const library::SimpleVertex* getVertices() const override;
    const WORD* getIndices() const override;

    static constexpr const library::SimpleVertex VERTICES[] =
    {
        { .Position = DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f) },
        { .Position = DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f) },
        { .Position = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f) },
        { .Position = DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f) },
        { .Position = DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f) },
        { .Position = DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f) },
        { .Position = DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f) },
        { .Position = DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f) },
    };
    static constexpr const UINT NUM_VERTICES = 8u;
    static constexpr const WORD INDICES[] =
    {
        3,1,0,
        2,1,3,

        0,5,4,
        1,5,0,

        3,4,7,
        0,4,3,

        1,6,5,
        2,6,1,

        2,7,6,
        3,7,2,

        6,4,5,
        7,4,6,
    };
    static constexpr const UINT NUM_INDICES = 36u;
};