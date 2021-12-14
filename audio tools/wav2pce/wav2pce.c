#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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
	printf("source file : %s\n", args[1]);

	// detect wave header
	fseek(fp, 0, SEEK_SET); // "RIFF" at position 0
	uint32_t header_reader;
	fread(&header_reader, 4, 1, fp);
	if (header_reader != 1179011410) {
		printf("missing or wrong file header\n");
		return 1;
	}
	fseek(fp, 8, SEEK_SET); // "WAVE" at position 8
	fread(&header_reader, 4, 1, fp);
	if (header_reader != 1163280727) {
		printf("found RIFF header but not of type WAVE\n");
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
	uint8_t byte_size = bit_depth >> 3;
	printf("byte size per sample : %d\n", byte_size);
	fseek(fp, 40, SEEK_SET);
	uint32_t data_length;
	fread(&data_length, 4, 1, fp);
	printf("data length : %d\n", data_length);
	int sample_count_per_channel = data_length / (channel_count * byte_size);
	printf("sample count per channel : %d\n", sample_count_per_channel);
	printf("wav file playback length : %fs\n", (float) sample_count_per_channel / (float) sample_rate);

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
	
	// create target file
	char target_filename[2048];
	char * extension = strrchr(args[1], '.');
	strncpy(target_filename, args[1], extension - args[1]);
	strcat(target_filename, ".bin");
	printf("\ntarget file : %s\n", target_filename);

	// process / convert / save
	printf("target playback rate : %fkHz\n", pce_timer_rate);

	// cleanup and shutdown
	fclose(fp);

	return 0;
}
