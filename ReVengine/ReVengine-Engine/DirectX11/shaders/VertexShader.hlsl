struct vs_input
{
    float2 position : POSITION;
    float3 color : COLOR;
};

struct vs_output
{
    float3 color : COLOR;
    float4 position : SV_POSITION; //System value of position
};

vs_output vs_main(vs_input input)
{
    vs_output output = (vs_output) 0;
    output.position = float4(input.position.x, input.position.y, 0, 1.0f);
    output.color = input.color;
    return output;
}