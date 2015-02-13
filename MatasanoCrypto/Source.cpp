
#include "ByteSequence.h"
#include "SingleByteXORDecipher.h"
#include "SingleByteXORCryptAnalyzer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

using namespace std;

int main()
{
	cout << "Set 1. Challenge 1" << endl;
	ByteSequence seq = ByteSequence::from_hex_string("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
	assert(seq.to_base64_string() == "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t");
	cout << "Test passed" << endl << endl;

	cout << "Set 1. Challenge 2" << endl;
	ByteSequence seq1 = ByteSequence::from_hex_string("1c0111001f010100061a024b53535009181c");
	ByteSequence seq2 = ByteSequence::from_hex_string("686974207468652062756c6c277320657965");
	ByteSequence xor_seq = seq1 ^ seq2;
	assert(xor_seq.to_hex_string() == "746865206b696420646f6e277420706c6179");
	cout << "Test passed" << endl << endl;

	cout << "Set 1. Challenge 3" << endl;
	SingleByteXORCryptAnalyzer analyzer;
	std::string possible_message;
	analyzer.analyze(
		ByteSequence::from_hex_string("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"),
		possible_message);
	cout << "Decrypted message:" << possible_message << endl << endl;

	cout << "Set 1. Challenge 4" << endl;
	ifstream fin("4.txt");
	std::string line, decrypted_line;
	double best_prob = 0.0;
	while (fin >> line)
	{
		std::string buffer;
		double prob = analyzer.analyze(ByteSequence::from_hex_string(line), buffer);
		if (prob >= best_prob)
		{
			best_prob = prob;
			decrypted_line = buffer;
		}
	}
	cout << "Decrypted message:" << decrypted_line << endl << endl;

	cout << "Set 1. Challenge 5" << endl;
	seq = ByteSequence::from_plain_text_string("Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal");
	ByteSequence repeating_xor = seq ^ ByteSequence::from_plain_text_string("ICE");
	std::string hex_repeating_xor = repeating_xor.to_hex_string();
	assert(hex_repeating_xor ==
		"0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f");
	cout <<  "Test passed" << endl << endl;
	

	cin.ignore(1);
}