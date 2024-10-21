struct ps_input
{
    float3 color : COLOR;
};

struct ps_output
{
    float4 color : SV_TARGET;
};

ps_output ps_main(ps_input input)
{
    ps_output output;
    output.color = float4(input.color, 1.0f);
    return output;
}