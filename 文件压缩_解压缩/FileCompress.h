/**************************2016-8-22*******************************************
��Ŀ���ƣ��ļ�ѹ�����ѹ��
��Ŀ��飺����Huffman����ʵ��
ʵ�ֹ��̣�
		������С������������������
		���ɹ��������벢�����㣻
		���ַ�����������������д��ѹ���ļ���
		������������Ϣд�������ļ������ѹ��ʱ������
		���������ļ�������
		����ѹ���ļ����ַ���
		д���ѹ���ļ���
******************************************************************************/
#pragma once

#include "HuffmanTree.h"
#include <string>
#include <queue>
#include <algorithm>

#define _DEBUG_

typedef long  longType;

/******************************************************************************
struct CharInfo
*******************************************************************************/
struct CharInfo
{
	unsigned char _ch;
	longType _Count;
	string _code;

	CharInfo(longType Count = 0)
		:_Count(Count)
		, _ch(0)
	{}
/******************************************************************************
���غ�����
CharInfo operator+(const CharInfo& info)
bool operator < (const CharInfo& info) const
bool operator !=(const CharInfo& info) const
*******************************************************************************/
	CharInfo operator+(const CharInfo& info)
	{
		return CharInfo(_Count + info._Count);
	}
	bool operator < (const CharInfo& info) const
	{
		return _Count < info._Count;
	}
	bool operator !=(const CharInfo& info) const
	{
		return info._Count != _Count;
	}
};


ostream& operator<<(ostream& os, const CharInfo& info)
{
	os << info._ch << ":" << info._Count;

	return os;
}


/******************************************************************************
template<class T>
class FileCompress
*******************************************************************************/
template<class T>
class FileCompress
{
public:
	//���ַ�����д��_infos[]
	FileCompress()
	{
		for (size_t i = 0; i < 256; ++i)
		{
			_infos[i]._ch = i;
		}
	}
public:

/*******************************************************************************
�������ƣ�_GenerateHuffmanCode
����������HuffmanTreeNode<CharInfo>* root	Huffmantree�ĸ��ڵ�
�� �� ֵ��void
�������ܣ�����Huffman����
*******************************************************************************/
	void _GenerateHuffmanCode(HuffmanTreeNode<CharInfo>* root)
	{
		if (root == NULL)
		{
			return;
		}
		//�ݹ���Ҷ�ӽڵ�
		_GenerateHuffmanCode(root->_left);
		_GenerateHuffmanCode(root->_right);

		if (root->_left == NULL && root->_right == NULL)//��Ҷ�Ӳű���
		{
			HuffmanTreeNode<CharInfo>* cur = root;
			HuffmanTreeNode<CharInfo>* parent = cur->_parent;
			string &code = _infos[cur->_weight._ch]._code;
			while (parent)
			{
				if (parent->_left == cur)
				{
					code += '0';
				}
				else
				{
					code += '1';
				}
				cur = parent;
				parent = cur->_parent;
			}
			//��Ҷ�ӵ������ҵģ�����Ҫ����. 
			reverse(code.begin(), code.end());
		}
	}
	
/*******************************************************************************
�������ƣ�GetHuffmanCode
����������HuffmanTreeNode<CharInfo> *root	Huffmantree�ĸ��ڵ�
�� �� ֵ��void
�������ܣ���ȡHuffman���� 
*******************************************************************************/
	void GetHuffmanCode(HuffmanTreeNode<CharInfo> *root)
	{
		queue<HuffmanTreeNode<CharInfo>* > q;
		if (root)
		{
			q.push(root);
		}

		while (!q.empty())
		{
			HuffmanTreeNode<CharInfo>* node = q.front();
			if (node->_left == NULL && node->_right == NULL)//��Ҷ�ӲŴ�ӡ
			{
				//cout << node->_weight << " ";
			}
			if (node->_left)
			{
				q.push(node->_left);
			}
			if (node->_right)
			{
				q.push(node->_right);
			}
			q.pop();
		}

		cout << endl;
	}

/*******************************************************************************
�������ƣ�Compress
����������const char*filename		char* ���͵��ļ�����
�� �� ֵ��bool
�������ܣ�ʵ���ļ�ѹ��
*******************************************************************************/
	bool Compress(const char*filename)
	{
		assert(filename);

		long long charCount = 0;
		//���ļ���ͳ���ַ����ֵ�����
		FILE* fOut = fopen(filename, "rb");
		assert(fOut);

		char ch = fgetc(fOut);
		while (ch != EOF)
		{
			_infos[(unsigned char)ch]._Count++;
			ch = fgetc(fOut);
			charCount++;
		}

		//������������,���ɶ�Ӧ�Ĺ���������
		HuffmanTree<CharInfo> t;
		CharInfo invalid = CharInfo();
		t.CreatTree(_infos, 256, invalid);

		_GenerateHuffmanCode(t.GetTreeRoot());
#ifdef _DEBUG_
		GetHuffmanCode(t.GetTreeRoot());
#endif
		cout << endl;

		//����ѹ���ļ�
		string CompressFile = filename;
		CompressFile += ".huffman";
		FILE *finCompress = fopen(CompressFile.c_str(), "wb");
		assert(finCompress);

		//����������д��ѹ���ļ�

		/*�ض�λ��(������/�ļ�)�ϵ��ļ��ڲ�λ��ָ��
		int fseek(FILE *stream, long offset, int fromwhere);���������ļ�ָ��stream��λ��*/
		fseek(fOut, 0, SEEK_SET);
		ch = fgetc(fOut);
		char inch = 0;
		int index = 0;
		while (ch != EOF)	
		{
			string& code = _infos[(unsigned char)ch]._code;
#ifdef _DEBUG_
			//cout << code << "->";
#endif
			for (size_t i = 0; i < code.size(); ++i)
			{
				++index;
				inch <<= 1;
				if (code[i] == '1')
				{
					inch |= 1;
				}
				//һ���ַ�һ���ֽ�
				if (index == 8)
				{
					fputc(inch, finCompress);
					index = 0;
					inch = 0;
				}
			}
			ch = fgetc(fOut);
		}
		if (index != 0)
		{
			inch <<= (8 - index);
			fputc(inch, finCompress);
		}
		//���������ļ�������������Ϣ
		string configFileName = filename;
		configFileName += ".config";
		FILE* fInConfig = fopen(configFileName.c_str(), "wb");
		assert(fInConfig);

		//д���ַ�����,��д��λ����д��λ
		char CountStr[100];
		itoa(charCount >> 32, CountStr, 10);
		fputs(CountStr, fInConfig);
		fputc('\n', fInConfig);

		itoa(charCount & 0xFFFFFFFF, CountStr, 10);
		fputs(CountStr, fInConfig);
		fputc('\n', fInConfig);

		string infoStr;
		for (int i = 0; i < 256; ++i)
		{
			if (_infos[i] != invalid)
			{
				infoStr += _infos[i]._ch;
				infoStr += ',';
				itoa(_infos[i]._Count, CountStr, 10);
				infoStr += CountStr;
				infoStr += '\n';
				fputs(infoStr.c_str(), fInConfig);

				infoStr.clear();
			}
		}

		fclose(finCompress);
		fclose(fOut);
		fclose(fInConfig);
		return true;
	}
	
/*******************************************************************************
�������ƣ�ReadLine
����������FILE* fOut		�ļ�ָ��
		 string& line	
�� �� ֵ��bool
�������ܣ���һ��
*******************************************************************************/
	bool ReadLine(FILE* fOut, string& line)
	{
		char ch = fgetc(fOut);
		if (ch == EOF)
		{
			return false;
		}
		while (ch != EOF && ch != '\n')
		{
			line += ch;
			ch = fgetc(fOut);
		}
		return true;
	}

/*******************************************************************************
�������ƣ�UnCompress
����������const char*filename	char* ���͵��ļ�����
�� �� ֵ��bool
�������ܣ�ʵ���ļ���ѹ��
*******************************************************************************/
	bool UnCompress(const char*filename)
	{
		assert(filename);
		//�������ļ�,����
		string configFileName = filename;
		configFileName += ".config";
		FILE* fOutConfig = fopen(configFileName.c_str(), "rb");
		assert(fOutConfig);

		//���ļ����ַ������ȶ���λ���ٶ���λ
		string line;
		string CountStr;
		ReadLine(fOutConfig, line);
		CountStr += line;
		line.clear();
		ReadLine(fOutConfig, line);
		CountStr += line;
		long long Count = atoi(CountStr.c_str());
		line.clear();

		//��ʼ�������ļ�����
		char ch = 0;
		while (ReadLine(fOutConfig, line))
		{
			if (!line.empty())
			{
				ch = line[0];
				_infos[(unsigned char)(ch)]._Count = atoi(line.substr(2).c_str());
				line.clear();
			}
			else//����Ϊ���з�
			{
				line = '\n';
			}
		}
		//������_infos,��ʼ����

		HuffmanTree<CharInfo> t;
 		CharInfo invalid(0);
		t.CreatTree(_infos, 256, invalid);

		//��������������ѹ���ļ���ı��뿪ʼ��ѹ��
		string uncompressFileName = filename;
		uncompressFileName += ".Uncompress";
		FILE* fOut = fopen(uncompressFileName.c_str(), "wb");

		string compressFileName = filename;
		compressFileName += ".huffman";
		FILE* fIn = fopen(compressFileName.c_str(), "rb");

		ch = fgetc(fIn);
		int pos = 8;
		HuffmanTreeNode<CharInfo>* root = t.GetTreeRoot();
		HuffmanTreeNode<CharInfo>* cur = root;
		while (1)
		{
			if (cur->_left == NULL && cur->_right == NULL)
			{
				fputc(cur->_weight._ch, fOut);
				cur = root;
				if (--Count == 0)
					break;
			}
			--pos;
			if (ch & (1 << pos))
				cur = cur->_right;
			else
				cur = cur->_left;
			if (pos == 0)
			{
				ch = fgetc(fIn);
				pos = 8;
			}
		}

		fclose(fOutConfig);
		fclose(fOut);
		fclose(fIn);
		return true;
	}
protected:
	CharInfo _infos[256];
};