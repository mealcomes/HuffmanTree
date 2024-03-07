#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

const int N = 256;
const int M = 2 * N - 1;
struct HTNode
{
	int weigthpHT = 0;  //Ȩֵ
	int parent = 0;     //���ڵ�
	int lchild = 0;     //����
	int rchild = 0;     //�Һ���
};
typedef HTNode* HuffmanTree;
//HTNode pHT[2 * N];  //��������洢Huffman��

struct codetype {
	int start = N - 2;
	char bits[N] = { '\0' };
};
struct HuffmanCode {
	unsigned char symbol;
	codetype code;
};
//HuffmanCode pHC[N];  //��������洢Huffman����

void CreateHuffmanTree(HuffmanTree pHT);   //������������
void HuffmanCoding(HuffmanTree pHT, HuffmanCode pHC[]);  //���ɹ���������
#endif // !_HUFFMAN_H
