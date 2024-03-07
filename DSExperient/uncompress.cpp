#include <iostream>
#include <fstream>
#include<string>
#include<bitset>

#include"Huffman.h"
#include"Compress.h"
#include"Tool.h"

/*��ѹ�����*/
void uncompress(std::string fileName) {
	HEAD fileHead;
	HTNode pHT[2 * N];
	HuffmanCode pHC[N];

	std::ifstream fin(fileName, std::ios::in | std::ios::binary);
	std::string newFileName = fileName.erase(fileName.length() - 4);
	newFileName.insert(3, "1_");
	std::ofstream fout(newFileName, std::ios::out | std::ios::binary);

	fin.read((char*)&fileHead, sizeof(HEAD)); //��ȡ�ļ�ͷ
	for (int i = 1; i <= N; i++) {    //�����ļ�ͷ��ʼ��pHT�е�Ȩֵ
		pHT[i].weigthpHT = fileHead.weight[i - 1];
		pHC[i - 1].symbol = (unsigned char)(i - 1);
	}
	CreateHuffmanTree(pHT);           //������������
	HuffmanCoding(pHT, pHC);          //����
	std::string pBuffer;
	while (!fin.eof()) {              //��ѹ���ļ��ж�ȡ�����岢�浽pBuffer��
		char ch = (char)fin.get();
		std::bitset<8> binary(ch);    //��һ���ֽ�ת��Ϊ"01�ַ���"
		pBuffer += binary.to_string();
	}
	int len = pBuffer.length();
	int root = 2 * N - 1;
	for (int i = 0; i < len; i++) {   //ͨ�������������ҵ��������������Ӧ���ֽ�
		if (pHT[root].lchild == 0 && pHT[root].rchild == 0) {
			fout.put((char)(root - 1));
			root = 2 * N - 1;
		}
		root = (pBuffer[i] == '0') ? pHT[root].lchild : pHT[root].rchild;
	}
	
	std::cout << "��ѹ���ɹ�(�ļ��洢��'" + newFileName + "')!";
	fout.close();
	fin.close();
}
