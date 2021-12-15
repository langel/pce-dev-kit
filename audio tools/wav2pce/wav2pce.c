#include <stdint.h>
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
	if (channel_count > 1) {
		printf("wav2pce does not support non-mono wav files yet\n");
		return 1;
	}
	uint32_t sample_rate;
	fread(&sample_rate, 4, 1, fp);
	printf("sample rate : %dHz\n", sample_rate);
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

	// PC Engine clock and audio playback timer
	float pce_cpu_clock = 7160000.f; // 7.16 mHz
	// timer uses multiples of 1024 cpu cycles
	// timer counter is 0 based (off by 1!)
	// 60Hz frame rate has 119333.333 cpu cycles
	// timer counter set to 0 gets called 116.536/frame
	float pce_timer_rate = pce_cpu_clock / 1024.f;

	// conversion adjusters
	float sample_ratio = pce_timer_rate / sample_rate;
	float bit_ratio = 0.f;
	float bit_offset = 0.f;
	// XXX target bit depth could vary
	//     4 bit storage would use half the space
	//     stacking channels could create more bit depth
	uint8_t pce_bit_depth = 5;
	if (bit_depth == 32) {
		bit_offset = 1.f;
		bit_ratio = (float) pce_bit_depth / 2.f;
	}
	else {
		bit_offset = 1 << (bit_depth - 1);
		bit_ratio = (float) (2 << pce_bit_depth) / (float) (2 << bit_depth);
	}
	
	// create target file and spit out info
	char target_filename[2048] = "";
	char * extension = strrchr(args[1], '.');
	strncpy(target_filename, args[1], extension - args[1]);
	strcat(target_filename, ".bin");
	printf("\ntarget file : %s\n", target_filename);
	FILE * tp = fopen(target_filename, "w");
	printf("target playback rate : %fHz\n", pce_timer_rate);
	printf("target bit depth : %d\n", pce_bit_depth);
	printf("bit ratio : %f\n", bit_ratio);
	printf("sample ratio : %f\n", sample_ratio);

	// process / convert / save
	fseek(fp, 44, SEEK_SET);
	// XXX need separate loop for 32bit float wav data
	uint16_t source_data;
	uint8_t target_data;
	for (int i = 0; i < data_length; i += byte_size) {
		fread(&source_data, byte_size, 1, fp);
		source_data += bit_offset;
		target_data = (uint8_t) ((float) source_data * bit_ratio);
		fwrite(&target_data, 1, 1, tp);
	}

	// cleanup and shutdown
	fclose(fp);
	fclose(tp);
	printf("\nsuccessful conversion\n");
	return 0;
}
