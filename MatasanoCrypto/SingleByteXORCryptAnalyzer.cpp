#include "SingleByteXORCryptAnalyzer.h"
#include "SingleByteXORDecipher.h"

SingleByteXORCryptAnalyzer::SingleByteXORCryptAnalyzer()
{
}


SingleByteXORCryptAnalyzer::~SingleByteXORCryptAnalyzer()
{
}

double SingleByteXORCryptAnalyzer::analyze(const ByteSequence &seq, std::string &decrypted_text)
{
	SingleByteXORDecipher decipher;
	double m_best_metric = 0;
	for (int key = 0; key <= 255; ++key)
	{
		ByteSequence msg = decipher.decipherMessage(seq, key);		
		double crt_metric = metric(msg);
		if (crt_metric > m_best_metric)
		{
			m_best_metric = crt_metric;
			decrypted_text = msg.to_plain_text_string();
		}
	}
	return m_best_metric;
}

double SingleByteXORCryptAnalyzer::metric(const ByteSequence &msg)
{
	int letters = 0;
	for (int i = msg.size() - 1; i >= 0; --i)
	{
		if (isalpha(msg[i]) || isblank(msg[i]))
			++letters;
	}
	return (double)letters / msg.size();
}