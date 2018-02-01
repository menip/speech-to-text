#include "stt_queue.h"

String STTQueue::next() {
	if (empty()) {
		WARN_PRINT("Empty keywords queue, returning empty String");
		return String("");
	}

	String kw = keywords.get(0);
	keywords.remove(0);
	return kw;
}

bool STTQueue::add(String kw) {
	if (size() + 1 > capacity)
		return false;

	keywords.push_back(kw);
	return true;
}

int STTQueue::size() {
	return keywords.size();
}

bool STTQueue::empty() {
	return keywords.empty();
}

void STTQueue::clear() {
	keywords.clear();
}

void STTQueue::set_capacity(int capacity) {
	if (capacity <= 0) {
		ERR_PRINT("Keywords queue capacity must be greater than 0");
		return;
	}
	this->capacity = capacity;
	if (size() > capacity)
		WARN_PRINT("New capacity exceeds current number of keywords in buffer");
}

int STTQueue::get_capacity() {
	return capacity;
}

void STTQueue::_bind_methods() {
	ClassDB::bind_method("next",  &STTQueue::next);
	ClassDB::bind_method("size",  &STTQueue::size);
	ClassDB::bind_method("empty", &STTQueue::empty);
	ClassDB::bind_method("clear", &STTQueue::clear);

	ClassDB::bind_method(D_METHOD("set_capacity", "capacity"),
	                     &STTQueue::set_capacity);
	ClassDB::bind_method("get_capacity", &STTQueue::get_capacity);

	BIND_CONSTANT(DEFAULT_KWS_CAPACITY);
}

STTQueue::STTQueue() {
	capacity = DEFAULT_KWS_CAPACITY;
}

STTQueue::~STTQueue() {}
