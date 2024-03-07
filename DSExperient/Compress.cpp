#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include<fstream>
#include "Tool.h"
#include "Huffman.h"

#define endl '\n'

/*ѹ�����*/
void Compress(std::string fileName) {
	int weight[N] = { 0 };
	HTNode pHT[2 * N];  //��������洢Huffman��
	HuffmanCode pHC[N];  //��������洢Huffman����

	int initLen = readWeight(fileName, weight, pHT, pHC);  //��ȡ�ļ�Ȩֵ
	std::cout << initLen << "�ֽ�\n";
	//PrintWeight(weight);                      //���Ȩֵ
	CreateHuffmanTree(pHT);            //������������
	//TestHufTreeN(pHT, pHC, M);                  //����������Ȩֵ
	HuffmanCoding(pHT, pHC);           //���й���������
	//TestHufCode(pHC, pHT, M);                   //��������������

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
	std::cout << "����ѹ���ļ�" << fileName + ".huf\n";
	std::cout << finalLen << endl;
	std::cout << "ѹ������:" << finalLen * 1.0 / initLen * 100 << "%\n";
}

/*�����ļ�ѹ��*/
int Encode(std::string fileName, const HuffmanCode pHC[], char* pBuffer, const int nSize) {
	char cd[300] = { '\0' };    //���ٹ�����
	int pos = 0;
	std::ifstream fin(fileName, std::ios::in | std::ios::binary);
	while (!fin.eof()) {
		int tmp = (int)fin.get();    //�õ���ȡ����һ���ַ���Ӧ��intֵ
		if (tmp != -1) {
			std::strcat(cd, pHC[tmp].code.bits + pHC[tmp].code.start); //������intֵ��Ӧ�Ĺ���������ƴ�ӵ�������
			while (strlen(cd) >= 8) {          //����������ÿ8λ����һ��ת��
				*(pBuffer + pos) = Str2byte(cd);
				pos++;
				int len = strlen(cd);
				for (int i = 0; i <= len; i++) { //����������
					cd[i] = cd[i + 8];
				}
			}
		}
	}
	if (strlen(cd) > 0) {       //�����²�����λ�ı������ת��ƴ��
		int len = strlen(cd);
		for (int i = len; i < 8; i++)
			cd[i] = 0;
		*(pBuffer + pos) = Str2byte(cd);
		pos++;
	}
	return 0;
}
