#include <bits/stdc++.h>
using namespace std;
void fetchver(string filename,int ver)//fetchver() prints the desired version of file
{
	stringstream str1;
	str1<<ver;
	string vf=".folder/v"+str1.str()+filename;
	FILE *fp;
	fp=fopen(vf.c_str(),"r");
	if(fp==NULL)
		printf("File could not be opened\n");
	else
	{
		while(feof(fp)==0)
		{
			char c=getc(fp);
			if(feof(fp)==0)
				putchar(c);
		}
	}
	return;
}
int trackcheck(string filename)//trackcheck() finds number of saved versions
{
	FILE *fp;
	fp=fopen(".file","r");
	if(fp==NULL)
		return -1;
	int flag=-1;
	while(feof(fp)==0)
	{
		char buf[100];
		fscanf(fp,"%s",buf);
		if(strcmp(buf,filename.c_str())==0)
		{
			fscanf(fp,"%s",buf);
			stringstream st(buf);
			st>>flag;
			break;
		}
	}
	fclose(fp);
	return flag;
}
int main(int argc,char **argv)
{
	if(argc==1)
	{
		cout<<"Please mention file names.\nType :\"./getver <file1.ext> <file2.ext>...\"\n";
		return 0;
	}
	while(argc-->1)
	{
		string filename=argv[argc];
		string cmd1="touch "+filename;
		system(cmd1.c_str());
		int dot=0;
		for(int i=0;i<filename.length();i++)
		{
			if(filename[i]=='.')
				dot=i;
		}
		string name=filename.substr(0,dot);
		int ver=trackcheck(filename);
		if(ver>1)
		{
			cout<<"File "<<filename<<" has "<<ver<<" saved versions.\nEnter which version number to access.\n";
			int inp;
			cin>>inp;
			if(inp>ver)
				cout<<"Invalid input.\n";
			else
			{
				cout<<"File : "<<filename<<"\nVersion : "<<inp<<endl;
				fetchver(filename,inp);
			}

		}
		else if(ver==1)
		{
			cout<<"File : "<<filename<<"\nVersion : "<<ver<<endl;
			fetchver(filename,ver);
		}
		else
			cout<<"File "<<filename<<" has no saved versions.\n";
		if(argc>1)
			cout<<endl;
	}
	return 0;
}
