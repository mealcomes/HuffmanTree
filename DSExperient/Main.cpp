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
	std::cout << "========== Huffman文件压缩 =========" << endl;
	while (1) {
		std::cout << "\n====================================" << endl;
		std::cout << "1.压缩\n";
		std::cout << "2.解压缩\n";
		std::cout << "0.退出";
		std::cout << "\n====================================" << endl;
		std::cout << "请选择您要进行的操作:";
		std::string choice;
		std::cin >> choice;
		while (!choice._Equal("1") && !choice._Equal("2") && !choice._Equal("0")) {
			std::cout << "不存在该选项！\n请重新输入您要进行的操作:";
			std::cin >> choice;
		}
		if (choice._Equal("0")) {
			std::cout << "欢迎下次使用!";
			return 0;
		}

		std::string fileName;
		std::cout << "请输入文件名:\n";
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