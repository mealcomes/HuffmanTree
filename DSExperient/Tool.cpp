#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include<iostream>
#include<fstream>
#include<bitset>
#include "Huffman.h"
#include "Tool.h"
#include "Compress.h"

/*��ȡȨֵ*/
int readWeight(std::string fileName, int weight[], HTNode pHT[], HuffmanCode pHC[]) {
	std::ifstream fin(fileName, std::ios::in | std::ios::binary);
	int len = 0;
	while (!fin.eof()) {
		int i = (int)fin.get();
		if (i != -1) {
			weight[i]++;
			pHC[i].symbol = (unsigned char)i;
			pHC[i].code.start = N - 2;
			pHT[i + 1].lchild = pHT[i + 1].rchild = pHT[i + 1].parent = 0;
			pHT[i + 1].weigthpHT++;
			len++;
		}
	}
	fin.close();
	return len;
}

/*�����ʼȨֵ*/
void PrintWeight(int weight[]) {
	std::cout << "ԭ�ļ�ÿ���ַ���ȨֵΪ:\n";
	std::cout << "Byte Weight\n";
	for (int i = 0; i < N; i++) {
		printf("0x%02X %d\n", i, weight[i]);
	}
}

/*������������ʱѡ��Ȩֵ��С�Ľ��*/
int Select(HuffmanTree pHT, int nSize) {
	int minValue = std::numeric_limits<int>::max(), min = 0;
	for (int i = 1; i < nSize; i++) {
		if (pHT[i].parent == 0 && pHT[i].weigthpHT < minValue) {
			minValue = pHT[i].weigthpHT;
			min = i;
		}
	}
	return min;
}

/*����������������ڵ���Ϣ*/
void TestHufTree(HuffmanTree pHT) {
	std::cout << "��������ÿ���ڵ���ϢΪ:\n";
	std::cout << "Byte\tWeight\tParent\tLchild\tRchild\n";
	for (int i = 1; i < 2 * N; i++) {
		printf("pHT[%d]\t%d\t%d\t%d\t%d\n", i, pHT[i].weigthpHT, pHT[i].parent, pHT[i].lchild, pHT[i].rchild);
	}
}

/*���������������ڵ���Ϣ*/
void TestHufTreeN(HuffmanTree pHT, HuffmanCode pHC[], int root) {
	printf("������������������Ϊ:\n");
	PreTravelHuffTree(pHT, pHC, root, POINT_INFO);
}

/*��������������������*/
void TestHufCode(HuffmanCode pHC[], HuffmanTree pHT, int root) {
	printf("������������������������������Ϣ:\n");
	PreTravelHuffTree(pHT, pHC, root, CODE_INFO);
}

/*��������������� flag(1:��������Ϣ 2:���Ҷ�ӽ�����)*/
void PreTravelHuffTree(HuffmanTree pHT, HuffmanCode pHC[], int root, int flag) {
	if (root == 0)return;
	if (flag == 1)
		printf("%d ", pHT[root].weigthpHT);
	else {
		if (pHT[root].rchild == 0 && pHT[root].lchild == 0) {
			printf("0x%02X %s\n", root - 1, pHC[root - 1].code.bits + pHC[root - 1].code.start);
		}
	}
	PreTravelHuffTree(pHT, pHC, pHT[root].lchild, flag);
	PreTravelHuffTree(pHT, pHC, pHT[root].rchild, flag);
}

/*����01���ַ���ת��Ϊ�ֽ�*/
char Str2byte(const char pBinStr[]) {
	char b = 0x00;
	for (int i = 0; i < 8; i++) {
		b = b << 1;
		if (pBinStr[i] == '1')
			b = b | 0x01;
	}
	return b;
}

/*��ʼ���ļ�ͷ*/
void IniteHead(std::string fileName, HEAD& fileHead) {
	strcpy(fileHead.type, "HUF");
	fileHead.length = 0;

	std::ifstream fin(fileName, std::ios::in | std::ios::binary);
	while (!fin.eof()) {
		int tmp = (int)fin.get();    //�õ���ȡ����һ���ַ���Ӧ��intֵ
		if (tmp != -1) {
			fileHead.weight[tmp]++;
			fileHead.length++;
		}
	}
	fin.close();
}

/*��ѹ���������д���ļ�*/
int writeFile(const std::string fileName, const HEAD fileHead, const char* pBuffer, const int nSize) {
	std::string file(fileName + ".huf");
	std::ofstream fout(file, std::ios::out | std::ios::binary);
	fout.write((char*)&fileHead, sizeof HEAD);
	fout.write(pBuffer, nSize);

	fout.close();
	return nSize + 1 + fileName.length() + sizeof(HEAD);
}