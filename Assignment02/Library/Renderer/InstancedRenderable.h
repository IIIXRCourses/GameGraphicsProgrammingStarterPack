/*+===================================================================
  File:      V0XEL.H

  Summary:   InstancedRenderable header file contains declarations of InstancedRenderable class
             used for the lab samples of Game Graphics Programming
             course.

  Classes: InstancedRenderable

  © 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Renderer/DataTypes.h"
#include "Renderer/Renderable.h"

namespace library
{
    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    InstancedRenderable

      Summary:  Base class for renderable 3d cube object

      Methods:  SetInstanceData
                  Sets the instance data
                GetInstanceBuffer
                  Returns a instance buffer
                GetNumInstances
                  Returns the number of instance data
                initializeInstance
                  Initialize the instance buffer
                InstancedRenderable
                  Constructor.
                ~InstancedRenderable
                  Destructor.
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    class InstancedRenderable : public Renderable
    {
    public:
        InstancedRenderable(_In_ const XMFLOAT4& outputColor);
        InstancedRenderable(_In_ std::vector<InstanceData>&& aInstanceData, _In_ const XMFLOAT4& outputColor);
        InstancedRenderable(const InstancedRenderable& other) = delete;
        InstancedRenderable(InstancedRenderable&& other) = delete;
        InstancedRenderable& operator=(const InstancedRenderable& other) = delete;
        InstancedRenderable& operator=(InstancedRenderable&& other) = delete;
        ~InstancedRenderable() = default;

        virtual HRESULT Initialize(_In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext* pImmediateContext) override = 0;
        virtual void Update(_In_ FLOAT deltaTime) override = 0;

        void SetInstanceData(_In_ std::vector<InstanceData>&& aInstanceData);

        virtual ComPtr<ID3D11Buffer>& GetInstanceBuffer();
        virtual UINT GetNumInstances() const;

        UINT GetNumVertices() const override = 0;
        UINT GetNumIndices() const override = 0;

    protected:
        const SimpleVertex* getVertices() const override = 0;
        const WORD* getIndices() const override = 0;

        virtual HRESULT initializeInstance(_In_ ID3D11Device* pDevice);

    protected:
        ComPtr<ID3D11Buffer> m_instanceBuffer;
        std::vector<InstanceData> m_aInstanceData;

    private:
        BYTE m_padding[8];
    };
}