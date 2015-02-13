#pragma once

#include "ByteSequence.h"
#include <string>

class SingleByteXORCryptAnalyzer
{
public:
	SingleByteXORCryptAnalyzer();
	~SingleByteXORCryptAnalyzer();

	// returns the probability of a bytesequence 
	// being crypted by single byte XOR-ing
	double analyze(const ByteSequence &, std::string &decrypted_text);
	double metric(const ByteSequence &msg);
private:
	double m_best_metric = 0;
};

