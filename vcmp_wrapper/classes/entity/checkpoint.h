#pragma once
#include "../../../main.h"
#include "player.h"

class CCheckpoint
{
public:
	void set_world(int32_t world);
	void set_color(RGBa color);
	void set_position(Vector pos);
	void set_radius(float radius);

	int32_t get_world();
	RGBa get_color();
	Vector get_position();
	float get_radius();
	int32_t ID();
	CPlayer* get_owner();

	void delete_();
	bool is_streamed_to_player(CPlayer* player);

	int checkpointId;
	int ownerId;
};

CCheckpoint* retrieve_checkpoint_instance(int checkpointId);
CCheckpoint* allocate_checkpoint_instance(int checkpointId);
void destroy_checkpoint_instance(int checkpointId);