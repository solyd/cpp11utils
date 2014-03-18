#pragma once

#include <utility>

#include "src/utils/types.h"
#include "src/utils/collections/threadsafe/Queue.h"

namespace alxutils {

template<typename MessageType, typename MsgQType = threadsafe::Queue<MessageType>>
class MessageReceiver {
public:
	static const uint MAX_MESSAGES_DEFAULT = 4096;
	MessageReceiver(const uint maxMessages = MAX_MESSAGES_DEFAULT) : m_msgs(maxMessages) {}

	void sendMsg(const MessageType & msg);
	void sendMsg(MessageType && msg);

protected:
	MessageType recvMsg();
	uint pendingMessagesCount();

private:
	MsgQType m_msgs;
};

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template<typename MessageType, typename MsgQType>
inline void MessageReceiver<MessageType, MsgQType>::sendMsg(const MessageType& msg) {
	m_msgs.enqueue(msg);
}

template<typename MessageType, typename MsgQType>
inline void MessageReceiver<MessageType, MsgQType>::sendMsg(MessageType&& msg) {
	m_msgs.enqueue(std::move(msg));
}


template<typename MessageType, typename MsgQType>
inline MessageType MessageReceiver<MessageType, MsgQType>::recvMsg() {
	return m_msgs.dequeue();
}

template<typename MessageType, typename MsgQType>
inline uint MessageReceiver<MessageType, MsgQType>::pendingMessagesCount() {
	return m_msgs.size();
}

}
