
struct VS_INPUT
{
    float4 position : POSITION;
    //float4 color : COLOR;
    float2 uv : TEXCOORD;
};


struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    //float4 color : COLOR;
    float2 uv : TEXCOORD;
};


//상수 버퍼를 이용하여 값(정점의 위치 크기 회전??)을 변경
cbuffer TransformData : register(b0)
{
    float4 offset;
}


//vs : 정점 단위로 실행된다.
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = input.position + offset;
    output.uv = input.uv;
    
    return output;
}

Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);


float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 color = texture0.Sample(sampler0, input.uv);
	
    return color;
}