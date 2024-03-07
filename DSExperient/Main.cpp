#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<queue>
#include<string>
#include<bitset>

#include"Compress.h"
#include"Huffman.h"
#include"uncompress.h"
#include "Tool.h"

#define endl '\n'

int main() {
	std::cout << "========== Huffman�ļ�ѹ�� =========" << endl;
	while (1) {
		std::cout << "\n====================================" << endl;
		std::cout << "1.ѹ��\n";
		std::cout << "2.��ѹ��\n";
		std::cout << "0.�˳�";
		std::cout << "\n====================================" << endl;
		std::cout << "��ѡ����Ҫ���еĲ���:";
		std::string choice;
		std::cin >> choice;
		while (!choice._Equal("1") && !choice._Equal("2") && !choice._Equal("0")) {
			std::cout << "�����ڸ�ѡ�\n������������Ҫ���еĲ���:";
			std::cin >> choice;
		}
		if (choice._Equal("0")) {
			std::cout << "��ӭ�´�ʹ��!";
			return 0;
		}

		std::string fileName;
		std::cout << "�������ļ���:\n";
		std::cin >> fileName;

		if (choice._Equal("1")) {
			Compress(fileName);

		}
		else if (choice._Equal("2")) {
			uncompress(fileName);

		}
	}
	return 0;
}