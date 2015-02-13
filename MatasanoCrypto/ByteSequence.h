#pragma once

#include <vector>

typedef unsigned char byte_t;

class ByteSequence
{
public:
	ByteSequence();
	ByteSequence(int length);
	ByteSequence(const ByteSequence &seq);
	~ByteSequence();

	const byte_t& operator[](int index) const;
	byte_t& operator[](int index);
	ByteSequence operator^(const ByteSequence &seq) const;
	ByteSequence operator^(byte_t b) const;

	static ByteSequence from_hex_string(std::string);
	static ByteSequence& from_base64_string(std::string);

	std::string to_hex_string();
	std::string to_base64_string();
	std::string to_plain_text_string();

	int size() const;

private:
	std::vector<byte_t> m_storage;

	static byte_t decimal_from_hex(char x);
	static char decimal_to_base64(byte_t x);
	static char decimal_to_hex(byte_t x);

};

