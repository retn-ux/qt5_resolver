#include "pch.h"
#include <MathPlus.h>


/*********************************************************************************
*函数名：OperationExtend
*形参：MH，mWord,output（输出）
*作用：将乘法扩展到64位，高32位和低32位将分别放在output中
**********************************************************************************/
void OperationExtend(int MH, int mWord,int *output) {
	//每一个元素只保存2个字节，将字节扩展到8个
	int stopOverflow[4];
	//进位标志位
	unsigned short int CF = 0;
	stopOverflow[3] = MH & 0xFFFF;
	stopOverflow[2] = (MH & 0xFFFF0000) >> 16;
	stopOverflow[1] = 0;
	stopOverflow[0] = 0;
	//将0x55555556与mWord相乘取其中高32位
	for (int a = 3;a >= 0;a--) {
		stopOverflow[a] *= mWord;
		stopOverflow[a] += CF;
		CF = (stopOverflow[a] & 0xFFFF0000) >> 16;
	}

	output[0] |= (stopOverflow[0] & 0xFFFF);
	output[0] <<= 16;
	output[0] |= (stopOverflow[1] & 0xFFFF);

	output[1] |= (stopOverflow[3] & 0xFFFF);
	output[1] <<= 16;
	output[1] |= (stopOverflow[4] & 0xFFFF);
}



void_ptr vptr_add_Gauge(void_ptr v, Gauge d) {
	return tovptr(toGauge(v) + d);
}
