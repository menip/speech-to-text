#ifndef STT_ERROR_H
#define STT_ERROR_H

#include "core/object.h"
#include "core/ustring.h"

/**
 * Shortcut for printing STTError::Error values with \c ERR_PRINT()
 */
#define STT_ERR_PRINTS(e) ERR_PRINTS(STTError::get_singleton()->get_error_string(e));

/**
 * Defines error values returned by some STT-related methods.
 *
 * Defines error values returned by some speech recognition-related methods, as well
 * as their meanings.
 *
 * @author Leonardo Macedo
 */
class STTError : public Object {
	GDCLASS(STTError, Object);

public:
	/**
	 * Defines error values that some speech recognition-related functions may
	 * return.
	 */
	enum Error {
		OK,                 ///< No error occurred
		UNDEF_FILES_ERR,    ///< One or more file/directory names aren't defined
		UNDEF_CONFIG_ERR,   ///< Undefined configuration variable (STTConfig)
		UNDEF_QUEUE_ERR,    ///< Undefined keywords queue (STTQueue)
		USER_DIR_MAKE_ERR,  ///< Couldn't create STT directory in \c user://
		USER_DIR_COPY_ERR,  ///< Couldn't copy config files to \c user:// directory
		MULTIBYTE_STR_ERR,  ///< Couldn't convert filename to a multibyte sequence
		MEM_ALLOC_ERR,      ///< No memory available for allocation
		CONFIG_CREATE_ERR,  ///< Couldn't create Pocketsphinx configuration variable
		REC_CREATE_ERR,     ///< Couldn't open audio device (microphone)
		DECODER_CREATE_ERR, ///< Couldn't create Sphinxbase decoder variable
		REC_START_ERR,      ///< Couldn't start recording user's voice
		REC_STOP_ERR,       ///< Couldn't stop recording user's voice
		UTT_START_ERR,      ///< Couldn't start utterance during speech recognition
		UTT_RESTART_ERR,    ///< Couldn't restart utterance during speech recognition
		AUDIO_READ_ERR      ///< Error while reading data from recorder
	};

protected:
	static STTError *singleton;  ///< Singleton for this class's only instance.

	/**
	 * Makes \a GDScript recognize public methods and the enum from this class.
	 */
	static void _bind_methods();

public:
	/**
	 * Returns this class's only instance (or \c NULL, if it wasn't instanced yet).
	 *
	 * @return This class's singleton.
	 */
	static STTError * get_singleton();

	/**
	 * Returns a short \c String explaining the given Error value.
	 *
	 * @param err an Error value.
	 *
	 * @return \c String explaining the \c err value.
	 */
	String get_error_string(Error err);

	/**
	 * Initializes the class's singleton.
	 */
	STTError();

	/**
	 * Doesn't actually do anything. :P
	 */
	~STTError();
};

// Makes the enum work when binding to methods
VARIANT_ENUM_CAST(STTError::Error);

#endif  // STT_ERROR_H
