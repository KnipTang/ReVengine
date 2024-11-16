struct vs_input
{
    float3 position : POSITION;
    //float2 uv: UV;
    float3 color : COLOR;
};

struct vs_output
{
    float4 position : SV_POSITION;
    //float2 uv: UV;
    float3 color : COLOR;
};

cbuffer CBuf
{
    matrix transform;
};

vs_output vs_main(vs_input input)
{
    vs_output output = (vs_output) 0;
    
    output.position = mul(float4(input.position.x, input.position.y, input.position.z, 1.0f), transform);
    //output.uv = input.uv;
    output.color = input.color;
    
    return output;
}