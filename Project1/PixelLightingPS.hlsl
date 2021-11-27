/*-----------------------------------------------------
    
    [PixelLightingPS.hlsl]
    Author : �o���đ�

------------------------------------------------------*/
#include "Common.hlsli"

Texture2D g_texture : register(t0);
SamplerState g_samplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_TARGET)
{
    float4 normal = normalize(In.Normal);
    float light = 0.5f - 0.5f * dot(normal.xyz, _Light.Direction.xyz);
    
    outDiffuse = g_texture.Sample(g_samplerState, In.TexCoord);
    outDiffuse.rgb *= (light * In.Diffuse.rgb);
    outDiffuse.a += In.Diffuse.a;
    
    // �t�H�����ʔ���
    float3 eyev = In.WorldPosition.xyz - _CameraPosition.xyz; // �����x�N�g��
    eyev = normalize(eyev);
    
    float3 refv = reflect(_Light.Direction.xyz, normal.xyz); // ���̔��˃x�N�g��
    refv = normalize(refv);
    float speculer = -dot(eyev, refv);
    speculer = saturate(speculer);
    speculer = pow(speculer, 30);

    outDiffuse.rgb += speculer;
}