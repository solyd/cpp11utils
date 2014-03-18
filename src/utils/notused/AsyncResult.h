//#pragma once
//
//#include <chrono>
//#include <atomic>
//#include <type_traits>
//
//#include "src/utils/Semaphore.h"
//#include "src/utils/utils.h"
//#include "src/utils/types.h"
//
//namespace alxutils {
//
//template<typename T>
//class AsyncResult {
//public:
//	typedef std::function<void(const T & res)> FOnResultReady;
//
//public:
//	AsyncResult() :
//		m_onResultReady([] (const T & res) {}),
//		m_startTime(std::chrono::system_clock::now()),
//		m_ready(false) {}
//
//	void setResult(const T & res);
//	void onResultReady(const FOnResultReady & f);
//	bool isReady();
//	void wait();
//
//	TimePoint startTime();
//	TimePoint endTime();
//	Milliseconds duration();
//
//protected:
//	FOnResultReady	 m_onResultReady;
//	TimePoint 			 m_startTime;
//	TimePoint 			 m_endTime;
//	Milliseconds		 m_duration;
//	EventFlag 			 m_resultReadyEvent;
//	std::atomic_bool m_ready;
//	T 							 m_result;
//};
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//template<>
//class AsyncResult<void> {
//public:
//	typedef std::function<void()> FOnResultReady;
//
//public:
//	AsyncResult() :
//		m_onResultReady([] () {}),
//		m_startTime(std::chrono::system_clock::now()),
//		m_ready(false) {}
//
//	void setResult();
//	void onResultReady(const FOnResultReady & f);
//	bool isReady();
//	void wait();
//
//	TimePoint startTime();
//	TimePoint endTime();
//	Milliseconds duration();
//
//protected:
//	FOnResultReady	 m_onResultReady;
//	TimePoint 			 m_startTime;
//	TimePoint 			 m_endTime;
//	EventFlag 			 m_resultReadyEvent;
//	std::atomic_bool m_ready;
//};
//
//
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//template<typename T>
//inline void AsyncResult<T>::setResult(const T & res) {
//	m_endTime = std::chrono::system_clock::now();
//	m_result = res;
//	m_ready = true;
//	m_resultReadyEvent.notifyAll();
//	m_onResultReady(m_result);
//}
//
//template<typename T>
//inline void AsyncResult<T>::onResultReady(const FOnResultReady & f) {
//	m_onResultReady = f;
//}
//
//template<typename T>
//inline bool AsyncResult<T>::isReady() {
//	return m_ready;
//}
//
//template<typename T>
//inline void AsyncResult<T>::wait() {
//	m_resultReadyEvent.wait();
//}
//
//template<typename T>
//inline TimePoint AsyncResult<T>::startTime() {
//	return m_startTime;
//}
//
//template<typename T>
//inline TimePoint AsyncResult<T>::endTime() {
//	return m_endTime;
//}
//
//template<typename T>
//inline Milliseconds AsyncResult<T>::duration() {
//	return std::chrono::duration_cast<Milliseconds>(m_endTime - m_startTime);
//}
//
//// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//inline void AsyncResult<void>::setResult() {
//	m_endTime = std::chrono::system_clock::now();
//	m_ready = true;
//	m_resultReadyEvent.notifyAll();
//	m_onResultReady();
//}
//
//inline void AsyncResult<void>::onResultReady(const FOnResultReady & f) {
//	m_onResultReady = f;
//}
//
//inline bool AsyncResult<void>::isReady() {
//	return m_ready;
//}
//
//inline void AsyncResult<void>::wait() {
//	m_resultReadyEvent.wait();
//}
//
//inline TimePoint AsyncResult<void>::startTime() {
//	return m_startTime;
//}
//
//inline TimePoint AsyncResult<void>::endTime() {
//	return m_endTime;
//}
//
//inline Milliseconds AsyncResult<void>::duration() {
//	return std::chrono::duration_cast<Milliseconds>(m_endTime - m_startTime);
//}
//
//
//}
//
//
//
//
//
//
//
//
