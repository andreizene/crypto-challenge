#include "ByteSequence.h"
#include <assert.h>

#define FIRST_64_DIGIT(a) ((a) >> 2)
#define SECOND_64_DIGIT(a, b) ((((a) << 4) | ((b) >> 4)) & 0x3F)
#define THIRD_64_DIGIT(a, b) ((((a) << 2) | ((b) >> 6)) &  0x3F)
#define FOURTH_64_DIGIT(a) ((a) & 0x3F) 

#define FIRST_16_DIGIT(a) ((a) >> 4)
#define LAST_16_DIGIT(a) ((a) & 0x0F)

using namespace std;

ByteSequence::ByteSequence()
{
}

ByteSequence::ByteSequence(int length)
{
	m_storage.resize(length);
}

ByteSequence::ByteSequence(const ByteSequence &seq)
{
	m_storage = seq.m_storage;
}

ByteSequence::~ByteSequence()
{
}

const byte_t& ByteSequence::operator[] (int i) const
{
	return m_storage[i];
}

byte_t& ByteSequence::operator[] (int i)
{
	return m_storage[i];
}


// if right operand is shorter than left operand, this is going to 
// use reapeating-key XOR
ByteSequence ByteSequence::operator^ (const ByteSequence &seq) const
{
	assert(seq.size() <= this->size());
	
	int seq_size = seq.size();
	ByteSequence new_seq(this->size());
	for (int i = this->size() - 1; i >= 0; --i)
	{
		new_seq[i] = (*this)[i] ^ seq[i % seq_size];
	}
	
	return new_seq;
}

ByteSequence ByteSequence::operator^ (byte_t b) const
{
	int size = this->size();
	ByteSequence new_seq(size);
	for (int i = size - 1; i >= 0; --i)
	{
		new_seq[i] = (*this)[i] ^ b;
	}

	return new_seq;
}

int ByteSequence::size() const
{
	return m_storage.size();
}

ByteSequence ByteSequence::from_hex_string(std::string str)
{
	int seq_length = str.length() / 2 + str.length() % 2;
	ByteSequence seq(seq_length);

	int pos = str.length() - 1;
	while (pos >= 0)
	{
		byte_t byte;
		byte = decimal_from_hex(str[pos]);
		if (pos - 1 >= 0) 
			byte |= (decimal_from_hex(str[pos - 1]) << 4);
		seq[--seq_length] = byte;
		pos -= 2;
	}

	return seq;
}

ByteSequence& ByteSequence::from_base64_string(std::string)
{
	// TODO:
	return ByteSequence(0);
}

ByteSequence ByteSequence::from_plain_text_string(std::string str)
{
	ByteSequence seq;

	seq.m_storage = vector<byte_t>(str.begin(), str.end());

	return seq;
}

std::string ByteSequence::to_base64_string()
{
	int b64_length = 4 * m_storage.size() / 3 + ((m_storage.size()) % 3 ? 1 : 0);
	string base64(b64_length, '0');

	int bytes_pos = m_storage.size();
	while (--bytes_pos >= 0)
	{
		base64[--b64_length] = decimal_to_base64(FOURTH_64_DIGIT(m_storage[bytes_pos]));
		if (bytes_pos >= 0)
			base64[--b64_length] = decimal_to_base64(THIRD_64_DIGIT(
												(bytes_pos - 1 >= 0 ? m_storage[bytes_pos - 1] : 0), 
												m_storage[bytes_pos]));
		if (--bytes_pos >= 0)
			base64[--b64_length] = decimal_to_base64(SECOND_64_DIGIT(
												(bytes_pos - 1 >= 0 ? m_storage[bytes_pos - 1] : 0),
												m_storage[bytes_pos]));
		if (--bytes_pos >= 0)
			base64[--b64_length] = decimal_to_base64(FIRST_64_DIGIT(m_storage[bytes_pos]));
	}
	
	return base64;
}

std::string ByteSequence::to_hex_string()
{
	int hex_length = 2 * m_storage.size();
	string hex(hex_length, '0');

	int bytes_pos = m_storage.size();
	while (--bytes_pos >= 0)
	{
		hex[--hex_length] = decimal_to_hex(LAST_16_DIGIT(m_storage[bytes_pos]));
		hex[--hex_length] = decimal_to_hex(FIRST_16_DIGIT(m_storage[bytes_pos]));
	}

	return hex;
}

std::string ByteSequence::to_plain_text_string()
{
	return string (m_storage.begin(), m_storage.end());
}

byte_t ByteSequence::decimal_from_hex(char x)
{
	if (x >= '0' && x <= '9')
	{
		return x - '0';
	}

	if (x >= 'A' && x <= 'F')
	{
		return x - 'A' + 10;
	}

	if (x >= 'a' && x <= 'f')
	{
		return x - 'a' + 10;
	}

	return 255;
}

char ByteSequence::decimal_to_hex(byte_t x)
{
	if (x >= 0 && x <= 9)
	{
		return x + '0';
	}

	if (x >= 10 && x <= 15)
	{
		return x + 'a' - 10;
	}

	return '\0';
}

char ByteSequence::decimal_to_base64(byte_t x)
{
	if (x >= 0 && x <= 25)
	{
		return x + 'A';
	}

	if (x >= 26 && x <= 51)
	{
		return x + 'a' - 26;
	}

	if (x >= 52 && x <= 61)
	{
		return x + '0' - 52;
	}

	if (x == 62)
	{
		return '+';
	}

	if (x == 63)
	{
		return '/';
	}

	return '\0';
}