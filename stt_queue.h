#ifndef STT_QUEUE_H
#define STT_QUEUE_H

#include "core/reference.h"
#include "core/vector.h"

class STTQueue : public Reference {
	GDCLASS(STTQueue, Reference);

private:
	// Queue for storing recognized keywords; operations are thread-safe
	Vector<String> keywords;

	int capacity;

protected:
	static void _bind_methods();

public:
	enum {
		DEFAULT_KWS_CAPACITY = 100
	};

	String next();

	/*
	 * Adds the specified keyword to the end of the queue, returning true if
	 * successful (i.e., didn't exceed the queue capacity).
	 *
	 * @kw keyword to be added to the queue.
	 *
	 * @return true if the word was added to the queue, or false otherwise.
	 */
	bool add(String kw);

	int size();

	bool empty();

	void clear();

	void set_capacity(const int &capacity);

	int get_capacity();

	/*
	 * Initializes queue capacity.
	 */
	STTQueue();

	/*
	 * Doesn't actually do anything. :P
	 */
	~STTQueue();
};

#endif  // STT_QUEUE_H
