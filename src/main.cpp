#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <functional>
#include <typeinfo>
#include <utility>
#include <queue>
#include <memory>
#include <list>
#include <condition_variable>
#include <unordered_set>

#include "src/utils/utils.h"
#include "src/utils/logger/ILogger.h"
#include "src/utils/DeathHandler.h"

//#include "src/utils/collections/BlockingQueue.h"
//#include "src/utils/collections/HashSet.h"
//#include "src/utils/ScopeGuard.h"
//#include "src/utils/Range.h"
//#include "src/utils/Semaphore.h"

using namespace alxutils;

struct A {

	A(const int & x, const int &  y) {
		_x = x;
		_y = y;
	}

	int _y;
	int _x;

};

int main() {
	Debug::DeathHandler dh;



	return 0;
}
