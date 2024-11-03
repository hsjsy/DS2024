#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <cstring>

class BinNode
{
public:
    char data;      // �洢�ַ�
    int freq;       // �洢Ƶ��
    BinNode* left;  // ������
    BinNode* right; // ������

    BinNode(char d, int f)
        : data(d), freq(f), left(nullptr), right(nullptr)
    {
    }
};

// ���ȶ��бȽ���
struct Compare
{
    bool operator()(BinNode* l, BinNode* r)
    {
        return l->freq > r->freq; // С����
    }
};


class HuffTree
{
private:
    BinNode* root;

public:
    HuffTree(const std::unordered_map<char, int>& freqMap)
    {
        std::priority_queue<BinNode*, std::vector<BinNode*>, Compare> minHeap;

        for (const auto& pair : freqMap)
        {
            minHeap.push(new BinNode(pair.first, pair.second));
        }

        while (minHeap.size() > 1)
        {
            BinNode* left = minHeap.top();
            minHeap.pop();
            BinNode* right = minHeap.top();
            minHeap.pop();
            BinNode* newNode = new BinNode('\0', left->freq + right->freq);
            newNode->left = left;
            newNode->right = right;
            minHeap.push(newNode);
        }

        root = minHeap.top(); // ���յĸ��ڵ�
    }

    BinNode* getRoot()
    {
        return root;
    }

    // �ͷ��ڴ�
    ~HuffTree()
    {
        // ��ʵ��һ���ݹ��ͷź���
        deleteTree(root);
    }

private:
    void deleteTree(BinNode* node)
    {
        if (node)
        {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
};


class HuffCode
{
public:
    std::unordered_map<char, std::string> codes;

    void generateCodes(BinNode* root, const std::string& str)
    {
        if (!root) return;

        if (root->data != '\0')
        {
            codes[root->data] = str; // Ҷ�ڵ�
        }

        generateCodes(root->left, str + "0");
        generateCodes(root->right, str + "1");
    }
};


void huffmanCoding(const std::string& text)
{
    std::unordered_map<char, int> freqMap;

    // ͳ���ַ�Ƶ��
    for (char c : text)
    {
        if (isalpha(c))
        {
            c = tolower(c); // �����ִ�Сд
            freqMap[c]++;
        }
    }

    // ����Huffman��
    HuffTree huffTree(freqMap);
    HuffCode huffCode;
    huffCode.generateCodes(huffTree.getRoot(), "");

    // ���������
    std::ofstream outFile("result.txt");
    for (const auto& pair : huffCode.codes)
    {
        outFile << pair.first << ": " << pair.second << std::endl;
    }

    // ���뵥��
    std::string words[] = {"dream", "example", "huffman"};
    for (const std::string& word : words)
    {
        std::string encodedWord;
        for (char c : word)
        {
            c = tolower(c);
            encodedWord += huffCode.codes[c];
        }
        outFile << word << ": " << encodedWord << std::endl;
    }

    outFile.close();
}


int main()
{
    // std::ifstream inFile("text.txt");
    std::ifstream inFile("E:\\�㷨�����ݽṹ\\ʵ��\\exp3\\text.txt");
    std::string text((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    huffmanCoding(text);

    return 0;
}
