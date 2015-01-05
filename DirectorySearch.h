#include<string.h>
#include<iostream>
#include<vector>
#include <stdio.h>
#include <stdlib.h>
#include <sys/dir.h>
#include <sys/stat.h>
using namespace std;
class SearchPic
{
	public:
		SearchPic():pathCount(0){}
		void List_Files(const char *path, int recursive);
		vector<string> Paths;
	private:
		int pathCount;
		int IS_DIR(const char* path);
		int judgePic(char* str);
		void List_Files_Core(const char *path, int recursive);

};
int SearchPic::IS_DIR(const char* path)
{
	struct stat st;
	lstat(path, &st);
	return S_ISDIR(st.st_mode);
}
int SearchPic::judgePic(char* str)
{
	int length = strlen(str);
	if(length < 4)
	{
		return 0;
	}
	char* pstr = str + length - 3;
	if(strncmp("jpg", pstr, 3) == 0 || strncmp("bmp", pstr, 3) == 0 || strncmp("png", pstr, 3) == 0 || strncmp("JPG", pstr, 3) == 0 || strncmp("BMP", pstr, 3) == 0 || strncmp("PNG", pstr, 3) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//遍历文件夹de递归函数
void SearchPic::List_Files_Core(const char *path, int recursive)
{
	DIR *pdir;
	struct dirent *pdirent;
	char tempPath[256];
	pdir = opendir(path);
	if(pdir)
	{
		while(pdirent = readdir(pdir))
		{
			//跳过"."和".."
			if(strcmp(pdirent->d_name, ".") == 0
					|| strcmp(pdirent->d_name, "..") == 0)
				continue;
			sprintf(tempPath, "%s/%s", path, pdirent->d_name);
			if(IS_DIR(tempPath))
			{
				if(recursive == 1)
				{
					List_Files_Core(tempPath, recursive);
				}
			}
			else
			{
				if(judgePic(pdirent->d_name) == 1)
				{
					string path(tempPath);
					Paths.push_back(path);
				}
			}
		}
	}
	else
	{
		printf("opendir error:%s\n", path);
	}
	closedir(pdir);

}
//遍历文件夹的驱动函数

void SearchPic::List_Files(const char *path, int recursive)
{
	int len;
	char tempPath[256];

	Paths.clear();

	//去掉末尾的'/'
	len = strlen(path);
	strcpy(tempPath, path);
	if(tempPath[len - 1] == '/') tempPath[len -1] = '\0';

	if(IS_DIR(tempPath))
	{
		//处理目录
		List_Files_Core(tempPath, recursive);
	}
	else   //输出文件
	{
		printf("%s\n", path);
	}
}

