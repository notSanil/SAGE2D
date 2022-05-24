#include "Entity.h"

namespace Sage {
	Entity::Entity(entt::entity id, GameScene* scene):
		entityId(id), scene(scene)
	{
	}
}