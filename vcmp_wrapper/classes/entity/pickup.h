#pragma once
#include "../../../main.h"
#include "player.h"

class CPickup {
public:
	int pickupId;

	void set_world(int world);
	void set_alpha(int alpha);
	void set_auto(bool automatic);
	void set_auto_timer(int timer);
	void set_position(Vector pos);
	void set_single_use(bool bSingleUse);
	int get_world();
	int get_alpha();
	bool get_auto();
	int get_auto_timer();
	bool get_single_use(void);
	Vector get_position();
	int get_model();
	int get_quantity();
	void delete_();
	int ID();
	bool is_streamed_for_player(CPlayer* player);
	void respawn();
};

CPickup* retrieve_pickup_instance(int pickupId);
CPickup* allocate_pickup_instance(int pickupId);
void destroy_pickup_instance(int pickupId);