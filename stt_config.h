#ifndef STT_CONFIG_H
#define STT_CONFIG_H

#include "core/resource.h"
#include "stt_error.h"

#include "sphinxbase/err.h"
#include "sphinxbase/ad.h"
#include "pocketsphinx.h"

// Directory, in user://, where config files are copied
#define STT_USER_DIRNAME "stt/"

class STTConfig : public Resource {
	GDCLASS(STTConfig, Resource);
	friend class STTRunner;

private:
	cmd_ln_t *conf;         // Configuration type for Sphinx variables
	ad_rec_t *recorder;     // Records sound from microphone
	ps_decoder_t *decoder;  // Decodes speech to text

	String hmm_dirname;    // Hidden Markov Model directory name
	String dict_filename;  // Dictionary filename
	String kws_filename;   // Keywords filename

	char *hmm;   // C string path for hmm_dirname
	char *dict;  // C string path for dict_filename
	char *kws;   // C string path for kws_filename

	/*
	 * Converts the given filename to its corresponding path in the STT user://
	 * directory.
	 *
	 * @filename filename to convert to user:// path.
	 *
	 * @return The corresponding path to filename in the STT user:// directory.
	 */
	String _convert_to_data_path(String filename);

protected:
	static void _bind_methods();

public:
	STTError::Error init();

	void set_hmm_dirname(const String &hmm_dirname);

	String get_hmm_dirname() const;

	void set_dict_filename(const String &dict_filename);

	String get_dict_filename() const;

	void set_kws_filename(const String &kws_filename);

	String get_kws_filename() const;

	/*
	 * Initializes attributes.
	 */
	STTConfig();

	/*
	 * Clears memory used by the object.
	 */
	~STTConfig();
};

#endif  // STT_CONFIG_H
