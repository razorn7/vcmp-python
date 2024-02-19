#include "checkpoint.h"
#include "../core.h"

std::array<CCheckpoint*, MAX_CHECKPOINTS> checkpointMap;

void CCheckpoint::set_world(int32_t world) {
	functions->SetCheckPointWorld(this->checkpointId, world);
}

void CCheckpoint::set_color(RGBa color) {
	functions->SetCheckPointColour(this->checkpointId, color.r, color.g, color.b, color.a);
}

void CCheckpoint::set_radius(float radius) {
	functions->SetCheckPointRadius(this->checkpointId, radius);
}

void CCheckpoint::set_position(Vector pos) {
	functions->SetCheckPointPosition(this->checkpointId, pos.x, pos.y, pos.z);
}

int32_t CCheckpoint::get_world() {
	return functions->GetCheckPointWorld(this->checkpointId);
}

RGBa CCheckpoint::get_color() {
	int r, g, b, a;
	functions->GetCheckPointColour(this->checkpointId, &r, &g, &b, &a);

	return RGBa(r, g, b, a);
}

float CCheckpoint::get_radius() {
	return (functions->GetCheckPointRadius(this->checkpointId));
}

Vector CCheckpoint::get_position() {
	float x, y, z;
	functions->GetCheckPointPosition(this->checkpointId, &x, &y, &z);

	return Vector(x, y, z);
}

void CCheckpoint::delete_(){
	//PS! this instance wil be deleted due to a callback!!!
	functions->DeleteCheckPoint(this->checkpointId);
}

int CCheckpoint::ID() { 
	return this->checkpointId;
}

bool CCheckpoint::is_streamed_to_player(CPlayer* player) {
	return (functions->IsCheckPointStreamedForPlayer(this->checkpointId, player->playerId) == 1 ? true : false);
}

CPlayer* CCheckpoint::get_owner(void) { 
	return retrieve_player_instance(this->ownerId);
}

CCheckpoint* retrieve_checkpoint_instance(int checkpointId)
{
	if (checkpointId < 0 || checkpointId >= MAX_CHECKPOINTS)
		return NULL;

	return checkpointMap[checkpointId];
}

CCheckpoint* allocate_checkpoint_instance(int checkpointId)
{
	if (checkpointId < 0 || checkpointId >= MAX_CHECKPOINTS)
		return NULL;
	else if (!functions->CheckEntityExists(vcmpEntityPoolCheckPoint, checkpointId))
		return NULL;
	else if (checkpointMap[checkpointId] != NULL)
		return checkpointMap[checkpointId];

	CCheckpoint* pCheckpoint = new CCheckpoint();
	pCheckpoint->checkpointId = checkpointId;

	checkpointMap[pCheckpoint->checkpointId] = pCheckpoint;
	return pCheckpoint;
}

void destroy_checkpoint_instance(int checkpointId)
{
	if (checkpointId < 0 || checkpointId >= MAX_CHECKPOINTS)
		return;
	else if (checkpointMap[checkpointId] == NULL)
		return;
	else
	{
		CCheckpoint* pCheckpoint = checkpointMap[checkpointId];
		delete pCheckpoint;

		checkpointMap[checkpointId] = NULL;
	}
}

PYBIND11_EMBEDDED_MODULE(vcmp_checkpoint, m) {
	pybind11::class_<CCheckpoint, std::shared_ptr<CCheckpoint> >(m, "CCheckpoint")
		.def(pybind11::init<>())
		.def_property("world", &CCheckpoint::get_world, &CCheckpoint::set_world)
		.def_property("color", &CCheckpoint::get_color, &CCheckpoint::set_color)
		.def_property("radius", &CCheckpoint::get_radius, &CCheckpoint::set_radius)
		.def_property("position", &CCheckpoint::get_position, &CCheckpoint::set_position)
		.def_property("pos", & CCheckpoint::get_position, & CCheckpoint::set_position)
		.def("ID", &CCheckpoint::ID)
		.def("get_owner", &CCheckpoint::get_owner)
		.def("delete", &CCheckpoint::delete_)
		.def("is_streamed_to_player", &CCheckpoint::is_streamed_to_player);
}