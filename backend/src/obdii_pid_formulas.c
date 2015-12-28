#include "obdii.h"

static int pid00_handler(int packed)
{
	return packed;
}
static int pid01_handler(int packed)
{
	return packed;
}
static int pid02_handler(int packed)
{
	return packed;
}
static int pid03_handler(int packed)
{
	return packed;
}
static int pid04_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*100/255);
}
static int pid05_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A-40);
}
static int pid06_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return ((A-128) * 100/128);
}
static int pid07_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return ((A-128) * 100/128);
}
static int pid08_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return ((A-128) * 100/128);
}
static int pid09_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return ((A-128) * 100/128);
}
static int pid0A_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*3);
}
static int pid0B_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A);
}
static int pid0C_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B)/4);
}
static int pid0D_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A);
}
static int pid0E_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return ((A-128)/2);
}
static int pid0F_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A-40);
}
static int pid10_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B) / 100);
}
static int pid11_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*100/255);
}
static int pid12_handler(int packed)
{
	return packed;
}
static int pid13_handler(int packed)
{
	return packed;
}
static int pid14_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (A/200) / ((B-128) * 100/128);
}
static int pid15_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (A/200) / ((B-128) * 100/128);
}
static int pid16_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (A/200) / ((B-128) * 100/128);
}
static int pid17_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (A/200) / ((B-128) * 100/128);
}
static int pid18_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (A/200) / ((B-128) * 100/128);
}
static int pid19_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (A/200) / ((B-128) * 100/128);
}
static int pid1A_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (A/200) / ((B-128) * 100/128);
}
static int pid1B_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (A/200) / ((B-128) * 100/128);
}
static int pid1C_handler(int packed)
{
	return packed;
}
static int pid1D_handler(int packed)
{
	return packed;
}
static int pid1E_handler(int packed)
{
	return packed;
}
static int pid1F_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return ((A*256)+B);
}
static int pid20_handler(int packed)
{
	return packed;
}
static int pid21_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return ((A*256)+B);
}
static int pid22_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B) * 0.079);
}
static int pid23_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B) * 10);
}
static int pid24_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B)*2/65535);
}
static int pid25_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int C = (packed >> (8 * 2)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	int D = (packed >> (8 * 3)) & 0xFF;
	return (((A*256)+B)*2/65535) / (((C*256)+D)*8/65535);
}
static int pid26_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int C = (packed >> (8 * 2)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	int D = (packed >> (8 * 3)) & 0xFF;
	return (((A*256)+B)*2/65535) / (((C*256)+D)*8/65535);
}
static int pid27_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int C = (packed >> (8 * 2)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	int D = (packed >> (8 * 3)) & 0xFF;
	return (((A*256)+B)*2/65535) / (((C*256)+D)*8/65535);
}
static int pid28_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int C = (packed >> (8 * 2)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	int D = (packed >> (8 * 3)) & 0xFF;
	return (((A*256)+B)*2/65535) / (((C*256)+D)*8/65535);
}
static int pid29_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int C = (packed >> (8 * 2)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	int D = (packed >> (8 * 3)) & 0xFF;
	return (((A*256)+B)*2/65535) / (((C*256)+D)*8/65535);
}
static int pid2A_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int C = (packed >> (8 * 2)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	int D = (packed >> (8 * 3)) & 0xFF;
	return (((A*256)+B)*2/65535) / (((C*256)+D)*8/65535);
}
static int pid2B_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int C = (packed >> (8 * 2)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	int D = (packed >> (8 * 3)) & 0xFF;
	return (((A*256)+B)*2/65535) / (((C*256)+D)*8/65535);
}
static int pid2C_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*100/255);
}
static int pid2D_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return ((A-128) * 100/128);
}
static int pid2E_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*100/255);
}
static int pid2F_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*100/255);
}
static int pid30_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A);
}
static int pid31_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return ((A*256)+B);
}
static int pid32_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B)/4);
}
static int pid33_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A);
}
static int pid34_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int C = (packed >> (8 * 2)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	int D = (packed >> (8 * 3)) & 0xFF;
	return (((A*256)+B)/32768) / (((C*256)+D)/256 - 128);
}
static int pid35_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int C = (packed >> (8 * 2)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	int D = (packed >> (8 * 3)) & 0xFF;
	return (((A*256)+B)/32768) / (((C*256)+D)/256 - 128);
}
static int pid36_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int C = (packed >> (8 * 2)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	int D = (packed >> (8 * 3)) & 0xFF;
	return (((A*256)+B)/32768) / (((C*256)+D)/256 - 128);
}
static int pid37_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int C = (packed >> (8 * 2)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	int D = (packed >> (8 * 3)) & 0xFF;
	return (((A*256)+B)/32768) / (((C*256)+D)/256 - 128);
}
static int pid38_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int C = (packed >> (8 * 2)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	int D = (packed >> (8 * 3)) & 0xFF;
	return (((A*256)+B)/32768) / (((C*256)+D)/256 - 128);
}
static int pid39_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int C = (packed >> (8 * 2)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	int D = (packed >> (8 * 3)) & 0xFF;
	return (((A*256)+B)/32768) / (((C*256)+D)/256 - 128);
}
static int pid3A_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int C = (packed >> (8 * 2)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	int D = (packed >> (8 * 3)) & 0xFF;
	return (((A*256)+B)/32768) / (((C*256)+D)/256 - 128);
}
static int pid3B_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int C = (packed >> (8 * 2)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	int D = (packed >> (8 * 3)) & 0xFF;
	return (((A*256)+B)/32768) / (((C*256)+D)/256 - 128);
}
static int pid3C_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B)/10 - 40);
}
static int pid3D_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B)/10 - 40);
}
static int pid3E_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B)/10 - 40);
}
static int pid3F_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B)/10 - 40);
}
static int pid40_handler(int packed)
{
	return packed;
}
static int pid41_handler(int packed)
{
	return packed;
}
static int pid42_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B)/1000);
}
static int pid43_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B)*100/255);
}
static int pid44_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B)/32768);
}
static int pid45_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*100/255);
}
static int pid46_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A-40);
}
static int pid47_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*100/255);
}
static int pid48_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*100/255);
}
static int pid49_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*100/255);
}
static int pid4A_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*100/255);
}
static int pid4B_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*100/255);
}
static int pid4C_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*100/255);
}
static int pid4D_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return ((A*256)+B);
}
static int pid4E_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return ((A*256)+B);
}
static int pid4F_handler(int packed)
{
	int D = (packed >> (8 * 3)) & 0xFF;
	return (D*10);
}
static int pid50_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*10);
}
static int pid51_handler(int packed)
{
	return packed;
}
static int pid52_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*100/255);
}
static int pid53_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B)/200);
}
static int pid54_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B)-32767);
}
static int pid55_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return ((A-128)*100/128) / ((B-128)*100/128);
}
static int pid56_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return ((A-128)*100/128) / ((B-128)*100/128);
}
static int pid57_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return ((A-128)*100/128) / ((B-128)*100/128);
}
static int pid58_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return ((A-128)*100/128) / ((B-128)*100/128);
}
static int pid59_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B) * 10);
}
static int pid5A_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*100/255);
}
static int pid5B_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A*100/255);
}
static int pid5C_handler(int packed)
{
	return packed;
}
static int pid5D_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return ((((A*256)+B)-26880)/128);
}
static int pid5E_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (((A*256)+B)/20);
}
static int pid5F_handler(int packed)
{
	return packed;
}
static int pid60_handler(int packed)
{
	return packed;
}
static int pid61_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A-125);
}
static int pid62_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	return (A-125);
}
static int pid63_handler(int packed)
{
	int A = (packed >> (8 * 0)) & 0xFF;
	int B = (packed >> (8 * 1)) & 0xFF;
	return (A*256+B);
}
static int pid64_handler(int packed)
{
	return packed;
}
static int pid65_handler(int packed)
{
	return packed;
}
static int pid66_handler(int packed)
{
	return packed;
}
static int pid67_handler(int packed)
{
	return packed;
}
static int pid68_handler(int packed)
{
	return packed;
}
static int pid69_handler(int packed)
{
	return packed;
}
static int pid6A_handler(int packed)
{
	return packed;
}
static int pid6B_handler(int packed)
{
	return packed;
}
static int pid6C_handler(int packed)
{
	return packed;
}
static int pid6D_handler(int packed)
{
	return packed;
}
static int pid6E_handler(int packed)
{
	return packed;
}
static int pid6F_handler(int packed)
{
	return packed;
}
static int pid70_handler(int packed)
{
	return packed;
}
static int pid71_handler(int packed)
{
	return packed;
}
static int pid72_handler(int packed)
{
	return packed;
}
static int pid73_handler(int packed)
{
	return packed;
}
static int pid74_handler(int packed)
{
	return packed;
}
static int pid75_handler(int packed)
{
	return packed;
}
static int pid76_handler(int packed)
{
	return packed;
}
static int pid77_handler(int packed)
{
	return packed;
}
static int pid78_handler(int packed)
{
	return packed;
}
static int pid79_handler(int packed)
{
	return packed;
}
static int pid7A_handler(int packed)
{
	return packed;
}
static int pid7B_handler(int packed)
{
	return packed;
}
static int pid7C_handler(int packed)
{
	return packed;
}
static int pid7D_handler(int packed)
{
	return packed;
}
static int pid7E_handler(int packed)
{
	return packed;
}
static int pid7F_handler(int packed)
{
	return packed;
}

const pid_handler pid_formulas[N_PID] = {
        pid00_handler,
        pid01_handler,
        pid02_handler,
        pid03_handler,
        pid04_handler,
        pid05_handler,
        pid06_handler,
        pid07_handler,
        pid08_handler,
        pid09_handler,
        pid0A_handler,
        pid0B_handler,
        pid0C_handler,
        pid0D_handler,
        pid0E_handler,
        pid0F_handler,
        pid10_handler,
        pid11_handler,
        pid12_handler,
        pid13_handler,
        pid14_handler,
        pid15_handler,
        pid16_handler,
        pid17_handler,
        pid18_handler,
        pid19_handler,
        pid1A_handler,
        pid1B_handler,
        pid1C_handler,
        pid1D_handler,
        pid1E_handler,
        pid1F_handler,
        pid20_handler,
        pid21_handler,
        pid22_handler,
        pid23_handler,
        pid24_handler,
        pid25_handler,
        pid26_handler,
        pid27_handler,
        pid28_handler,
        pid29_handler,
        pid2A_handler,
        pid2B_handler,
        pid2C_handler,
        pid2D_handler,
        pid2E_handler,
        pid2F_handler,
        pid30_handler,
        pid31_handler,
        pid32_handler,
        pid33_handler,
        pid34_handler,
        pid35_handler,
        pid36_handler,
        pid37_handler,
        pid38_handler,
        pid39_handler,
        pid3A_handler,
        pid3B_handler,
        pid3C_handler,
        pid3D_handler,
        pid3E_handler,
        pid3F_handler,
        pid40_handler,
        pid41_handler,
        pid42_handler,
        pid43_handler,
        pid44_handler,
        pid45_handler,
        pid46_handler,
        pid47_handler,
        pid48_handler,
        pid49_handler,
        pid4A_handler,
        pid4B_handler,
        pid4C_handler,
        pid4D_handler,
        pid4E_handler,
        pid4F_handler,
        pid50_handler,
        pid51_handler,
        pid52_handler,
        pid53_handler,
        pid54_handler,
        pid55_handler,
        pid56_handler,
        pid57_handler,
        pid58_handler,
        pid59_handler,
        pid5A_handler,
        pid5B_handler,
        pid5C_handler,
        pid5D_handler,
        pid5E_handler,
        pid5F_handler,
        pid60_handler,
        pid61_handler,
        pid62_handler,
        pid63_handler,
        pid64_handler,
        pid65_handler,
        pid66_handler,
        pid67_handler,
        pid68_handler,
        pid69_handler,
        pid6A_handler,
        pid6B_handler,
        pid6C_handler,
        pid6D_handler,
        pid6E_handler,
        pid6F_handler,
        pid70_handler,
        pid71_handler,
        pid72_handler,
        pid73_handler,
        pid74_handler,
        pid75_handler,
        pid76_handler,
        pid77_handler,
        pid78_handler,
        pid79_handler,
        pid7A_handler,
        pid7B_handler,
        pid7C_handler,
        pid7D_handler,
        pid7E_handler,
        pid7F_handler
};
