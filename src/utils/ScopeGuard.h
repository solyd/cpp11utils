#pragma once

#include <functional>
#include <utility>

#include "utils.h"

namespace alxutils {

class ScopeGuard {
public:
	typedef std::function<void()> FGuardFunction;

	ScopeGuard(const FGuardFunction & onScopeExit);
	~ScopeGuard();

	void disable();
	void enable();

protected:
	FGuardFunction m_onScopeExit;
	bool					 m_executeOnScopeExit;
};

}
