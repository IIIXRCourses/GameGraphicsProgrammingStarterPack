/*+===================================================================
  File:      CUBE.H

  Summary:   Cube header file contains declarations of Cube class
             used for the lab samples of Game Graphics Programming
             course.

  Classes: Cube

  © 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Renderer/DataTypes.h"

namespace library
{
    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    Camera

      Summary:  Immitates a camera that moves according to the WASD and
                mouse input.

      Methods:  GetEye
                  Getter for the eye vector
                GetAt
                  Getter for the at vector
                GetUp
                  Getter for the up vector
                GetView
                  Getter for the view transform matrix
                GetConstantBuffer
                  Get the constant buffer containing the view transform
                HandleInput
                  Handles the keyboard / mouse input
                Initialize
                  Initialize the view matrix constant buffers
                Update
                  Update the camera according to the input
                Camera
                  Constructor.
                ~Camera
                  Destructor.
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    class Camera
    {
    public:
        Camera() = delete;
        Camera(_In_ const XMVECTOR& position);
        Camera(const Camera& other) = delete;
        Camera(Camera&& other) = delete;
        Camera& operator=(const Camera& other) = delete;
        Camera& operator=(Camera&& other) = delete;
        virtual ~Camera() = default;

        const XMVECTOR& GetEye() const;
        const XMVECTOR& GetAt() const;
        const XMVECTOR& GetUp() const;
        const XMMATRIX& GetView() const;
        ComPtr<ID3D11Buffer>& GetConstantBuffer();

        virtual void HandleInput(_In_ const DirectionsInput& directions, _In_ const MouseRelativeMovement& mouseRelativeMovement, _In_ FLOAT deltaTime);
        virtual HRESULT Initialize(_In_ ID3D11Device* device);
        virtual void Update(_In_ FLOAT deltaTime);
    protected:
        static constexpr const XMVECTORF32 DEFAULT_FORWARD = { 0.0f, 0.0f, 1.0f, 0.0f };
        static constexpr const XMVECTORF32 DEFAULT_RIGHT = { 1.0f, 0.0f, 0.0f, 0.0f };
        static constexpr const XMVECTORF32 DEFAULT_UP = { 0.0f, 1.0f, 0.0f, 0.0f };

        ComPtr<ID3D11Buffer> m_cbChangeOnCameraMovement;

        FLOAT m_yaw;
        FLOAT m_pitch;

        FLOAT m_moveLeftRight;
        FLOAT m_moveBackForward;
        FLOAT m_moveUpDown;

        FLOAT m_travelSpeed;
        FLOAT m_rotationSpeed;

        BYTE m_padding[12]; // struct alignment

        XMVECTOR m_cameraForward;
        XMVECTOR m_cameraRight;
        XMVECTOR m_cameraUp;

        XMVECTOR m_eye;
        XMVECTOR m_at;
        XMVECTOR m_up;

        XMMATRIX m_rotation;
        XMMATRIX m_view;
    };
}