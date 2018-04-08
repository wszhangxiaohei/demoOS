#include<bits/stdc++.h>
#include "DiskOperate.cpp"
#define system_size 100*1024*1024   //系统大小  
#define block_szie 1024 //盘块大小  
#define block_count system_size/block_szie //系统盘块数目

using namespace std;

char* systemStartAddr
string currentDir;
DirOperate dirOp;

//磁盘操作
typedef class DiskOperate{
public:
	bool write(int startBlock, string content);//从哪开始写，写啥
	bool read(int startBlock, int dataSize);//从哪，多长
}DiskOperate;

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
}DirOperate;

//用的几个函数 没有实现
Directory*get_new_Directory(); 
//在目录存储块为新的目录申请空间，获得新的文件目录指针

FCB*get_new_FCB();
//在FCB的存储磁盘区域申请空间，获得文件新的FCB指针，失败返回null

int get_new_data_block();
//在磁盘中查看磁盘中是否空间，获得一块磁盘号,失败返回-1


typedef class DirOperate {
	//指令层
	//推荐在这里负责目录逻辑，仅返回status，在命令行里根据返回status，决定此次操作正确与否
public:
	//file
	int create_file(Directory*lastDirectory, string fileName, string expandFileName, char type); //创建成功返回0，失败返回-1
	string cat_file(FCB*FCBptr); //return content of file
	bool rm_file(FCB*FCBptr); //remove a file, just change the recycleFlag   形参指针是否要改成目录的指针？？	
					//int change_file(); we need it?or just remove&create
	void list_directory(Directory*directory);//列出当前目录下的文件或文件夹-1层
	void list_all_directory(Directory*directory);//列出当前目录下所有文件或者文件夹
	//void touch_directory();//创建目录-------创建文件或者文件夹时自动创建目录了 该函数没有实现
	void rm_directory(Directory*directory);
}DirOperate;


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

typedef class FCB {
private:
	string expandName;//文件扩展名
	string time;//文件建立时间或者上次修改时间
	int blockStarNum;  //文件数据起始盘块号 
	int  blockEndNum;//文件数据结束盘块号 
	int fileSize;//文件大小，盘块为单位  
	int dataSize;//已写入的内容大小，字节为单位 
	int readptr;//读指针，字节为单位 
	int link;//文件链接数  
	int permission;// 文件读写权限 0可读写 1只读 2只写
	bool recyleBin;//文件是否放入回收站 0不在回收站 1在回收站
public:
	FCB();
	string get_expandName();
	string get_time();
	int get_blockStarNum();
	int get_blockEndNum();
	int get_fileSize();
	int get_dataSize();
	int get_readptr();
	int get_link();
	int get_permission();
	bool get_recyleBin();
	void set_expandName(string newExpandName);
	void set_time(string newTime);
	void set_blockStarNum(int newBlockStarNum);
	void set_blockEndNum(int newBlockEndNum);
	void set_fileSize(int newFileSize);
	void set_dataSize(int newDataSize);
	void set_readptr(int newReadptr);
	void set_link(int newLink);
	void set_permission(int newPermission);
	void set_recyleBin(bool newRecyleBin);

}FCB;


typedef class Directory{
public:
    char fileName[59];
    char type;  //文件类型,0文件夹,1文件  
    int startBlock; //文件是FCB起始盘块 文件夹是当前磁盘块号
    Directory* folderPtr; //下一层目录项
    Directory fileList[20];//本目录下内容？
}Directory;  
//下面是新的
typedef class Directory {
private:
	string fileName;
	char type;  //文件类型,0文件夹,1文件  
	//int startBlock; //文件是FCB起始盘块 文件夹是当前磁盘块号????
	FCB* FCBptr; //下一层目录项,文件夹此项为null，文件指向FCB的地址
	Directory *fileList[DIRECTORY_MAX];//目录为文件夹时本目录下内容的指针
	int fileListNum;
public:
	Directory();
	string get_fileName();
	void set_fileName(string newFileName);
	char get_type();
	void set_type(char newType);
	//int get_startBlock();
	//void set_startBlock(int newStartBlock);
	FCB*get_FCBptr();
	void set_FCBptr(FCB* newFCBptr);
	Directory* get_fileList(int i);
	void set_fileList(Directory*newFileList[],int i);
	void set_all_fileList(Directory*newFileList[]);
	//int get_fileList_num();
	int get_fileListNum();
	bool add_fileDirectory(Directory*directory);
	
}Directory;

void example(){
	initSystem();
	string op;
	//这里是命令行，在这里进行初始化，循环，交互
	while (1){
		cout << "[root@localhost " + currentDir + "]";
		cin >> op;
		bool endThisOperate = false;
		fflush(stdin);
		string[] args = op.split(' ');
		//这里加多空格容错
		switch (args[0]){
			case "ls":
			case "ll":
				//列出目录
				dirOp.list_directory("");
				endThisOperate = true;
				break;
			case "touch":
				dirName = args[1];
				//检查是否存在此目录，不存在则创建
				break;

			case "cat":
				fileName = args[1];
				//查看文件信息
				break;
			case ""


		}

		
	}
}

void init_system(){
	systemStartAddr = (char*)malloc(system_size * sizeof(char));  
    //初始化盘块的位示图  
    for(int i=0; i<block_count; i++)  
        systemStartAddr[i] = '0';  
    //用于存放位示图的空间已被占用  
    int bitMapSize = block_count * sizeof(char) / block_szie;//位示图占用盘块数:100  
    for(int i=0; i<bitMapSize; i++)//从零开始分配  
        systemStartAddr[i] = '1';   //盘块已被使用  
}

void test_unit(){
	//这里调试
}

int main(){
	example();

	return 0;
}
