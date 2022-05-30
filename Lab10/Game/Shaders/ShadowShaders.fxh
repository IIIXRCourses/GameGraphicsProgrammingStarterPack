//--------------------------------------------------------------------------------------
// File: ShadowShaders.fx
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License (MIT).
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer cbShadowMatrix : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
    bool isVoxel;
}

struct VS_SHADOW_INPUT
{
	float4 Position : POSITION;
    row_major matrix mTransform : INSTANCE_TRANSFORM;
};


struct PS_SHADOW_INPUT
{
    float4 Position : SV_POSITION;
	float4 DepthPosition : TEXCOORD0;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_SHADOW_INPUT VSShadow(VS_SHADOW_INPUT input)
{
	/*--------------------------------------------------------------------
	  TODO: Vertex shader code (remove the comment)
	--------------------------------------------------------------------*/
};


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PSShadow(PS_SHADOW_INPUT input) : SV_Target
{
	/*--------------------------------------------------------------------
	  TODO: Pixel shader code (remove the comment)
	--------------------------------------------------------------------*/
};