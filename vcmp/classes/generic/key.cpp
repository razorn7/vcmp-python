#include "key.h"

int32_t CKeyBind::bind_key(bool onKeyDown, int32_t key, int32_t key2, int32_t key3) {
	int32_t keyslot = functions->GetKeyBindUnusedSlot();
	functions->RegisterKeyBind(keyslot, static_cast<uint8_t>(onKeyDown), key, key2, key3);

	return keyslot;
}

bool CKeyBind::remove(int nKeybindId) {
	return (functions->RemoveKeyBind(nKeybindId) ? true : false);
}

void CKeyBind::remove_all(void) {
	functions->RemoveAllKeyBinds();
}

PYBIND11_EMBEDDED_MODULE(vcmp_key_bindings, module) {
	pybind11::class_<CKeyBind>(module, "Key")
		.def_static("bind", &CKeyBind::bind_key)
		.def_static("remove", &CKeyBind::remove)
		.def_static("remove_all", &CKeyBind::remove_all);
}