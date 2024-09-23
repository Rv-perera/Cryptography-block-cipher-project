#include <iostream>
#include <bitset>
#include <vector>
#include <string>

using namespace std;

// Convert string to vector of 8-bit ASCII integers
vector<int> string_to_blocks(string plaintext) {
    vector<int> blocks;
    for (char c : plaintext) {
        blocks.push_back(int(c));
    }
    return blocks;
}

// Convert vector of 8-bit integers back to string
string blocks_to_string(vector<int> blocks) {
    string plaintext;
    for (int block : blocks) {
        plaintext += char(block);
    }
    return plaintext;
}

int main() {
    string plaintext = "HELLO";
    int key = 0b10101100;  // Example key
    int iv = 0b00101101;   // Initialization Vector for CBC

    // Convert plaintext to blocks
    vector<int> blocks = string_to_blocks(plaintext);

    // ECB Mode
    vector<int> encrypted_ecb = ecb_encrypt(blocks, key);
    vector<int> decrypted_ecb = ecb_decrypt(encrypted_ecb, key);

    cout << "ECB Mode:" << endl;
    cout << "Original Plaintext: " << plaintext << endl;
    cout << "Encrypted ECB: ";
    for (int block : encrypted_ecb) {
        cout << bitset<8>(block) << " ";
    }
    cout << endl;
    cout << "Decrypted ECB: " << blocks_to_string(decrypted_ecb) << endl;

    // CBC Mode
    vector<int> encrypted_cbc = cbc_encrypt(blocks, key, iv);
    vector<int> decrypted_cbc = cbc_decrypt(encrypted_cbc, key, iv);

    cout << "CBC Mode:" << endl;
    cout << "Original Plaintext: " << plaintext << endl;
    cout << "Encrypted CBC: ";
    for (int block : encrypted_cbc) {
        cout << bitset<8>(block) << " ";
    }
    cout << endl;
    cout << "Decrypted CBC: " << blocks_to_string(decrypted_cbc) << endl;

    return 0;
}
