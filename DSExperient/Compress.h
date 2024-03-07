#ifndef _COMPRESS_H_
#define _COMPRESS_H_
#include <string>
#include"Huffman.h"

const int SIZE = 256;
struct HEAD {          //文件头
	char type[4];      //文件类型
	int length;        //文件长度
	int weight[SIZE] = { 0 };  //权值
};

int Encode(std::string fileName, const HuffmanCode pHC[], char* pBuffer, const int nSize);
void Compress(std::string fileName);

#endif // !_COMPRESS_H_
