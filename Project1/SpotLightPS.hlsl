/*--------------------------------------------------------------
    
    [SpotLightPS.hlsl]
    Author : �o���đ�

--------------------------------------------------------------*/
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
       
    // �u�����t�H��
    float3 eyev = In.WorldPosition.xyz - _CameraPosition.xyz; // �����x�N�g��
    eyev = normalize(eyev);
    
    float3 halfv = eyev + _Light.Direction.xyz;
    halfv = normalize(halfv);
    
    float speculer = -dot(halfv, normal.xyz);
    speculer = saturate(speculer);
    
    speculer = pow(speculer, 30);
    outDiffuse.rgb += speculer;
    outDiffuse.a = In.Diffuse;
    
    // �X�|�b�g���C�g�̏���
    float3 vp = normalize(In.WorldPosition.xyz - _Light.Position.xyz); // ���C�g����s�N�Z���ւ̃x�N�g��
    float angle = abs(acos(dot(_Light.Direction.xyz, vp))); // ���ρ�acos���g���Ċp�x�ɕϊ����A�p�x�ɕ��̐��͂Ȃ��̂ŁA��Βl�ɂ���
    
    // ���C�g�͈̔͂��v�Z
    float spot = 1.0f - (1.0f / (_Light.Angle + _Parameter.x)) * angle;
    
    spot = saturate(spot);
    outDiffuse.rgb += spot;
}