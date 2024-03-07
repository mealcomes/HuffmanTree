#ifndef _TOOL_H_
#define _TOOL_H_
#include<string>
#include"Huffman.h"
#include"Compress.h"
#define POINT_INFO 1   
#define CODE_INFO 2

int readWeight(std::string fileName, int weight[], HTNode pHT[], HuffmanCode pHC[]); //��ȡȨֵ
void PrintWeight(int weight[]);                                                      //�����ʼȨֵ
void TestHufTree(HuffmanTree pHT);										             //����������������ڵ���Ϣ
void TestHufTreeN(HuffmanTree pHT, HuffmanCode pHC[], int root);					 //���������������ڵ���Ϣ
int Select(HuffmanTree pHT, int nSize);												 //������������ʱѡ��Ȩֵ��С�Ľ��
void TestHufCode(HuffmanCode pHC[], HuffmanTree pHT, int root);                      //��������������������
void PreTravelHuffTree(HuffmanTree pHT, HuffmanCode pHC[], int root, int flag);      //��������������� flag(1:��������Ϣ 2:���Ҷ�ӽ�����)
void IniteHead(std::string fileName, HEAD& fileHead);								 //��ʼ���ļ�ͷ
int writeFile(const std::string fileName, const HEAD fileHead, const char* pBuffer, const int nSize);//��ѹ���������д���ļ�
char Str2byte(const char pBinStr[]);												 //����01���ַ���ת��Ϊ�ֽ�
#endif // !_READWEIGHT_H_
