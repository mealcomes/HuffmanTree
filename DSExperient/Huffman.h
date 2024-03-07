#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

const int N = 256;
const int M = 2 * N - 1;
struct HTNode
{
	int weigthpHT = 0;  //权值
	int parent = 0;     //父节点
	int lchild = 0;     //左孩子
	int rchild = 0;     //右孩子
};
typedef HTNode* HuffmanTree;
//HTNode pHT[2 * N];  //分配数组存储Huffman树

struct codetype {
	int start = N - 2;
	char bits[N] = { '\0' };
};
struct HuffmanCode {
	unsigned char symbol;
	codetype code;
};
//HuffmanCode pHC[N];  //分配数组存储Huffman编码

void CreateHuffmanTree(HuffmanTree pHT);   //构建哈夫曼树
void HuffmanCoding(HuffmanTree pHT, HuffmanCode pHC[]);  //生成哈弗曼编码
#endif // !_HUFFMAN_H
