
#include "ByteSequence.h"
#include "SingleByteXORDecipher.h"
#include "SingleByteXORCryptAnalyzer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
	cout << "Set 1. Challenge 1" << endl;
	ByteSequence seq = ByteSequence::from_hex_string("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
	cout << seq.to_base64_string() << endl << endl;

	cout << "Set 1. Challenge 2" << endl;
	ByteSequence seq1 = ByteSequence::from_hex_string("1c0111001f010100061a024b53535009181c");
	ByteSequence seq2 = ByteSequence::from_hex_string("686974207468652062756c6c277320657965");
	ByteSequence xor_seq = seq1 ^ seq2;
	cout << xor_seq.to_hex_string() << endl << endl;

	cout << "Set 1. Challenge 3" << endl;
	SingleByteXORCryptAnalyzer analyzer;
	std::string possible_message;
	analyzer.analyze(
		ByteSequence::from_hex_string("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"),
		possible_message);
	cout << possible_message << endl << endl;

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
	cout << decrypted_line << endl << endl;

	cout << "Set 1. Challenge 5" << endl;

	cout << endl << endl;

	cin.ignore(1);
}