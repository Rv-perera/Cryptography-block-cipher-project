#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

// ECB Mode Encryption
vector<int> ecb_encrypt(vector<int> blocks, int key) {
    vector<int> encrypted_blocks;
    for (int block : blocks) {
        encrypted_blocks.push_back(encrypt(block, key));
    }
    return encrypted_blocks;
}

// ECB Mode Decryption
vector<int> ecb_decrypt(vector<int> encrypted_blocks, int key) {
    vector<int> decrypted_blocks;
    for (int block : encrypted_blocks) {
        decrypted_blocks.push_back(decrypt(block, key));
    }
    return decrypted_blocks;
}

// CBC Mode Encryption
vector<int> cbc_encrypt(vector<int> blocks, int key, int iv) {
    vector<int> encrypted_blocks;
    int previous_block = iv;
    for (int block : blocks) {
        int xor_block = block ^ previous_block;  // XOR with previous ciphertext block
        int encrypted_block = encrypt(xor_block, key);
        encrypted_blocks.push_back(encrypted_block);
        previous_block = encrypted_block;
    }
    return encrypted_blocks;
}

// CBC Mode Decryption
vector<int> cbc_decrypt(vector<int> encrypted_blocks, int key, int iv) {
    vector<int> decrypted_blocks;
    int previous_block = iv;
    for (int block : encrypted_blocks) {
        int decrypted_block = decrypt(block, key);
        decrypted_blocks.push_back(decrypted_block ^ previous_block);
        previous_block = block;
    }
    return decrypted_blocks;
}

int main() {
    int key = 0b10101100;  // Example key
    int iv = 0b00101101;   // Initialization Vector for CBC

    // Define blocks to encrypt
    vector<int> blocks = {0b11001010, 0b10100101, 0b11110000};

    // ECB Mode
    vector<int> encrypted_ecb = ecb_encrypt(blocks, key);
    vector<int> decrypted_ecb = ecb_decrypt(encrypted_ecb, key);

    cout << "ECB Mode:" << endl;
    for (int block : encrypted_ecb) {
        cout << "Encrypted: " << bitset<8>(block) << endl;
    }
    for (int block : decrypted_ecb) {
        cout << "Decrypted: " << bitset<8>(block) << endl;
    }

    // CBC Mode
    vector<int> encrypted_cbc = cbc_encrypt(blocks, key, iv);
    vector<int> decrypted_cbc = cbc_decrypt(encrypted_cbc, key, iv);

    cout << "CBC Mode:" << endl;
    for (int block : encrypted_cbc) {
        cout << "Encrypted: " << bitset<8>(block) << endl;
    }
    for (int block : decrypted_cbc) {
        cout << "Decrypted: " << bitset<8>(block) << endl;
    }

    return 0;
}
