#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include<fstream>
#include "Tool.h"
#include "Huffman.h"

#define endl '\n'

/*压缩入口*/
void Compress(std::string fileName) {
	int weight[N] = { 0 };
	HTNode pHT[2 * N];  //分配数组存储Huffman树
	HuffmanCode pHC[N];  //分配数组存储Huffman编码

	int initLen = readWeight(fileName, weight, pHT, pHC);  //读取文件权值
	std::cout << initLen << "字节\n";
	//PrintWeight(weight);                      //输出权值
	CreateHuffmanTree(pHT);            //构建哈夫曼树
	//TestHufTreeN(pHT, pHC, M);                  //先序遍历输出权值
	HuffmanCoding(pHT, pHC);           //进行哈夫曼编码
	//TestHufCode(pHC, pHT, M);                   //先序遍历输出编码

	size_t nSize = 0;
	for (int i = 0; i < 256; i++) {
		nSize += weight[i] * strlen(pHC[i].code.bits + pHC[i].code.start);
	}
	nSize = (nSize % 8 == 0) ? nSize / 8 + 1 : nSize / 8;

	char* pBuffer = new char[nSize * sizeof(char)];

	Encode(fileName, pHC, pBuffer, nSize);

	HEAD fileHead;
	IniteHead(fileName, fileHead);
	int finalLen = writeFile(fileName, fileHead, pBuffer, nSize);
	std::cout << "生成压缩文件" << fileName + ".huf\n";
	std::cout << finalLen << endl;
	std::cout << "压缩比率:" << finalLen * 1.0 / initLen * 100 << "%\n";
}

/*进行文件压缩*/
int Encode(std::string fileName, const HuffmanCode pHC[], char* pBuffer, const int nSize) {
	char cd[300] = { '\0' };    //开辟工作区
	int pos = 0;
	std::ifstream fin(fileName, std::ios::in | std::ios::binary);
	while (!fin.eof()) {
		int tmp = (int)fin.get();    //得到读取到的一个字符对应的int值
		if (tmp != -1) {
			std::strcat(cd, pHC[tmp].code.bits + pHC[tmp].code.start); //将上述int值对应的哈夫曼编码拼接到工作区
			while (strlen(cd) >= 8) {          //哈夫曼编码每8位进行一次转码
				*(pBuffer + pos) = Str2byte(cd);
				pos++;
				int len = strlen(cd);
				for (int i = 0; i <= len; i++) { //工作区右移
					cd[i] = cd[i + 8];
				}
			}
		}
	}
	if (strlen(cd) > 0) {       //将余下不够八位的编码进行转码拼接
		int len = strlen(cd);
		for (int i = len; i < 8; i++)
			cd[i] = 0;
		*(pBuffer + pos) = Str2byte(cd);
		pos++;
	}
	return 0;
}
