struct vs_input
{
    float3 position_local : POSITION;
};

struct vs_output
{
    float4 position_clip : SV_POSITION; //System value of position
};

//vs_output vs_main(vs_input input)
//{
//    vs_output output = (vs_output) 0;
//    output.position_clip = float4(input.position_local, 1.0);
//    return output;
//}

float4 vs_main(float2 pos : POSITION) : SV_Position
{
    return float4(pos.x, pos.y, 0.0f, 1.0f);
}