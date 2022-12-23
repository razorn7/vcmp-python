#pragma once
#include <stdlib.h>
#include "../entity/player.h"
#include "../main.h"

#define STREAM_MAX_SIZE 4096

class CStream {
public:
	static void start_write(void);
	static void set_write_position(int position);
	static int get_write_position(void);
	static int get_write_size(void);
	static bool has_write_error(void);
	static void write_byte(int value);
	static void write_integer(int value);
	static void write_float(float value);
	static void write_string(char const* value);
	static void send(CPlayer* player);

	static void load_input(const void* data, size_t size);
	static void set_read_position(int position);
	static int get_read_position(void);
	static int get_read_size(void);
	static bool has_read_error(void);
	static int read_byte(void);
	static int read_integer(void);
	static float read_float(void);
	static char const* read_string(void);

private:

	static bool can_write(size_t size);
	static void write(const void* value, size_t size);

	static uint16_t read_be_int16(void);

	static uint8_t inputStreamData[STREAM_MAX_SIZE];
	static size_t inputStreamSize;
	static size_t inputStreamPosition;
	static bool inputStreamError;

	static uint8_t outputStreamData[STREAM_MAX_SIZE];
	static size_t outputStreamPosition;
	static size_t outputStreamEnd;
	static bool outputStreamError;
};