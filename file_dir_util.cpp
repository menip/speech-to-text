#include "file_dir_util.h"
#include "core/os/memory.h"      // memdelete()
#include "core/os/dir_access.h"  // dir_exists(), open(), make_dir(), copy()

bool FileDirUtil::create_dir_safe(String path, String dirname) {
	DirAccess *da = DirAccess::open(path);
	Error err;

	if (da->dir_exists(dirname))
		err = OK;
	else {
		err = da->make_dir(dirname);
		if (err != OK)
			ERR_PRINTS("Couldn't create '" + dirname + "' directory in '" +
			           path + "'");
	}

	memdelete(da);
	return err == OK;
}

bool FileDirUtil::copy_file(String from, String to) {
	DirAccess *da = DirAccess::open(to);

	String from_basename = from.get_file();
	String to_target = to.plus_file(from_basename);

	if (da->copy(from, to_target) != OK) {
		ERR_PRINTS("Couldn't copy '" + from + "' to '" + to_target + "'");
		memdelete(da);
		return false;
	}

	memdelete(da);
	return true;
}

bool FileDirUtil::copy_dir_recursive(String from, String to) {
	String dirname = from.get_file();

	DirAccess *dfrom = DirAccess::open(from);
	DirAccess *dto = DirAccess::open(to);

	// Create directory with same name in "to"
	if (!create_dir_safe(to, dirname)) {
		memdelete(dfrom);
		memdelete(dto);
		return false;
	}

	// Copy each file in "from" to "to" directory
	dfrom->list_dir_begin();
	String filename = dfrom->get_next();
	while (filename != "") {
		// Ignore "." and ".." filenames
		if (filename == "." || filename == "..") {
			filename = dfrom->get_next();
			continue;
		}

		// If filename is actually a directory, recursively copy everything in it
		if (dfrom->dir_exists(filename))
			copy_dir_recursive(from.plus_file(filename), to.plus_file(dirname));
		// Regular file; copy normally
		else if (!copy_file(from.plus_file(filename), to.plus_file(dirname))) {
			memdelete(dfrom);
			memdelete(dto);
			return false;
		}

		filename = dfrom->get_next();
	}

	memdelete(dfrom);
	memdelete(dto);
	return true;
}

bool FileDirUtil::remove_dir_recursive(String dirname) {
	DirAccess *da = DirAccess::open(dirname);

	if (!DirAccess::exists(dirname)) {
		ERR_PRINTS("Directory '" + dirname + "' not found");
		memdelete(da);
		return false;
	}

	// Remove all files/directories in "dirname" directory
	da->list_dir_begin();
	String filename = da->get_next();
	while (filename != "") {
		// Ignore "." and ".." filenames
		if (filename == "." || filename == "..") {
			filename = da->get_next();
			continue;
		}

		// If filename is actually a directory, recursively remove everything in it
		if (da->dir_exists(filename))
			remove_dir_recursive(dirname.plus_file(filename));
		// Regular file; remove normally
		else if (da->remove(filename) != OK) {
			ERR_PRINTS("Couldn't delete '" + filename + "' in '" + dirname + "'");
			memdelete(da);
			return false;
		}

		filename = da->get_next();
	}

	// Delete empty "dirname" directory
	Error err = da->remove(dirname);
	if (err != OK)
		ERR_PRINTS("Couldn't delete '" + dirname + "'");

	memdelete(da);
	return err == OK;
}
