#ifndef BICUDO_CORE_MIXIN_H
#define BICUDO_CORE_MIXIN_H

#include <functional>

namespace bicudo {
	enum class runtime {
		initialisation, eventlistener, update, unsafeupdate, render
	};

	struct mixin {
		void *data {nullptr};
		std::function<void(void*)> callback {[](void*) {}};
	};
}

#endif