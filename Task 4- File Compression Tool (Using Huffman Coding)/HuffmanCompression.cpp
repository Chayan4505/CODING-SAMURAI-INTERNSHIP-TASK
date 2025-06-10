#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>
using namespace std;

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left, *right;

    HuffmanNode(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

unordered_map<char, int> buildFrequencyTable(const string &data) {
    unordered_map<char, int> freq;
    for (char ch : data) {
        freq[ch]++;
    }
    return freq;
}

void generateCodes(HuffmanNode* root, string code, unordered_map<char, string> &huffmanCode) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }
    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

string compressText(const string &text, unordered_map<char, string> &huffmanCode) {
    string compressed = "";
    for (char ch : text) {
        compressed += huffmanCode[ch];
    }
    return compressed;
}

vector<unsigned char> binaryStringToBytes(const string &binary) {
    vector<unsigned char> bytes;
    for (size_t i = 0; i < binary.size(); i += 8) {
        string byteString = binary.substr(i, 8);
        while (byteString.length() < 8) byteString += '0'; 
        bitset<8> bits(byteString);
        bytes.push_back(static_cast<unsigned char>(bits.to_ulong()));
    }
    return bytes;
}

int main() {
    ifstream input("input.txt", ios::in);
    ofstream output("compressed.bin", ios::binary);

    if (!input || !output) {
        cerr << "Error opening files.\n";
        return 1;
    }

    string text((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());
    input.close();

    unordered_map<char, int> freq = buildFrequencyTable(text);

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (auto pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        HuffmanNode* merged = new HuffmanNode('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }
    HuffmanNode* root = pq.top();

    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    string compressedBinary = compressText(text, huffmanCode);
    vector<unsigned char> compressedBytes = binaryStringToBytes(compressedBinary);

    for (unsigned char byte : compressedBytes) {
        output.put(byte);
    }
    output.close();

    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << endl;
    }

    cout << "\nCompression complete. Compressed data saved to 'compressed.bin'.\n";
    return 0;
}
