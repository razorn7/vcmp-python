#pragma once
#include "../main.h"

class CKeyBind {
public:
	static int32_t bind_key(bool onKeyDown, int32_t key, int32_t key2, int32_t key3);
	static bool remove(int nKeybindId);
	static void remove_all(void);
};