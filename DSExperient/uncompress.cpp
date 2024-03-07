#include <iostream>
#include <fstream>
#include<string>
#include<bitset>

#include"Huffman.h"
#include"Compress.h"
#include"Tool.h"

/*解压缩入口*/
void uncompress(std::string fileName) {
	HEAD fileHead;
	HTNode pHT[2 * N];
	HuffmanCode pHC[N];

	std::ifstream fin(fileName, std::ios::in | std::ios::binary);
	std::string newFileName = fileName.erase(fileName.length() - 4);
	newFileName.insert(3, "1_");
	std::ofstream fout(newFileName, std::ios::out | std::ios::binary);

	fin.read((char*)&fileHead, sizeof(HEAD)); //读取文件头
	for (int i = 1; i <= N; i++) {    //根据文件头初始化pHT中的权值
		pHT[i].weigthpHT = fileHead.weight[i - 1];
		pHC[i - 1].symbol = (unsigned char)(i - 1);
	}
	CreateHuffmanTree(pHT);           //创建哈夫曼树
	HuffmanCoding(pHT, pHC);          //编码
	std::string pBuffer;
	while (!fin.eof()) {              //从压缩文件中读取数据体并存到pBuffer中
		char ch = (char)fin.get();
		std::bitset<8> binary(ch);    //将一个字节转化为"01字符串"
		pBuffer += binary.to_string();
	}
	int len = pBuffer.length();
	int root = 2 * N - 1;
	for (int i = 0; i < len; i++) {   //通过哈夫曼树，找到哈夫曼树编码对应的字节
		if (pHT[root].lchild == 0 && pHT[root].rchild == 0) {
			fout.put((char)(root - 1));
			root = 2 * N - 1;
		}
		root = (pBuffer[i] == '0') ? pHT[root].lchild : pHT[root].rchild;
	}
	
	std::cout << "解压缩成功(文件存储在'" + newFileName + "')!";
	fout.close();
	fin.close();
}
