#pragma once
#include <string>
#include <cstdio>
#include <cstring>
#include <assert.h>
#include "HuffmanTree.h"

//使用LongType的原因是防止个数超过了int大小
typedef long long LongType;
struct CharInfo{
//修改3,_ch的范围会超过125
	unsigned char _ch;
	LongType _count;
	string _code;

	//for invalid
	bool operator!=(const CharInfo& info){
		return _count != info._count;
	}

	//for minheap.parent
	CharInfo operator+(const CharInfo& info){
		CharInfo tmp;
		tmp._count = _count + info._count;
		return tmp;
	}

	//for compare
	bool operator<(const CharInfo& info){
		return _count < info._count;
	}
};

class FileCompress{
	typedef HuffmanTreeNode<CharInfo> HTreeNode;
	//临时结构体，用来将源文件的字符和个数传入压缩文件中
	//这里不要传入_code，两个原因
	//第一个：string太大了，而且用不到，浪费空间和时间
	//第二个：我们通过二进制写入压缩文件中，这样是值传递，
	//再次读出来使用的时候，程序会崩溃，因为访问了非法空间。
	struct TmpCharInfo{
		unsigned char _ch;
		LongType _count;
	};
public:
	//constructor
	FileCompress(){
		for(size_t i = 0; i < 256; ++i){
			_infos[i]._ch = i;
			_infos[i]._count = 0;
			_infos[i]._code = " ";
		}
	}

	//Compress 压缩
	void Compress(const char* file){
//修改4，fopen的打开方式，用二进制方式打开
//如果是文本格式的话，会解析失败，因为字符'\0'会
//错误解释为结束符号。
		//统计文件的字符个数
		FILE* fout = fopen(file, "rb");
		assert(fout);
//修改2，fgetc的返回值是整型
		int ch = fgetc(fout);
		while(ch != EOF){
			//需要强转的原因是遇到中文字符的时候，ch是负数
			//但是_infos的范围是0~256，所以强转ch为unsigned char这样才不会越界
			++ _infos[(unsigned char)ch]._count;
			ch = fgetc(fout);
		}
		
		//create HuffmanTree
		CharInfo invilad;
		//因为不是256个字符都会出现，所以就通过设定非法值invilad，并让_count=0
		//在HuffmanTree中不创建
		invilad._count = 0;
		HuffmanTree<CharInfo> tree(_infos, 256, invilad); 
		//code不要初始化，不然会出现编码错误
		//生成编码，并记录到_infos的_code中
		string code;
		GenerateHuffmanTreeCode(tree.GetRoot(), code);
		
		
		//write
		string compressfile = file;
		compressfile += ".huffman";
		//c_str()函数的作用是
		//将c++的 string类转变为c语言风格的字符串
		//fopen接受const char* 参数
		FILE* fin = fopen(compressfile.c_str(), "wb");
		assert(fin);
		
		//write source
		for(int i = 0; i < 256; ++i){
			//非法值不写入
			if(_infos[i]._count != 0){
				TmpCharInfo info;
				info._ch = _infos[i]._ch;
				info._count = _infos[i]._count;
				//二进制写入
				fwrite(&info, sizeof(info), 1, fin);
			}
		}
		//flag of the end of source
		//用来标记源文件字符和个数结束，方便读取停止
		TmpCharInfo info;
		info._count = -1;
		fwrite(&info, sizeof(info), 1, fin);
		
		//write code
		//将文件中的指定位置归为文件起始位置
		fseek(fout, 0, SEEK_SET);
		ch = fgetc(fout);
		//value作为要写入的值，设定为0，
		//当对应位的code是字符1的时候，将该位修改为1
		char value = 0;
		//用来修改对应位，同时当pos为8的时候，
		//表示已经完成一个字节的修改，此时将value写入压缩文件
		size_t pos = 0;
		while(ch != EOF){
			string& code = _infos[(unsigned char)ch]._code;
			for(size_t i = 0; i < code.size(); ++i){
				if(code[i] == '1'){
					value |= (1 << pos);
				}
				else if(code[i] == '0'){
					value &= ~(1 << pos);
				}
				else{
					assert(false);
				}
				++ pos;
				//写入的时候，只能够一个字节一个字节的写
				//所以当8个比特位的时候，写入
				if(pos == 8){
					fputc(value, fin);
					value = pos = 0;
				}
			}
			ch = fgetc(fout);
		}
		//pos > 0表示后面有还未写入压缩文件中的字符
		//将整个value写入，这样会多出几个不需要的0字符。
		//解压缩的时候需要处理
		if(pos > 0){
			fputc(value, fin);
		}
		
		fclose(fout);
		fclose(fin);
	}

	//GenerateHuffmanTreeCode 生成编码，利用递归
	void GenerateHuffmanTreeCode(const HTreeNode* root, string code){
		if(root == NULL)
			return;
		if(root->_left == NULL && root->_right == NULL){
			//change _infos
			_infos[(unsigned char)(root->_val._ch)]._code = code;
			return;
		}
		//如果是左子树，编码为0,；右子树，编码为1
		GenerateHuffmanTreeCode(root->_left, code+'0');
		GenerateHuffmanTreeCode(root->_right, code+'1');
	}

	//unCompress 解压缩
	void UnCompress(const char* file){
		//change the name of file
		//将解压缩的文件名字进行修改，以表示区分
		string uncompressfile = file;
		size_t pos = uncompressfile.rfind('.');
		if(pos == string::npos){
			perror("pos wrong");
			exit(1);
		}
		uncompressfile.erase(pos);
		//cout << uncompressfile << endl;//show "file.unhuffman"
		uncompressfile += ".unhuffman";
		
		//uncompress
		//open fin
		//fin用来存储解压之后的文件
		FILE* fin = fopen(uncompressfile.c_str(), "wb");
		assert(fin);
		//read to get ch and count
		//打开源文件获取源文件的字符和个数，用来重建HuffmanTree
		FILE* fout = fopen(file, "rb");
		assert(fout);
		TmpCharInfo info;
		fread(&info, sizeof(info), 1, fout);
		while(info._count != -1){
			_infos[(unsigned char)info._ch]._ch = info._ch;
			_infos[(unsigned char)info._ch]._count = info._count;
			fread(&info, sizeof(info), 1, fout);
		}
		//create HuffmanTree
		//重新构造HuffmanTree的目的是为了解压的时候，可以有参考
		//从而知道每个编码对应的字符是什么
		CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo> tree(_infos, 256, invalid);
		HTreeNode* root = tree.GetRoot();
		HTreeNode* cur = root;
		//num表示所有字符个数之和，用来控制解压的个数。
		LongType num = root->_val._count;
		int ch = fgetc(fout);
//修改1，解决文件中只有一个字符的情况
		//olny root
		if(root->_left == NULL){
			while(num--){
				fputc(root->_val._ch, fin);
			}
		}
		//more than root
		else{
			while(ch != EOF){
				for(size_t i = 0; i < 8; ++i){
					//cout << (ch&(1<<i)) << endl;
					//只用来判断是否等于零即可
					//左边为0
					if(((unsigned char)ch & (1 << i)) == 0){
						cur = cur->_left;
					}
					//右边为1
					else{
						cur = cur->_right;
					}
					if(cur->_left == NULL && cur->_right == NULL){
						//当解压字符个数达到压缩字符个数，跳出循环
						//避免当初压缩的时候多添加的无用字符被写入文件中
						if(num-- == 0){
							break;
						}
						fputc(cur->_val._ch, fin);
						cur = root;
					}
				}
				ch = fgetc(fout);
			}
		}
		fclose(fin);
		fclose(fout);
	}

protected:
	//一共只有256个字符，所以可以直接定义一个数组
	CharInfo _infos[256];
};

void TestFileCompress(){
	FileCompress fc;
	FileCompress fcu;
	fc.Compress("file");
	fcu.UnCompress("file.huffman");
}
