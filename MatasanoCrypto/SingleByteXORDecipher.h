#pragma once
#include <string>
#include "ByteSequence.h"

class SingleByteXORDecipher
{
public:
	SingleByteXORDecipher();
	~SingleByteXORDecipher();

	ByteSequence decipherMessage(const ByteSequence &, const byte_t &key);
	ByteSequence decipherMessage(const ByteSequence &seq, const ByteSequence &key);
protected:
	double metric(const ByteSequence &);
};

