#include "ScopeGuard.h"

namespace alxutils {

ScopeGuard::ScopeGuard(const FGuardFunction& onScopeExit) :
		m_onScopeExit(std::move(onScopeExit)), m_executeOnScopeExit(true)
{
}

ScopeGuard::~ScopeGuard() {
	if (m_executeOnScopeExit)
		m_onScopeExit();
}

void ScopeGuard::disable() { m_executeOnScopeExit = false; }
void ScopeGuard::enable() { m_executeOnScopeExit = true; }

}


