#ifndef _COMPRESS_H_
#define _COMPRESS_H_
#include <string>
#include"Huffman.h"

const int SIZE = 256;
struct HEAD {          //�ļ�ͷ
	char type[4];      //�ļ�����
	int length;        //�ļ�����
	int weight[SIZE] = { 0 };  //Ȩֵ
};

int Encode(std::string fileName, const HuffmanCode pHC[], char* pBuffer, const int nSize);
void Compress(std::string fileName);

#endif // !_COMPRESS_H_
