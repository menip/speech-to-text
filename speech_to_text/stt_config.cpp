#include "stt_config.h"
#include "file_dir_util.h"

#include "core/os/os.h"           // OS::get_singleton()->get_data_dir()
#include "core/os/memory.h"       // memalloc(), memfree(), memdelete()
#include "core/os/dir_access.h"   // DirAccess::exists()
#include "core/os/file_access.h"  // FileAccess::exists()

/*
 * Adds the -adcdev option as a possible command line argument.
 * This argument corresponds to the microphone name.
 */
static arg_t cont_args_def[] = {
	POCKETSPHINX_OPTIONS,
	// Microphone
	{
		"-adcdev",
		ARG_STRING,
		NULL,  // Use default system microphone
		"Name of audio device to use for input."
	},
	CMDLN_EMPTY_OPTION
};

STTError::Error STTConfig::init() {
	// Check if files were set
	if (hmm_dirname == "" || dict_filename == "" || kws_filename == "") {
		STT_ERR_PRINTS(STTError::UNDEF_FILES_ERR);
		return STTError::UNDEF_FILES_ERR;
	}

#ifdef DEBUG_ENABLED
	print_line("[STTConfig res:// files]");
	print_line(" - HMM directory: '"   + hmm_dirname   + "'");
	print_line(" - Dictionary file: '" + dict_filename + "'");
	print_line(" - Keywords file: '"   + kws_filename  + "'");
#endif

	String user_dirname = "user://" + String(STT_USER_DIRNAME);

	// Create STT directory in user://
	if (!FileDirUtil::create_dir_safe("user://", STT_USER_DIRNAME)) {
		STT_ERR_PRINTS(STTError::USER_DIR_MAKE_ERR);
		return STTError::USER_DIR_MAKE_ERR;
	}

	// Copy config files to STT directory in user://
	if (!FileDirUtil::copy_dir_recursive(hmm_dirname, user_dirname) ||
			!FileDirUtil::copy_file(dict_filename, user_dirname) ||
			!FileDirUtil::copy_file(kws_filename, user_dirname)) {
		STT_ERR_PRINTS(STTError::USER_DIR_COPY_ERR);
		return STTError::USER_DIR_COPY_ERR;
	}

	String user_hmm_dirname = _convert_to_data_path(hmm_dirname);
	String user_dict_filename = _convert_to_data_path(dict_filename);
	String user_kws_filename = _convert_to_data_path(kws_filename);

#ifdef DEBUG_ENABLED
	print_line("[STTConfig user:// files]");
	print_line(" - HMM directory: '"   + user_hmm_dirname   + "'");
	print_line(" - Dictionary file: '" + user_dict_filename + "'");
	print_line(" - Keywords file: '"   + user_kws_filename  + "'");
#endif

	String names[3];
	names[0] = user_hmm_dirname;
	names[1] = user_dict_filename;
	names[2] = user_kws_filename;

	char *convert[3];

	// Convert each filename: String -> wchar_t * -> char *
	for (int i = 0; i < 3; i++) {
		int len = wcstombs(NULL, names[i].c_str(), 0);
		if (len == -1) {
			STT_ERR_PRINTS(STTError::MULTIBYTE_STR_ERR);
			return STTError::MULTIBYTE_STR_ERR;
		}

		convert[i] = (char *) memalloc((len + 1) * sizeof(char));
		if (convert[i] == NULL) {
			STT_ERR_PRINTS(STTError::MEM_ALLOC_ERR);
			return STTError::MEM_ALLOC_ERR;
		}

		wcstombs(convert[i], names[i].c_str(), len + 1);
	}

	hmm  = convert[0];
	dict = convert[1];
	kws  = convert[2];

	// Create configuration variable
	conf = cmd_ln_init(NULL, ps_args(), TRUE,
	                   "-hmm", hmm,
	                   "-dict", dict,
	                   "-kws", kws,
	                   NULL);

	if (conf == NULL) {
		STT_ERR_PRINTS(STTError::CONFIG_CREATE_ERR);
		return STTError::CONFIG_CREATE_ERR;
	}

	// Update basic configuration with custom one for mic
	conf = cmd_ln_init(conf, cont_args_def, TRUE, NULL);
	if (conf == NULL) {
		STT_ERR_PRINTS(STTError::CONFIG_CREATE_ERR);
		return STTError::CONFIG_CREATE_ERR;
	}

	// Create recorder variable
	recorder = ad_open_dev(cmd_ln_str_r(conf, "-adcdev"),
	                       (int) cmd_ln_float32_r(conf, "-samprate"));

	if (recorder == NULL) {
		cmd_ln_free_r(conf);
		STT_ERR_PRINTS(STTError::REC_CREATE_ERR);
		return STTError::REC_CREATE_ERR;
	}

	// Creater decoder variable
	decoder = ps_init(conf);

	if (decoder == NULL) {
		cmd_ln_free_r(conf);
		ad_close(recorder);
		STT_ERR_PRINTS(STTError::DECODER_CREATE_ERR);
		return STTError::DECODER_CREATE_ERR;
	}

	return STTError::OK;
}

void STTConfig::set_hmm_dirname(const String &hmm_dirname) {
	if (DirAccess::exists(hmm_dirname))
		this->hmm_dirname = hmm_dirname;
	else
		ERR_PRINTS("Directory '" + hmm_dirname + "' not found!");
}

String STTConfig::get_hmm_dirname() const {
	return hmm_dirname;
}

void STTConfig::set_dict_filename(const String &dict_filename) {
	if (FileAccess::exists(dict_filename))
		this->dict_filename = dict_filename;
	else
		ERR_PRINTS("File '" + dict_filename + "' not found!");
}

String STTConfig::get_dict_filename() const {
	return dict_filename;
}

void STTConfig::set_kws_filename(const String &kws_filename) {
	if (FileAccess::exists(kws_filename))
		this->kws_filename = kws_filename;
	else
		ERR_PRINTS("File '" + kws_filename + "' not found!");
}

String STTConfig::get_kws_filename() const {
	return kws_filename;
}

String STTConfig::_convert_to_data_path(String filename) {
	String user_path = OS::get_singleton()->get_data_dir();
	String basename = filename.get_file();
	return user_path.plus_file(STT_USER_DIRNAME).plus_file(basename);
}

void STTConfig::_bind_methods() {
	ClassDB::bind_method("init", &STTConfig::init);

	ClassDB::bind_method(D_METHOD("set_hmm_dirname", "hmm_dirname"),
	                     &STTConfig::set_hmm_dirname);
	ClassDB::bind_method("get_hmm_dirname", &STTConfig::get_hmm_dirname);

	ClassDB::bind_method(D_METHOD("set_dict_filename", "dict_filename"),
	                     &STTConfig::set_dict_filename);
	ClassDB::bind_method("get_dict_filename", &STTConfig::get_dict_filename);

	ClassDB::bind_method(D_METHOD("set_kws_filename", "kws_filename"),
	                     &STTConfig::set_kws_filename);
	ClassDB::bind_method("get_kws_filename", &STTConfig::get_kws_filename);

	ADD_PROPERTYNZ(PropertyInfo(Variant::STRING, "hmm directory", PROPERTY_HINT_DIR),
	               "set_hmm_dirname", "get_hmm_dirname");
	ADD_PROPERTYNZ(PropertyInfo(Variant::STRING, "dictionary file",
	                            PROPERTY_HINT_FILE, "dict"),
	               "set_dict_filename", "get_dict_filename");
	ADD_PROPERTYNZ(PropertyInfo(Variant::STRING, "keywords file",
	                            PROPERTY_HINT_FILE, "kws"),
	               "set_kws_filename", "get_kws_filename");
}

STTConfig::STTConfig() {
	// Disable Pocketsphinx log output
	err_set_logfp(NULL);

	conf = NULL;
	recorder = NULL;
	decoder = NULL;

	hmm_dirname   = "";
	dict_filename = "";
	kws_filename  = "";

	hmm = NULL;
	dict = NULL;
	kws = NULL;
}

STTConfig::~STTConfig() {
	if (conf     != NULL) cmd_ln_free_r(conf);
	if (recorder != NULL) ad_close(recorder);
	if (decoder  != NULL) ps_free(decoder);

	if (hmm  != NULL) memfree(hmm);
	if (dict != NULL) memfree(dict);
	if (kws  != NULL) memfree(kws);
}
