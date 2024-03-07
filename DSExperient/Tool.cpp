#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include<iostream>
#include<fstream>
#include<bitset>
#include "Huffman.h"
#include "Tool.h"
#include "Compress.h"

/*读取权值*/
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

/*输出初始权值*/
void PrintWeight(int weight[]) {
	std::cout << "原文件每个字符的权值为:\n";
	std::cout << "Byte Weight\n";
	for (int i = 0; i < N; i++) {
		printf("0x%02X %d\n", i, weight[i]);
	}
}

/*构建哈夫曼树时选择权值最小的结点*/
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

/*输出哈夫曼树各个节点信息*/
void TestHufTree(HuffmanTree pHT) {
	std::cout << "哈夫曼树每个节点信息为:\n";
	std::cout << "Byte\tWeight\tParent\tLchild\tRchild\n";
	for (int i = 1; i < 2 * N; i++) {
		printf("pHT[%d]\t%d\t%d\t%d\t%d\n", i, pHT[i].weigthpHT, pHT[i].parent, pHT[i].lchild, pHT[i].rchild);
	}
}

/*先序遍历输出各个节点信息*/
void TestHufTreeN(HuffmanTree pHT, HuffmanCode pHC[], int root) {
	printf("先序遍历哈夫曼树结果为:\n");
	PreTravelHuffTree(pHT, pHC, root, POINT_INFO);
}

/*先序遍历输出哈夫曼编码*/
void TestHufCode(HuffmanCode pHC[], HuffmanTree pHT, int root) {
	printf("先序遍历哈夫曼树输出哈夫曼编码信息:\n");
	PreTravelHuffTree(pHT, pHC, root, CODE_INFO);
}

/*先序遍历哈夫曼树 flag(1:输出结点信息 2:输出叶子结点编码)*/
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

/*将“01”字符串转化为字节*/
char Str2byte(const char pBinStr[]) {
	char b = 0x00;
	for (int i = 0; i < 8; i++) {
		b = b << 1;
		if (pBinStr[i] == '1')
			b = b | 0x01;
	}
	return b;
}

/*初始化文件头*/
void IniteHead(std::string fileName, HEAD& fileHead) {
	strcpy(fileHead.type, "HUF");
	fileHead.length = 0;

	std::ifstream fin(fileName, std::ios::in | std::ios::binary);
	while (!fin.eof()) {
		int tmp = (int)fin.get();    //得到读取到的一个字符对应的int值
		if (tmp != -1) {
			fileHead.weight[tmp]++;
			fileHead.length++;
		}
	}
	fin.close();
}

/*将压缩后的数据写入文件*/
int writeFile(const std::string fileName, const HEAD fileHead, const char* pBuffer, const int nSize) {
	std::string file(fileName + ".huf");
	std::ofstream fout(file, std::ios::out | std::ios::binary);
	fout.write((char*)&fileHead, sizeof HEAD);
	fout.write(pBuffer, nSize);

	fout.close();
	return nSize + 1 + fileName.length() + sizeof(HEAD);
}