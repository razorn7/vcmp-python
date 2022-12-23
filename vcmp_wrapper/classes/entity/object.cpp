#include "object.h"

std::array<CObject*, MAX_OBJECTS> objectMap;

void CObject::set_world(int world) {
	functions->SetObjectWorld(this->objectId, world);
}
	
void CObject::set_position(Vector pos) {
	functions->SetObjectPosition(this->objectId, pos.x, pos.y, pos.z);
}

int CObject::get_model() { 
	return functions->GetObjectModel(this->objectId);
}

int CObject::get_alpha() {
	return functions->GetObjectAlpha(this->objectId);
}

int CObject::get_world() {
	return functions->GetObjectWorld(this->objectId);
}

Vector CObject::get_position() {
	float x, y, z;
	functions->GetObjectPosition(this->objectId, &x, &y, &z);

	return Vector(x, y, z);
}

Quaternion CObject::get_rotation() {
	float w, x, y, z;
	functions->GetObjectRotation(this->objectId, &x, &y, &z, &w);

	return Quaternion(x, y, z, w);
}

Vector CObject::get_rotation_euler() {
	float x, y, z;
	functions->GetObjectRotationEuler(this->objectId, &x, &y, &z);

	return Vector(x, y, z);
}

void CObject::delete_() {
	// PS! this instance will be deleted due to a callback!!!
	functions->DeleteObject(this->objectId);
}

void CObject::move_to(Vector pos, int time) {
	functions->MoveObjectTo(this->objectId, pos.x, pos.y, pos.z, time);
}

void CObject::move_by(Vector offset, int time) {
	functions->MoveObjectBy(this->objectId, offset.x, offset.y, offset.z, time);
}

void CObject::rotate_to(Quaternion rotation, int time) {
	functions->RotateObjectTo(this->objectId, rotation.x, rotation.y, rotation.z, rotation.w, time);
}

void CObject::rotate_by(Quaternion rotOffset, int time) {
	functions->RotateObjectBy(this->objectId, rotOffset.x, rotOffset.y, rotOffset.z, rotOffset.w, time);
}

void CObject::rotate_to_euler(Vector rotation, int time) {
	functions->RotateObjectToEuler(this->objectId, rotation.x, rotation.y, rotation.z, time);
}

void CObject::rotate_by_euler(Vector rotOffset, int time) {
	functions->RotateObjectByEuler(this->objectId, rotOffset.x, rotOffset.y, rotOffset.z, time);
}

void CObject::set_alpha(int alpha, int fadeTime) {
	functions->SetObjectAlpha(this->objectId, alpha, fadeTime);
}

int CObject::ID() {
	return this->objectId;
}

bool CObject::is_streamed_for_player(CPlayer * player) {
	if(player != NULL)
		return (functions->IsObjectStreamedForPlayer(this->objectId, player->playerId) == 1 ? true : false);

	return false;
}

void CObject::set_reporting_shots(bool toReport) {
	functions->SetObjectShotReportEnabled(this->objectId, toReport);
}
	
void CObject::set_reporting_bumps(bool toReport) {
	functions->SetObjectTouchedReportEnabled(this->objectId, toReport);
}

bool CObject::get_reporting_shots() {
	return (functions->IsObjectShotReportEnabled(this->objectId) == 1 ? true : false);
}

bool CObject::get_reporting_bumps() {
	return (functions->IsObjectTouchedReportEnabled(this->objectId) == 1 ? true : false);
}

CObject* retrieve_object_instance(int objectId)
{
	if (objectId < 0 || objectId >= MAX_OBJECTS)
		return NULL;

	return objectMap[objectId];
}

CObject* allocate_object_instance(int objectId)
{
	if (objectId < 0 || objectId >= MAX_OBJECTS)
		return NULL;
	else if (!functions->CheckEntityExists(vcmpEntityPoolObject, objectId))
		return NULL;
	else if (objectMap[objectId] != NULL)
		return objectMap[objectId];

	CObject* pObject = new CObject();
	pObject->objectId = objectId;

	objectMap[pObject->objectId] = pObject;
	return pObject;
}

void destroy_object_instance(int objectId)
{
	if (objectId < 0 || objectId >= MAX_OBJECTS)
		return;
	else if (objectMap[objectId] == NULL)
		return;
	else
	{
		CObject* pObject = objectMap[objectId];
		delete pObject;

		objectMap[objectId] = NULL;
	}
}

PYBIND11_EMBEDDED_MODULE(vcmp_object, module) {
	pybind11::class_<CObject, std::shared_ptr<CObject> >(module, "CObject")
		.def(pybind11::init<>())
		.def_property("world", &CObject::get_world, &CObject::set_world)
		.def_property("position", &CObject::get_position, &CObject::set_position)
		.def_property("pos", &CObject::get_position, &CObject::set_position)
		.def_property("track_shots", &CObject::get_reporting_shots, &CObject::set_reporting_shots)
		.def_property("track_bumps", &CObject::get_reporting_bumps, &CObject::set_reporting_bumps)
		.def_property("alpha", &CObject::get_alpha, &CObject::set_alpha)
		.def_property_readonly("model", &CObject::get_model)
		.def_property_readonly("rotation", &CObject::get_rotation)
		.def_property_readonly("rotation_euler", &CObject::get_rotation_euler)
		.def_property_readonly("ID", &CObject::ID)
		.def("delete", &CObject::delete_)
		.def("move_to", &CObject::move_to)
		.def("move_by", &CObject::move_by)
		.def("rotate_to", &CObject::rotate_to)
		.def("rotate_by", &CObject::rotate_by)
		.def("rotate_to_euler", &CObject::rotate_to_euler)
		.def("rotate_by_euler", &CObject::rotate_by_euler);
}
