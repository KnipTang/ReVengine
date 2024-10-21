struct vs_input
{
    float3 position : POSITION;
    float3 color : COLOR;
};

struct vs_output
{
    float3 color : COLOR;
    float4 position : SV_POSITION; //System value of position
};

cbuffer CBuf
{
    matrix transform;
};

vs_output vs_main(vs_input input)
{
    vs_output output = (vs_output) 0;
    output.position = mul(float4(input.position.x, input.position.y, input.position.z, 1.0f), transform);
    output.color = input.color;
    return output;
}