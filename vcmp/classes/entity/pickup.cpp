#include "pickup.h"

std::array<CPickup*, MAX_PICKUPS> pickupMap;

void CPickup::set_world(int world) {
	functions->SetPickupWorld(this->pickupId, world);
}

void CPickup::set_alpha(int alpha) {
	functions->SetPickupAlpha(this->pickupId, alpha);
}

void CPickup::set_auto(bool automatic) {
	functions->SetPickupIsAutomatic(this->pickupId, automatic);
}

void CPickup::set_auto_timer(int timer) {
	functions->SetPickupAutoTimer(this->pickupId, timer);
}

void CPickup::set_position(Vector pos) {
	functions->SetPickupPosition(this->pickupId, pos.x, pos.y, pos.z);
}

void CPickup::set_single_use(bool bSingleUse) {
	functions->SetPickupOption(this->pickupId, vcmpPickupOption::vcmpPickupOptionSingleUse, bSingleUse ? 1 : 0);
}

int CPickup::get_world() {
	return functions->GetPickupWorld(this->pickupId);
}

int CPickup::get_alpha() {
	return functions->GetPickupAlpha(this->pickupId);
}

bool CPickup::get_auto() {
	return (functions->IsPickupAutomatic(this->pickupId) == 1 ? true : false);
}

int CPickup::get_auto_timer() {
	return functions->GetPickupAutoTimer(this->pickupId);
}

bool CPickup::get_single_use(void) {
	return (functions->GetPickupOption(this->pickupId, vcmpPickupOption::vcmpPickupOptionSingleUse) == 1 ? true : false);
}

Vector CPickup::get_position() {
	float x, y, z;
	functions->GetPickupPosition(this->pickupId, &x, &y, &z);

	return Vector(x, y, z);
}

int CPickup::get_model() {
	return functions->GetPickupModel(this->pickupId);
}

int CPickup::get_quantity() {
	return functions->GetPickupQuantity(this->pickupId);
}

void CPickup::delete_() {
	//PS! this instance will be deleted due to a callback!!!
	functions->DeletePickup(this->pickupId);
}

int CPickup::ID() {
	return this->pickupId;
}

bool CPickup::is_streamed_for_player(CPlayer* player) {
	return (functions->IsPickupStreamedForPlayer(this->pickupId, player->playerId) == 1 ? true : false);
}

void CPickup::respawn() {
	functions->RefreshPickup(this->pickupId);
}

CPickup* retrieve_pickup_instance(int pickupId) {
	if (pickupId < 0 || pickupId >= MAX_PICKUPS)
		return NULL;

	return pickupMap[pickupId];
}

CPickup* allocate_pickup_instance(int pickupId) {
	if (pickupId < 0 || pickupId >= MAX_PICKUPS)
		return NULL;
	else if (!functions->CheckEntityExists(vcmpEntityPoolPickup, pickupId))
		return NULL;
	else if (pickupMap[pickupId] != NULL)
		return pickupMap[pickupId];

	CPickup* ppickup = new CPickup();
	ppickup->pickupId = pickupId;

	pickupMap[ppickup->pickupId] = ppickup;
	return ppickup;
}

void destroy_pickup_instance(int pickupId) {
	if (pickupId < 0 || pickupId >= MAX_PICKUPS)
		return;
	else if (pickupMap[pickupId] == NULL)
		return;
	else
	{
		CPickup* ppickup = pickupMap[pickupId];
		delete ppickup;

		pickupMap[pickupId] = NULL;
	}
}

PYBIND11_EMBEDDED_MODULE(vcmp_pickup, m) {
	pybind11::class_<CPickup, std::shared_ptr<CPickup> >(m, "CPickup")
		.def(pybind11::init<>())
		.def_property("world", &CPickup::get_world, &CPickup::set_world)
		.def_property("alpha", &CPickup::get_alpha, &CPickup::set_alpha)
		.def_property("automatic", &CPickup::get_auto, &CPickup::set_auto)
		.def_property("timer", &CPickup::get_auto_timer, &CPickup::set_auto_timer)
		.def_property("respawn_timer", &CPickup::get_auto_timer, &CPickup::set_auto_timer)
		.def_property("position", &CPickup::get_position, &CPickup::set_position)
		.def_property("pos", &CPickup::get_position, &CPickup::set_position)
		.def_property("single_use", &CPickup::get_single_use, &CPickup::set_single_use)
		.def("model", &CPickup::get_model)
		.def("quantity", &CPickup::get_quantity)
		.def("ID", &CPickup::ID)
		.def("delete", &CPickup::delete_)
		.def("respawn", &CPickup::respawn)
		.def("is_streamed_to_player", &CPickup::is_streamed_for_player);
}