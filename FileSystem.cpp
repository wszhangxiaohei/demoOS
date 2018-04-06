#include<bits/stdc++.h>

using namespace std;

//磁盘操作
typedef class DiskOperate{
public:
	bool write(int startBlock, string content);//从哪开始写，写啥
	bool read(int startBlock, int dataSize);//从哪，多长
}

//指令层
//推荐在这里负责目录逻辑，仅返回status，在命令行里根据返回status，决定此次操作正确与否
typedef class DirOperate{
public:
	//file
	int create_file(); //return int startBlock
	string cat_file(); //return content of file
	bool rm_file(); //remove a file, just change the recycleFlag
	//int change_file(); we need it?or just remove&create

	void list_directory();
	void touch_directory();//创建目录
	void rm_directory();
}


//复制了word
typedef class FCB{
public:
    string time;          //文件建立时间或者上次修改时间
    int blockStartNum;   //文件数据起始盘块号  
    int blockEndtNum;   //文件数据起始盘块号  
    int fileSize;   //文件大小，盘块为单位  
    int dataSize;   //已写入的内容大小，字节为单位  
    int readptr;    //读指针，字节为单位  
    int link;   //文件链接数  
    int permission;   // 文件读写权限 0可读写 1只读 2只写
    bool recycleBin;
}FCB;

typedef class Directory{
public:
    char fileName[59];
    char type;  //文件类型,0文件夹,1文件  
    int startBlock; //文件是FCB起始盘块 文件夹是当前磁盘块号
    Directory* folderPtr; //下一层目录项
    Directory fileList[20];//本目录下内容？
}Directory;  



void example(){
	initSystem();
	string op;
	//这里是命令行，在这里进行初始化，循环，交互
	while (1){
		cout << "[root@localhost ~]";
		cin >> op;
		switch (op){
			//应该有成形的命令行解析头文件
		}

	}
}

void init_system(){
	//读入存储在
}

void test_unit(){
	//这里调试
}

int main(){
	example();

	return 0;
}