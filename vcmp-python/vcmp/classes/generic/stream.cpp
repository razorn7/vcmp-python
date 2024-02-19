#include "stream.h"

uint8_t CStream::inputStreamData[STREAM_MAX_SIZE];
size_t CStream::inputStreamSize;
size_t CStream::inputStreamPosition;
bool CStream::inputStreamError;

uint8_t CStream::outputStreamData[STREAM_MAX_SIZE];
size_t CStream::outputStreamEnd;
size_t CStream::outputStreamPosition;
bool CStream::outputStreamError;

void CStream::start_write(void) {
	outputStreamPosition = 0;
	outputStreamEnd = 0;
	outputStreamError = false;
}

void CStream::set_write_position(int position) {
	if (position < 0 || position > outputStreamEnd) {
		position = outputStreamEnd;
	}

	outputStreamPosition = position;
}

int CStream::get_write_position(void) {
	return (int)outputStreamPosition;
}

int CStream::get_write_size(void) {
	return (int)outputStreamEnd;
}

bool CStream::has_write_error(void) {
	return outputStreamError;
}

void CStream::write_byte(int value) {
	uint8_t data = (uint8_t)value;

	write(&data, sizeof(data));
}

void CStream::write_integer(int value) {
	write(&value, sizeof(value));
}

void CStream::write_float(float value) {
	write(&value, sizeof(value));
}

void CStream::write_string(char const* value) {
	if (value == nullptr) {
		return;
	}

	size_t size = strlen(value);
	uint16_t length = size > UINT16_MAX ? UINT16_MAX : (uint16_t)size;

	if (can_write(sizeof(length))) {
		if (!can_write(length)) {
			length = sizeof(outputStreamData) - outputStreamPosition;

			outputStreamError = true;
		}

		uint16_t lengthBE = ((length >> 8) & 0xFF) | ((length & 0xFF) << 8);

		write(&lengthBE, sizeof(lengthBE));
		write(value, length);
	}
}

bool CStream::can_write(size_t size) {
	return size <= sizeof(outputStreamData) - outputStreamPosition;
}

void CStream::write(const void* value, size_t size) {
	if (can_write(size)) {
		memcpy(&outputStreamData[outputStreamPosition], value, size);
		outputStreamPosition += size;

		if (outputStreamPosition > outputStreamEnd) {
			outputStreamEnd = outputStreamPosition;
		}
	}
	else {
		outputStreamError = true;
	}
}

void CStream::send(CPlayer* player) {
	functions->SendClientScriptData(player != nullptr ? player->ID() : -1, outputStreamData, outputStreamEnd);

	outputStreamPosition = 0;
	outputStreamEnd = 0;
	outputStreamError = false;
}

void CStream::load_input(const void* data, size_t size) {
	inputStreamSize = size > sizeof(inputStreamData) ? sizeof(inputStreamData) : size;
	inputStreamPosition = 0;
	inputStreamError = false;

	memcpy(inputStreamData, data, inputStreamSize);
}

void CStream::set_read_position(int position) {
	if (position < 0 || position > inputStreamPosition) {
		position = inputStreamSize;
	}

	inputStreamPosition = position;
}

int CStream::get_read_position(void) {
	return (int)inputStreamPosition;
}

int CStream::get_read_size(void) {
	return (int)inputStreamSize;
}

bool CStream::has_read_error(void) {
	return inputStreamError;
}

int CStream::read_byte(void) {
	if (inputStreamPosition + sizeof(uint8_t) > inputStreamSize) {
		inputStreamError = true;
		return 0;
	}

	return inputStreamData[inputStreamPosition++];
}

int CStream::read_integer(void) {
	if (inputStreamPosition + sizeof(int) > inputStreamSize) {
		inputStreamError = true;
		return 0;
	}

	int result = *(int*)&inputStreamData[inputStreamPosition];
	inputStreamPosition += sizeof(int);
	return result;
}

float CStream::read_float(void) {
	if (inputStreamPosition + sizeof(float) > inputStreamSize) {
		inputStreamError = true;
		return 0.0f;
	}

	float result = *(float*)&inputStreamData[inputStreamPosition];
	inputStreamPosition += sizeof(float);
	return result;
}

uint16_t CStream::read_be_int16(void) {
	if (inputStreamPosition + sizeof(uint16_t) > inputStreamSize) {
		inputStreamError = true;
		return 0;
	}

	uint16_t result = *(int16_t*)&inputStreamData[inputStreamPosition];
	inputStreamPosition += sizeof(uint16_t);
	return ((result >> 8) & 0xFF) | ((result & 0xFF) << 8);
}

char const* CStream::read_string(void) {
	static char result[4096];

	uint16_t length = read_be_int16();

	if (inputStreamPosition + length > inputStreamSize) {
		length = inputStreamSize - inputStreamPosition;
		inputStreamError = true;
	}

	length = length > 4095 ? 4095 : length;

	memcpy(result, &inputStreamData[inputStreamPosition], length);
	result[length] = '\0';

	inputStreamPosition += length;

	return result;
}

PYBIND11_EMBEDDED_MODULE(vcmp_stream, module) {
	pybind11::class_<CStream, std::shared_ptr<CStream> >(module, "Stream")
		.def(pybind11::init<>())
		.def_static("start_write", &CStream::start_write)
		.def_static("set_write_position", &CStream::set_write_position)
		.def_static("get_write_position", &CStream::get_write_position)
		.def_static("get_write_size", &CStream::get_write_size)
		.def_static("has_write_error", &CStream::has_write_error)
		.def_static("write_byte", &CStream::write_byte)
		.def_static("write_integer", &CStream::write_integer)
		.def_static("write_float", &CStream::write_float)
		.def_static("write_string", &CStream::write_string)
		.def_static("send", &CStream::send)
		.def_static("set_read_position", &CStream::set_read_position)
		.def_static("get_read_position", &CStream::get_read_position)
		.def_static("get_read_size", &CStream::get_read_size)
		.def_static("has_read_error", &CStream::has_read_error)
		.def_static("read_byte", &CStream::read_byte)
		.def_static("read_integer", &CStream::read_integer)
		.def_static("read_float", &CStream::read_float)
		.def_static("read_string", &CStream::read_string);
}