#include <stdio.h>
#include <stdlib.h>



int main(int argc, char* args[]) {

	// give a little help
	if (argc < 2) {
		printf("wav2pce {input filename}\n");
		printf("  outputs .bin of same name\n");
		return 1;
	}

	// try to open the source file
	FILE * fp;
	fp = fopen(args[1], "r");
	if (fp == NULL) {
		printf("failed access to : %s\n", args[1]);
		return 1;
	}

	// detect sample data
	fseek(fp, 22, SEEK_SET);
	uint16_t channel_count;
	fread(&channel_count, 2, 1, fp);
	printf("channel count : %d\n", channel_count);
	uint32_t sample_rate;
	fread(&sample_rate, 4, 1, fp);
	printf("sample rate : %d\n", sample_rate);
	fseek(fp, 34, SEEK_SET);
	uint16_t bit_depth;
	fread(&bit_depth, 2, 1, fp);
	printf("bit depth : %d\n", bit_depth);
	fseek(fp, 40, SEEK_SET);
	uint32_t data_length;
	fread(&data_length, 4, 1, fp);
	printf("data length : %d\n", data_length);

	// PC Engine clock and audio
	float pce_cpu_clock = 7160.f; // 7.16 mHz
	float pce_timer_rate = pce_cpu_clock / 1024.f;
	float pce_sample_rate = pce_cpu_clock / pce_timer_rate;

	// conversion adjusters
	float sample_ratio = pce_sample_rate / sample_rate;
	float bit_ratio = 0.f;
	float bit_offset = 0.f;

	// set adjusters and error handle weirdos
	fseek(fp, 44, SEEK_SET);
	if (bit_depth == 8 || bit_depth == 16) {
		bit_ratio = 5.f / (float) bit_depth;
	}
	else if (bit_depth == 32) {
		bit_ratio = 5.f / 2.f;
		bit_offset = 1.f;
	}
	else {
		printf("%d bit depth not supported\n", bit_depth);
		return 1;
	}
	
	// process / convert / save
	

	fclose(fp);

	return 0;
}
