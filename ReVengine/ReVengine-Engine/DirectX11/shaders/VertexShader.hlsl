struct vs_input
{
    float3 position_local : POS;
};

struct vs_output
{
    float4 position_clip : SV_POSITION; //System value of position
};

vs_output vs_main(vs_input input)
{
    vs_output output = (vs_output) 0;
    output.position_clip = float4(input.position_local, 1.0);
    return output;
}