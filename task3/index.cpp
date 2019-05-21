#include <iostream>
#include <string>
#include <vector>

#ifdef __linux__
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#elif defined(_WIN32)
#include <Windows.h>
#endif

using namespace std;

enum file_type
{
    ft_dir,
    ft_reg,
};

struct file_info 
{
    string name;
    string path;
    file_type type;
    uint64_t size;
    uint64_t mtime;
};

#ifdef __linux__

vector<file_info*> read_directory(string path)
{
    DIR *dirp = opendir(path.c_str());
    if (!dirp)
        return vector<file_info*>();

    vector<file_info*> vec;
    dirent *entry;
    while (entry = readdir(dirp)) {
        string name = entry->d_name;
        if (name == "." || name == "..")
            continue;
        struct stat st;
        string fullpath = path + "/" + name;
        if (stat(fullpath.c_str(), &st))
            continue; // err

        file_info *inf = new file_info;
        inf->name = name;
        inf->type = entry->d_type == DT_DIR ? ft_dir : ft_reg;
        inf->size = st.st_size;
        inf->mtime = st.st_mtim.tv_sec;
        vec.push_back(inf);
    }
    return vec;
}

#elif defined(_WIN32)

vector<file_info*> read_directory(string path)
{
	path += "/*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(path.c_str(), &fd);
	if (hFind == INVALID_HANDLE_VALUE)
		return vector<file_info*>();
    
	vector<file_info*> vec;
	do {
		file_info *info = new file_info;
		string name = fd.cFileName;
        if (name == "." || name == "..")
            continue;

        info->name = name;
		info->mtime = fd.ftLastWriteTime.dwLowDateTime;
		info->size = fd.nFileSizeLow | fd.nFileSizeHigh << 32;
		info->type = (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? ft_dir : ft_reg;
		vec.push_back(info);
	} while (FindNextFile(hFind, &fd));

	FindClose(hFind);
	return vec;
}


#endif


void FileIndexer::getfiles (string path){
	vector<file_info*> files= read_directory(path);
	for (int i=0; i<files.size(); i++){
	if (files[i]->type==ft_dir){
		getfiles(files[i]->path);
	}
		else{
			data[files[i]->path]=files[i];
		}
	}
}

unsigned FileIndexer::Build() {
	getfiles(root_path);
	return data.size();
	
}

void FileIndexer::print_file(std::shared_ptr<file_info> file) {
	cout << file->name << '\t' << file->path << '\t' << file->size << '\t' << file->mtime << endl;
	
}

void FileIndexer::PrintFiles() {
	for(auto& x: data) {
		print_file(x.second);
	}
	
	
}

void FileIndexer::PrintFilesSorted(SortingType type) {
	switch(type) {
		case Name:
			std::vector<std::shared_ptr<file_type>> files;
			for(auto& x: data) {
				files.push_back(x.second);	
			}
			std::sort(files.begin(), files.end(), [](const std::shared_ptr<file_type> a, const std::shared_ptr<file_type> b) {
				return a->name < b->name;
			});
			for(int i = 0; i < files.size(); ++i)
				print_file(files[i]);
			break;
		case Size:
			std::vector<std::shared_ptr<file_type>> files;
			for(auto& x: data) {
				files.push_back(x.second);	
			}
			std::sort(files.begin(), files.end(), [](const std::shared_ptr<file_type> a, const std::shared_ptr<file_type> b) {
				return a->size < b->size;
			});
			for(int i = 0; i < files.size(); ++i)
				print_file(files[i]);
			break;
		case Time:
			std::vector<std::shared_ptr<file_type>> files;
			for(auto& x: data) {
				files.push_back(x.second);	
			}
			std::sort(files.begin(), files.end(), [](const std::shared_ptr<file_type> a, const std::shared_ptr<file_type> b) {
				return a->mtime < b->mtime;
			});
			for(int i = 0; i < files.size(); ++i)
				print_file(files[i]);
			break;
	}
}

unsigned FileIndexer::FindFiles(const std::string &pattern) {
		auto it = data.find(path);
	if(it == data.end()) {
		return 1;
	} else return 0;
	
}

bool FileIndexer::MoveFile(const std::string &path, const std::string &new_path) {
	auto it = data.find(path);
	if(it == data.end()) {
		std::shared_ptr<file_info>& x = data[it.second];
		data.erase(it);
		x->path = new_path;
		data[x->path] = x;
		return true;
	} else return false;
}

bool FileIndexer::DeleteFile(const std::string &path) {
	auto it = data.find(path);
	if(it == data.end()) {
		data.erase(it);
		return true;
	} else return false;
}


/*
enum file_type
{
    ft_dir,
    ft_reg,
};

struct file_info 
{
    string name;
    string path;
    file_type type;
    uint64_t size;
    uint64_t mtime;
};

vector<file_info*> read_directory(string path);
*/

