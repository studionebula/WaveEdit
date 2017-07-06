#include "WaveEdit.hpp"
#include <string.h>
#include "pffft/pffft.h"
#include <samplerate.h>


void RFFT(const float *in, float *out, int len) {
	PFFFT_Setup *setup = pffft_new_setup(len, PFFFT_REAL);
	float *work = NULL;
	if (len >= 4096)
		work = new float[len];
	pffft_transform_ordered(setup, in, out, work, PFFFT_FORWARD);
	pffft_destroy_setup(setup);
	if (work)
		delete[] work;

	float a = 1.0 / len;
	for (int i = 0; i < len; i++) {
		out[i] *= a;
	}
}

void IRFFT(const float *in, float *out, int len) {
	PFFFT_Setup *setup = pffft_new_setup(len, PFFFT_REAL);
	float *work = NULL;
	if (len >= 4096)
		work = new float[len];
	pffft_transform_ordered(setup, in, out, work, PFFFT_BACKWARD);
	pffft_destroy_setup(setup);
	if (work)
		delete[] work;
}


int resample(const float *in, int inLen, float *out, int outLen, double ratio) {
	SRC_DATA data;
	data.data_in = in;
	data.data_out = out;
	data.input_frames = inLen;
	data.output_frames = outLen;
	data.end_of_input = true;
	data.src_ratio = ratio;
	src_simple(&data, SRC_SINC_FASTEST, 1);
	return data.output_frames_gen;
}


void cyclicOversample(const float *in, float *out, int len, int oversample) {
	float *x = new float[len * oversample]();
	// Zero-stuff oversampled buffer
	for (int i = 0; i < len; i++) {
		x[i * oversample] = in[i] * oversample;
	}
	float fft[len * oversample];
	RFFT(x, fft, len * oversample);

	// Apply brick wall filter
	// y_{N/2} = 0
	fft[1] = 0.0;
	// y_k = 0 for k >= len
	for (int i = len / 2; i < len * oversample / 2; i++) {
		fft[2*i] = 0.0;
		fft[2*i + 1] = 0.0;
	}

	IRFFT(fft, out, len * oversample);
}
