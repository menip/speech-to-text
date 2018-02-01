#ifndef STT_QUEUE_H
#define STT_QUEUE_H

#include "core/reference.h"
#include "core/vector.h"

/**
 * Stores keywords obtained through speech recognition.
 *
 * Wrapper for a queue datatype. Typically stores keywords from speech recognition.
 *
 * @author Leonardo Macedo
 */
class STTQueue : public Reference {
	GDCLASS(STTQueue, Reference);

private:
	/**
	 * Queue for storing recognized keywords; operations are thread-safe
	 */
	Vector<String> keywords;

	int capacity;  ///< Maximum number of keywords that can be stored in the queue

protected:
	/**
	 * Makes \a GDScript recognize public methods from this class.
	 */
	static void _bind_methods();

public:
	enum {
		DEFAULT_KWS_CAPACITY = 100  ///< Default capacity for the keywords queue
	};

	/**
	 * Removes and returns the first element in the keywords queue. If the queue is
	 * empty, returns an empty <tt>String ("")</tt>.
	 *
	 * @return The first element in the keywords queue, or \c "" if it is empty.
	 */
	String next();

	/**
	 * Adds the specified keyword to the end of the queue, returning \c true if
	 * successful (i.e., didn't exceed the queue capacity).
	 *
	 * @param kw keyword to be added to the queue.
	 *
	 * @return \c true if the word was added to the queue, or \c false otherwise.
	 */
	bool add(String kw);

	/**
	 * Returns how many keywords are in the queue.
	 *
	 * @return Number of keywords in the queue.
	 */
	int size();

	/**
	 * Returns \c true if the keywords queue is empty, or \c false otherwise.
	 *
	 * @return \c true if the queue is empty, or \c false otherwise.
	 */
	bool empty();

	/**
	 * Clears all keywords in the queue, leaving it with a size of 0.
	 */
	void clear();

	/**
	 * Sets the queue capacity as the specified value. Must be &ge; 0. If the new
	 * capacity exceeds the current number of elements in the queue, a warning
	 * message is printed, but no further actions are made.
	 *
	 * @param capacity new queue capacity (must be &ge; 0).
	 */
	void set_capacity(int capacity);

	/**
	 * Returns the current queue capacity.
	 *
	 * @return The current queue capacity.
	 */
	int get_capacity();

	/**
	 * Initializes queue capacity.
	 */
	STTQueue();

	/**
	 * Doesn't actually do anything. :P
	 */
	~STTQueue();
};

#endif  // STT_QUEUE_H
