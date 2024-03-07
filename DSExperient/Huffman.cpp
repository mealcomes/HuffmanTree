#define _CRT_SECURE_NO_WARNINGS
#include <limits>
#include<algorithm>
#include <iostream>
#include<string.h>
#include "Huffman.h"
#include"Tool.h"

/*¹¹½¨¹þ·òÂüÊ÷*/
void CreateHuffmanTree(HuffmanTree pHT){
	int nSize = N + 1;
	for (int i = 1; i < N; i++) {
		int x1 = Select(pHT, nSize);
		pHT[x1].parent = nSize;
		int x2 = Select(pHT, nSize);
		pHT[x2].parent = nSize;
		pHT[nSize].lchild = x1;
		pHT[nSize].rchild = x2;
		pHT[nSize].weigthpHT = pHT[x1].weigthpHT + pHT[x2].weigthpHT;
		pHT[nSize].parent = 0;
		nSize++;
	}
	pHT[nSize - 1].parent = 0;
}

/*Éú³É¹þ·òÂü±àÂë*/
void HuffmanCoding(HuffmanTree pHT, HuffmanCode pHC[]) {
	for (int i = 0; i < N; i++) {
		int start = pHC[i].code.start, parent = pHT[i + 1].parent, child = i + 1;
		while (parent != 0) {
			if (pHT[parent].lchild == child) {
				pHC[i].code.bits[start--] = '0';
			}
			else {
				pHC[i].code.bits[start--] = '1';
			}
			child = parent;
			parent = pHT[parent].parent;
		}
		pHC[i].code.bits[start] = '\0';
		pHC[i].code.start = start + 1;
	}
}
