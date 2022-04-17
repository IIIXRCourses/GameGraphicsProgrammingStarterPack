/*+===================================================================
  File:      V0XEL.H

  Summary:   Voxel header file contains declarations of Voxel class 
             used for the lab samples of Game Graphics Programming 
             course.

  Classes: Voxel

  © 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Renderer/DataTypes.h"
#include "Renderer/InstancedRenderable.h"

namespace library
{
    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    Voxel

      Summary:  Base class for renderable 3d cube object

      Methods:  Voxel
                  Constructor.
                ~Voxel
                  Destructor.
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    class Voxel : public InstancedRenderable
    {
    public:
        Voxel(_In_ const XMFLOAT4& outputColor);
        Voxel(_In_ std::vector<InstanceData>&& aInstanceData, _In_ const XMFLOAT4& outputColor);
        Voxel(const Voxel& other) = delete;
        Voxel(Voxel&& other) = delete;
        Voxel& operator=(const Voxel& other) = delete;
        Voxel& operator=(Voxel&& other) = delete;
        ~Voxel() = default;

        virtual HRESULT Initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext) override;
        virtual void Update(_In_ FLOAT deltaTime) override;

        UINT GetNumVertices() const override;
        UINT GetNumIndices() const override;

    protected:
        const SimpleVertex* getVertices() const override;
        const WORD* getIndices() const override;

        static constexpr const SimpleVertex VERTICES[] =
        {
            { .Position = XMFLOAT3(-1.0f, 1.0f, -1.0f), .TexCoord = XMFLOAT2(1.0f, 0.0f), .Normal = XMFLOAT3(0.0f, 1.0f, 0.0f) },
            { .Position = XMFLOAT3(1.0f, 1.0f, -1.0f), .TexCoord = XMFLOAT2(0.0f, 0.0f), .Normal = XMFLOAT3(0.0f, 1.0f, 0.0f) },
            { .Position = XMFLOAT3(1.0f, 1.0f,  1.0f), .TexCoord = XMFLOAT2(0.0f, 1.0f), .Normal = XMFLOAT3(0.0f, 1.0f, 0.0f) },
            { .Position = XMFLOAT3(-1.0f, 1.0f,  1.0f), .TexCoord = XMFLOAT2(1.0f, 1.0f), .Normal = XMFLOAT3(0.0f, 1.0f, 0.0f) },

            { .Position = XMFLOAT3(-1.0f, -1.0f, -1.0f), .TexCoord = XMFLOAT2(0.0f, 0.0f), .Normal = XMFLOAT3(0.0f, -1.0f, 0.0f) },
            { .Position = XMFLOAT3(1.0f, -1.0f, -1.0f), .TexCoord = XMFLOAT2(1.0f, 0.0f), .Normal = XMFLOAT3(0.0f, -1.0f, 0.0f) },
            { .Position = XMFLOAT3(1.0f, -1.0f,  1.0f), .TexCoord = XMFLOAT2(1.0f, 1.0f), .Normal = XMFLOAT3(0.0f, -1.0f, 0.0f) },
            { .Position = XMFLOAT3(-1.0f, -1.0f,  1.0f), .TexCoord = XMFLOAT2(0.0f, 1.0f), .Normal = XMFLOAT3(0.0f, -1.0f, 0.0f) },

            { .Position = XMFLOAT3(-1.0f, -1.0f,  1.0f), .TexCoord = XMFLOAT2(0.0f, 1.0f), .Normal = XMFLOAT3(-1.0f, 0.0f, 0.0f) },
            { .Position = XMFLOAT3(-1.0f, -1.0f, -1.0f), .TexCoord = XMFLOAT2(1.0f, 1.0f), .Normal = XMFLOAT3(-1.0f, 0.0f, 0.0f) },
            { .Position = XMFLOAT3(-1.0f,  1.0f, -1.0f), .TexCoord = XMFLOAT2(1.0f, 0.0f), .Normal = XMFLOAT3(-1.0f, 0.0f, 0.0f) },
            { .Position = XMFLOAT3(-1.0f,  1.0f,  1.0f), .TexCoord = XMFLOAT2(0.0f, 0.0f), .Normal = XMFLOAT3(-1.0f, 0.0f, 0.0f) },

            { .Position = XMFLOAT3(1.0f, -1.0f,  1.0f), .TexCoord = XMFLOAT2(1.0f, 1.0f), .Normal = XMFLOAT3(1.0f, 0.0f, 0.0f) },
            { .Position = XMFLOAT3(1.0f, -1.0f, -1.0f), .TexCoord = XMFLOAT2(0.0f, 1.0f), .Normal = XMFLOAT3(1.0f, 0.0f, 0.0f) },
            { .Position = XMFLOAT3(1.0f,  1.0f, -1.0f), .TexCoord = XMFLOAT2(0.0f, 0.0f), .Normal = XMFLOAT3(1.0f, 0.0f, 0.0f) },
            { .Position = XMFLOAT3(1.0f,  1.0f,  1.0f), .TexCoord = XMFLOAT2(1.0f, 0.0f), .Normal = XMFLOAT3(1.0f, 0.0f, 0.0f) },

            { .Position = XMFLOAT3(-1.0f, -1.0f, -1.0f), .TexCoord = XMFLOAT2(0.0f, 1.0f), .Normal = XMFLOAT3(0.0f, 0.0f, -1.0f) },
            { .Position = XMFLOAT3(1.0f, -1.0f, -1.0f), .TexCoord = XMFLOAT2(1.0f, 1.0f), .Normal = XMFLOAT3(0.0f, 0.0f, -1.0f) },
            { .Position = XMFLOAT3(1.0f,  1.0f, -1.0f), .TexCoord = XMFLOAT2(1.0f, 0.0f), .Normal = XMFLOAT3(0.0f, 0.0f, -1.0f) },
            { .Position = XMFLOAT3(-1.0f,  1.0f, -1.0f), .TexCoord = XMFLOAT2(0.0f, 0.0f), .Normal = XMFLOAT3(0.0f, 0.0f, -1.0f) },

            { .Position = XMFLOAT3(-1.0f, -1.0f, 1.0f), .TexCoord = XMFLOAT2(1.0f, 1.0f), .Normal = XMFLOAT3(0.0f, 0.0f, 1.0f) },
            { .Position = XMFLOAT3(1.0f, -1.0f, 1.0f), .TexCoord = XMFLOAT2(0.0f, 1.0f), .Normal = XMFLOAT3(0.0f, 0.0f, 1.0f) },
            { .Position = XMFLOAT3(1.0f,  1.0f, 1.0f), .TexCoord = XMFLOAT2(0.0f, 0.0f), .Normal = XMFLOAT3(0.0f, 0.0f, 1.0f) },
            { .Position = XMFLOAT3(-1.0f,  1.0f, 1.0f), .TexCoord = XMFLOAT2(1.0f, 0.0f), .Normal = XMFLOAT3(0.0f, 0.0f, 1.0f) },
        };
        static constexpr const UINT NUM_VERTICES = 24u;
        static constexpr const WORD INDICES[] =
        {
            3,1,0,
            2,1,3,

            6,4,5,
            7,4,6,

            11,9,8,
            10,9,11,

            14,12,13,
            15,12,14,

            19,17,16,
            18,17,19,

            22,20,21,
            23,20,22
        };
        static constexpr const UINT NUM_INDICES = 36u;
    };
}