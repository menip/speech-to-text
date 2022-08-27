#ifndef STT_ERROR_H
#define STT_ERROR_H

#include "core/object.h"
#include "core/ustring.h"


// Shortcut for printing STTError::Error values with ERR_PRINT()
#define STT_ERR_PRINTS(e) ERR_PRINT(STTError::get_singleton()->get_error_string(e));

class STTError : public Object {
	GDCLASS(STTError, Object);

public:
	/*
	 * Defines error values that some speech recognition-related functions may
	 * return.
	 */
	enum Error {
		OK,
		UNDEF_FILES_ERR,
		UNDEF_CONFIG_ERR,
		UNDEF_QUEUE_ERR,
		USER_DIR_MAKE_ERR,
		USER_DIR_COPY_ERR,
		MULTIBYTE_STR_ERR,
		MEM_ALLOC_ERR,
		CONFIG_CREATE_ERR,
		REC_CREATE_ERR,
		DECODER_CREATE_ERR,
		REC_START_ERR,
		REC_STOP_ERR,
		UTT_START_ERR,
		UTT_RESTART_ERR,
		AUDIO_READ_ERR
	};

protected:
	static STTError *singleton;  // Singleton for this class's only instance.

	static void _bind_methods();

public:
	/*
	 * Returns this class's only instance (or NULL, if it wasn't instanced yet).
	 *
	 * @return This class's singleton.
	 */
	static STTError * get_singleton();

	String get_error_string(Error err);

	/*
	 * Initializes the class singleton.
	 */
	STTError();

	/*
	 * Doesn't actually do anything. :P
	 */
	~STTError();
};

// Makes the enum work when binding to methods
VARIANT_ENUM_CAST(STTError::Error);

#endif  // STT_ERROR_H
