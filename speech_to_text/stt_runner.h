#ifndef STT_RUNNER_H
#define STT_RUNNER_H

#include "scene/main/node.h"
#include "core/os/thread.h"

#include "stt_config.h"
#include "stt_queue.h"

/**
 * Uses STT (Speech to Text) to identify keywords spoken by the user.
 *
 * Responsible for running speech recognition itself, identifying keywords spoken
 * by the user.
 *
 * @author Leonardo Macedo
 */
class STTRunner : public Node {
	GDCLASS(STTRunner, Node);

private:
	Thread *recognition;  ///< Used to run the speech recognition in parallel
	bool is_running;      ///< If true, speech recognition loop is currently on

	Ref<STTConfig> config; ///< Configuration object containing recognition variables
	Ref<STTQueue> queue;   ///< Queue for storing recognized keywords

	int rec_buffer_size;  ///< Microphone recorder buffer size

	/**
	 * Stores the last STTError::Error occurred in the speech recognition thread
	 * (if no error has yet ocurred, then its value is \c OK)
	 */
	STTError::Error run_error;

	/**
	 * Thread wrapper function, calls _recognize() method of its STTRunner argument.
	 */
	static void _thread_recognize(void *runner);

	/**
	 * Repeatedly listens to keywords from the user's microphone input.
	 */
	void _recognize();

	/**
	 * Stops recognition thread and emits an error value through the end_signal
	 * signal.
	 *
	 * @param err error value indicating what error ocurred.
	 */
	void _error_stop(STTError::Error err);

protected:
	/**
	 * Makes \a GDScript recognize public methods from this class.
	 */
	static void _bind_methods();

public:
	enum {
		DEFAULT_REC_BUFFER_SIZE = 2048  ///< Microphone recorder default buffer size
	};

	/**
	 * Creates a thread to repeatedly listen to keywords. The thread can be stopped
	 * with stop(). If start() was previously called, the current thread is halted
	 * and a new recognition, with the specified arguments, is created.
	 *
	 * @return One of the following STTError::Error values:
	 * - \c OK
	 * - \c UNDEF_CONFIG_ERR
	 * - \c UNDEF_QUEUE_ERR
	 *
	 * \note To check for an error that occurred and stopped the thread, see
	 * get_last_error().
	 *
	 * @see set_config for setting a STTConfig object
	 * @see set_queue for setting a STTQueue object
	 */
	STTError::Error start();

	/**
	 * Returns \c true if the speech recognition thread is active, or \c false
	 * otherwise.
	 */
	bool running();

	/**
	 * Stops the thread currently doing speech recognition. If start() wasn't called
	 * previously, this function does nothing.
	 */
	void stop();

	/**
	 * Sets the STTConfig object containing recognition variables. If the speech
	 * recognition thread is currently running, it will be stopped.
	 *
	 * @param p_config reference to a STTConfig object.
	 */
	void set_config(const Ref<STTConfig> &p_config);

	/**
	 * Returns the STTConfig object containing recognition variables.
	 *
	 * @return The currently used STTConfig object for speech recognition, or \c NULL
	 * if not previously defined.
	 */
	Ref<STTConfig> get_config() const;

	/**
	 * Sets the STTQueue that stores recognized keywords. If the speech recognition
	 * thread is already running, it will be stopped.
	 *
	 * @param p_queue reference to a STTQueue object.
	 */
	void set_queue(const Ref<STTQueue> &p_queue);

	/**
	 * Returns the STTQueue that stores recognized keywords.
	 *
	 * @return The currently used STTQueue object for storing keywords, or \c NULL if
	 * not previously defined.
	 */
	Ref<STTQueue> get_queue() const;

	/**
	 * Sets the microphone recorder buffer size used for speech recognition as the
	 * specified value. Must be > 0. If the speech recognition thread is currently
	 * running, it will be stopped.
	 *
	 * @param rec_buffer_size microphone recorder buffer size.
	 */
	void set_rec_buffer_size(int rec_buffer_size);

	/**
	 * Returns the microphone recorder buffer size used for speech recognition.
	 *
	 * @return Microphone recorder buffer size.
	 */
	int get_rec_buffer_size();

	/**
	 * Returns the STTError::Error value that depicts how the previously running
	 * speech recognition thread has ended. It can be one of the following values:
	 * - \c OK
	 * - \c REC_START_ERR
	 * - \c REC_STOP_ERR
	 * - \c UTT_START_ERR
	 * - \c UTT_RESTART_ERR
	 * - \c AUDIO_READ_ERR
	 *
	 * If no thread was previously run, returns STTError::OK.
	 */
	STTError::Error get_run_error();

	/**
	 * Resets the STTError::Error value that depicts how the previously running
	 * speech recognition thread has ended, setting its value to STTError::OK.
	 */
	void reset_run_error();

	/**
	 * Initializes attributes.
	 */
	STTRunner();

	/**
	 * Clears memory used by the object.
	 */
	~STTRunner();
};

#endif  // STT_RUNNER_H
