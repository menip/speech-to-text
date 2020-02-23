#ifndef FILE_DIR_UTIL_H
#define FILE_DIR_UTIL_H

#include "core/ustring.h"

/**
 * Utility class containing file and directory manipulation methods.
 *
 * Utility class that expands on DirAccess. Contains functions related to file
 * and directory manipulation.
 *
 * @author Leonardo Macedo
 */
class FileDirUtil {

public:
	/**
	 * Creates the directory with the specified name in the \c path directory, which
	 * can be absolute or relative. Returns \c true if creation was successful or
	 * directory already exists.
	 *
	 * @param path Relative or absolute path where new directory will be created.
	 * @param dirname Directory that will be created.
	 *
	 * @return \c true, if directory was successfully created or already exists.
	 */
	static bool create_dir_safe(String path, String dirname);

	/**
	 * Copies a file with name \c from to the directory with name \c to. Returns \c
	 * true if copy was successful, or \c false if an error occurred.
	 *
	 * @param from File to be copied.
	 * @param to Directory that will receive the copied file.
	 *
	 * @return \c true if \c from file was successfully copied to \to directory, or
	 * \c false otherwise.
	 */
	static bool copy_file(String from, String to);

	/**
	 * Copies the \c from directory and its content to the \c to directory, including
	 * any other directories inside it. Returns \c true if copy was successful, or \c
	 * false otherwise.
	 *
	 * @param from Directory to be copied.
	 * @param to Directory that will receive a copy of \c from.
	 *
	 * @return \c true if directory \c from and its contents were successfully copied
	 * to \c to directory, or \c false otherwise.
	 */
	static bool copy_dir_recursive(String from, String to);

	/**
	 * Deletes the directory with the specified name, recursively removing all files
	 * and directories in it. Returns \c true if successful, or \c false if an error
	 * occurred or the directory doesn't exist.
	 *
	 * @param dirname Directory to be deleted.

	 * @return \c true if \c dirname directory was successfully deleted, or \c false
	 * otherwise.
	 */
	static bool remove_dir_recursive(String dirname);
};

#endif  // FILE_DIR_UTIL_H
