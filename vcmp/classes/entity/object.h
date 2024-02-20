#pragma once
#include "../core.h"
#include "player.h"

class CPlayer;
class CObject {
public:
	int objectId;

	void set_world(int world);
	void set_position(Vector pos);
	int get_model();
	int get_alpha();
	int get_world();
	Vector get_position();
	Quaternion get_rotation();
	Vector get_rotation_euler();
	void delete_();
	void move_to(Vector pos, int time);
	void move_by(Vector offset, int time);
	void rotate_to(Quaternion rotation, int time);
	void rotate_by(Quaternion rotOffset, int time);
	void rotate_to_euler(Vector rotation, int time);
	void rotate_by_euler(Vector rotOffset, int time);
	void set_alpha(int alpha, int fadeTime);
	int ID();
	bool is_streamed_for_player(CPlayer* player);
	void set_reporting_shots(bool toReport);
	void set_reporting_bumps(bool toReport);
	bool get_reporting_shots();
	bool get_reporting_bumps();
};

CObject* retrieve_object_instance(int objectId);
CObject* allocate_object_instance(int objectId);
void destroy_object_instance(int objectId);