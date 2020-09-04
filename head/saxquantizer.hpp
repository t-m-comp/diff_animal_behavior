/*
Copyright (c) 2014 Mohamed Elsabagh <melsabag@gmu.edu>
 
Permission is hereby granted, free of charge, to any person obtaining a copy of this 
software and associated documentation files (the "Software"), to deal in the Software 
without restriction, including without limitation the rights to use, copy, modify, 
merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies 
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
DEALINGS IN THE SOFTWARE.
*/

#ifndef SAXQUANTIZER_HPP
#define SAXQUANTIZER_HPP

#include <deque>
#include <vector>
#include <cassert>
#include <iostream>
#include <boost/math/distributions/normal.hpp>

using std::deque;
using std::vector;


namespace SaxQuantizer
{

	/**
	 * Helper routine to generate the SAX codebook (list of cutpoints) of a given size
	 * @param <alphabet_size>: number of desired codewords
	 * @param <cutpoints> (out): resulting codebook
	 */
	inline void fill_cutpoints(size_t alphabet_size, vector<double> *cutpoints)
	{
		assert(alphabet_size > 0);
		static boost::math::normal dist(0.0, 1.0);
		//std::cout << "alphabet: " << alphabet_size << std::endl;
		cutpoints->reserve(alphabet_size);
		cutpoints->push_back(-DBL_MAX);
		for (size_t i = 1; i < alphabet_size; ++i)
		{
			double cdf = ((double) i) / alphabet_size;
			cutpoints->push_back(quantile(dist, cdf));
		}
	}

	/**
	 * Symbolic Aggregate Approximation with fractional sliding window, numerosity reduction, and scaling
	 */
	class Sax
	{
		private:
		size_t m_window_size;
		size_t m_string_size;
		size_t m_alphabet_size;

		double m_baseline_mean;
		double m_baseline_stdev;
		vector<double> m_cutpoints;
		vector<double> input;

		bool m_trained;

		/**
		 * SAX with fractional sliding window and automatic scaling.
		 * @param <it>: start iterator
		 * @param <end>: end iterator
		 * @param <syms> (out): quantized range
		 */
		//template<class Iter>
		void saxify(vector<int> & syms)
		{
		  // map to symbols. 0-based.
			for (size_t i = 0; i < input.size(); ++i)
			{
				int cnt = -1;
				for (const auto & cp : m_cutpoints)
				{
					if (input[i] >= cp) ++cnt;
				}
				syms.push_back(cnt);
			}
		}

		public:
		/**
		 * Constructs a SAX quantizer of a given window size, string size and alphabet size.
		 * @param <window_size>: sliding window size
		 * @param <string_size>: output string size for each sliding window (can be greater than window_size)
		 * @param <alphabet_size>: number of codewords
		 */
		Sax(size_t window_size, size_t string_size, size_t alphabet_size)
		: m_window_size(window_size), m_string_size(string_size), m_alphabet_size(alphabet_size),
		  m_baseline_mean(0), m_baseline_stdev(1), m_trained(false) {

			assert(window_size > 0);
			assert(string_size > 0);
			assert(alphabet_size > 0);
			//double paa[m_string_size];
			//fill_cutpoints(alphabet_size, &m_cutpoints);
		}

		virtual ~Sax()
		{
			m_cutpoints.clear();
		}

		/**
		 * Trains the quantizer from a given sample. This sets the baseline mean and stdevs, which are used in
		 * normalizing the input.
		 *
		 * @param <samples>: list of training values
		 */
		template<typename Container>
		void train(const Container & samples)
		{
			double mean = 0;
			double stdev = DBL_MIN;

			assert(!samples.empty());
			input.resize(samples.size());
			//cout<<samples.size()<<endl;
			if (samples.size() < 2)
			{
				mean = samples[0];
				stdev = DBL_MIN;

			}
			else
			{
				size_t n = 0;
				double M2 = 0;
				for (const auto & val : samples)
				{
					++n;
					double delta = val - mean;
					mean += delta / n;
					M2 += delta * (val - mean);
				}
				stdev = sqrt(M2 / (n-1));
			}

			if (stdev == 0)
				stdev = DBL_MIN;

			m_baseline_mean = mean;
			m_baseline_stdev = stdev;

			for (size_t i = 0; i < samples.size(); ++i)
			{
				input[i] = (samples[i] - m_baseline_mean) / m_baseline_stdev;//0;
			}

			m_trained = true;
		}

		/**
		 * Quantizes the given input sequence into a discrete alphabet using SAX.
		 * Calling this method will also train the quantizer using the input sequence, if
		 * not already trained.
		 *
		 * @param <seq>: the input sequence to be quantized
		 * @param <qseq> (out): quantized output sequence
		 * @param reduce (default true): if true, applies run-length numerosity reduction
		 *
		 * Returns the number of consumed symbols from the input sequence.
		 */
		template<typename Container>
		size_t quantize(const Container & seq, vector<int> *qseq, size_t alphabet_size, bool reduce=true)
		{
			vector<int> buf1, buf2;
			vector<int> syms_buf;

			fill_cutpoints(alphabet_size, &m_cutpoints);
			size_t consumed = 0;

			saxify(*qseq);
			m_cutpoints.clear();

			return consumed;
		}

		/**
		 * Returns the order of the quantizer (here, the window size)
		 */
		inline size_t order() const
		{
			return m_window_size;
		}

		void print()
		{
			cout<<m_baseline_mean<<"   "<<m_baseline_stdev<<"  "<<m_alphabet_size<<endl;
		}
		/**
		 * Returns the compression ratio of the quantizer (input size / output size)
		 */
		inline double ratio() const
		{
			return ((double) m_window_size) / m_string_size;
		}
	};

}

#endif
