#include "SingleByteXORDecipher.h"

using namespace std;

SingleByteXORDecipher::SingleByteXORDecipher()
{
}


SingleByteXORDecipher::~SingleByteXORDecipher()
{
}

ByteSequence SingleByteXORDecipher::decipherMessage(const ByteSequence &seq, const byte_t &key)
{
	ByteSequence msg = (seq ^ (byte_t)key);
	return msg;
}