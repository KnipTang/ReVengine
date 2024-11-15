struct vs_input
{
    float3 position : POSITION;
    float2 uv: UV;
};

struct vs_output
{
    float4 position : SV_POSITION;
    float2 uv : UV;
};

cbuffer CBuf
{
    matrix transform;
};

vs_output vs_main(vs_input input)
{
    vs_output output = (vs_output) 0;
    
    output.position = mul(float4(input.position.x, input.position.y, input.position.z, 1.0f), transform);
    output.uv = input.uv;
    
    return output;
}