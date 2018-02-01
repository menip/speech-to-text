#include "register_types.h"
#include "class_db.h"
#include "core/os/dir_access.h"  // DirAccess::exists()

#include "stt_config.h"
#include "stt_queue.h"
#include "stt_runner.h"
#include "stt_error.h"
#include "file_dir_util.h"

static STTError *stt_error = NULL;

void register_speech_to_text_types() {
	ClassDB::register_class<STTConfig>();
	ClassDB::register_class<STTQueue>();
	ClassDB::register_class<STTRunner>();
	ClassDB::register_virtual_class<STTError>();

	stt_error = memnew(STTError);
	Globals::get_singleton()->add_singleton(Globals::Singleton("STTError", STTError::get_singleton()));
}

void unregister_speech_to_text_types() {
	if (stt_error) memdelete(stt_error);

	// Remove all STT data in user://
	String user_dirname = "user://" + String(STT_USER_DIRNAME);
	if (DirAccess::exists(user_dirname))
		FileDirUtil::remove_dir_recursive(user_dirname);
}
