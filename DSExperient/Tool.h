#ifndef _TOOL_H_
#define _TOOL_H_
#include<string>
#include"Huffman.h"
#include"Compress.h"
#define POINT_INFO 1   
#define CODE_INFO 2

int readWeight(std::string fileName, int weight[], HTNode pHT[], HuffmanCode pHC[]); //读取权值
void PrintWeight(int weight[]);                                                      //输出初始权值
void TestHufTree(HuffmanTree pHT);										             //输出哈夫曼树各个节点信息
void TestHufTreeN(HuffmanTree pHT, HuffmanCode pHC[], int root);					 //先序遍历输出各个节点信息
int Select(HuffmanTree pHT, int nSize);												 //构建哈夫曼树时选择权值最小的结点
void TestHufCode(HuffmanCode pHC[], HuffmanTree pHT, int root);                      //先序遍历输出哈夫曼编码
void PreTravelHuffTree(HuffmanTree pHT, HuffmanCode pHC[], int root, int flag);      //先序遍历哈夫曼树 flag(1:输出结点信息 2:输出叶子结点编码)
void IniteHead(std::string fileName, HEAD& fileHead);								 //初始化文件头
int writeFile(const std::string fileName, const HEAD fileHead, const char* pBuffer, const int nSize);//将压缩后的数据写入文件
char Str2byte(const char pBinStr[]);												 //将“01”字符串转化为字节
#endif // !_READWEIGHT_H_
