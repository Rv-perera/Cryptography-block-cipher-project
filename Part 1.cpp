#include <iostream>
#include <bitset>

using namespace std;

// Define Block and Key Sizes
const int BLOCK_SIZE = 8;  // Block size in bits
const int KEY_SIZE = 8;    // Key size in bits

// Implement a Simple Substitution Box (S-box)
const int S_BOX[16] = {
    0b1110, 0b0100, 0b1101, 0b0001,
    0b0010, 0b1111, 0b1011, 0b1000,
    0b0011, 0b1010, 0b0110, 0b1100,
    0b0101, 0b1001, 0b0000, 0b0111
};

int substitute(int nibble) {
    return S_BOX[nibble];
}

// Implement a Simplified Permutation
const int PERMUTATION_TABLE[8] = {1, 5, 2, 0, 3, 7, 4, 6};

int permute(int block) {
    int permuted_block = 0;
    for (int i = 0; i < 8; i++) {
        int bit = (block >> PERMUTATION_TABLE[i]) & 1;
        permuted_block |= (bit << i);
    }
    return permuted_block;
}

// Implement a Basic Feistel Function
int feistel_function(int right_half, int key) {
    return right_half ^ key;
}

// Combine Components for Encryption
int encrypt(int block, int key) {
    int left_half = (block >> 4) & 0x0F;
    int right_half = block & 0x0F;
    int feistel_output = feistel_function(right_half, key);
    int new_right_half = left_half ^ feistel_output;
    int substituted_left = substitute(new_right_half);
    int substituted_right = substitute(right_half);
    int combined_block = (substituted_left << 4) | substituted_right;
    return permute(combined_block);
}

// Combine Components for Decryption
int decrypt(int block, int key) {
    int permuted_block = permute(block);  // Reverse the permutation
    int left_half = (permuted_block >> 4) & 0x0F;
    int right_half = permuted_block & 0x0F;
    int substituted_left = substitute(left_half);
    int substituted_right = substitute(right_half);
    int combined_block = (substituted_left << 4) | substituted_right;
    int feistel_output = feistel_function(substituted_right, key);
    int decrypted_left = combined_block ^ feistel_output;
    return decrypted_left;
}

int main() {
    // Example block and key (8 bits each)
    int block = 0b11001100;  // Example block
    int key = 0b10101010;    // Example key

    // Encrypt and decrypt the block using the key
    int encrypted_block = encrypt(block, key);
    int decrypted_block = decrypt(encrypted_block, key);

    cout << "Original Block: " << bitset<8>(block) << endl;
    cout << "Encrypted Block: " << bitset<8>(encrypted_block) << endl;
    cout << "Decrypted Block: " << bitset<8>(decrypted_block) << endl;

    return 0;
}
