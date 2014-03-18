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
#include <type_traits>

#include "src/utils/utils.h"
#include "src/utils/logger/ILogger.h"
#include "src/utils/DeathHandler.h"

#include "src/tests/tests.h"
#include "src/tests/FooClass.h"

//#include "src/utils/collections/BlockingQueue.h"
//#include "src/utils/collections/HashSet.h"
//#include "src/utils/ScopeGuard.h"
//#include "src/utils/Range.h"
//#include "src/utils/Semaphore.h"

using namespace alxutils;
using namespace tests;


int main() {
	Debug::DeathHandler dh;
	dh.set_generate_core_dump(true);

	dbgtrace;

	test_ThreadPool();

	return 0;
}
