#include <bits/stdc++.h>
using namespace std;
int ver;
string filename;
string name;	
int trackcheck(string filename)//trackcheck() searches for filename in .file
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
int checkver(string name)//checkver() checks for untracked changes
{
	string cmd="md5sum -c --status .folder/."+name+".md5";
	return(system(cmd.c_str()));
}
void track(string filename)//track() adds filename in .file with ver=0
{
	FILE *fp;
	fp=fopen(".file","a");
	if(fp==NULL)
		return;
	fprintf(fp,"%s    0\n",filename.c_str());
	fclose(fp);
}
void hashit(string filename,string name)//hashit() saves md5sum in name.md5 in .folder
{
	string cmd="md5sum "+filename+" > .folder/."+name+".md5";
	system(cmd.c_str());
}
void savefile(string filename,int ver)//savefile() saves the current version in .folder
{
	stringstream str1;
	str1<<ver;
	string cmd="cp "+filename+" .folder/v"+str1.str()+filename;
	system(cmd.c_str());
}
void incver(string filename,int ver)//incver() increments the number of saved versions of the filename in .file
{
	FILE *fp;
	fp=fopen(".file","r");
	FILE *np;
	np=fopen("newfile.txt","w");
	if(fp==NULL)
		return;
	if(np==NULL)
		return;
	while(feof(fp)==0)
	{
		char buf[100];
		fscanf(fp,"%s",buf);
		fprintf(np,"%s    ",buf);
		if(strcmp(buf,filename.c_str())==0)
		{
			fscanf(fp,"%s\n",buf);
			fprintf(np,"%d\n",ver);
		}
		else
		{
			fscanf(fp,"%s\n",buf);
			fprintf(np,"%s\n",buf);
		}
	}
	remove(".file");
	rename("newfile.txt",".file");
	fclose(fp);
	fclose(np);
}
int main(int argc,char **argv)
{
	if(argc==1)
	{
		cout<<"Please mention file names.\nType :\"./run <file1.ext> <file2.ext>...\"\n";
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
		if(ver>=0)
		{
			if(checkver(name)==0)
			{
				if(ver==0)
				{
					cout<<"No change in file "<<filename<<", but version not saved.\nDo you want to save version y/n?\n";
					char res;
					cin>>res;
					if(res=='n' || res=='N')
						cout<<"File "<<filename<<" not saved.\n";
					else if(res=='y' || res=='Y')
					{
						savefile(filename,ver+1);
						incver(filename,ver+1);
						cout<<"File "<<filename<<" saved.\n";
					}
					else
						cout<<"Undefined response.\nFile "<<filename<<" not saved.\n";
				}
				else
					cout<<"No change in last saved version  of file "<<filename<<endl;
			}
			else
			{
				cout<<"Unsaved changes present in file "<<filename<<"\nDo you want to track changes y/n?\n";
				char res;
				cin>>res;
				if(res=='n' || res=='N')
					cout<<"Unsaved changes in file "<<filename<<" not tracked.\n";
				else if(res=='y' || res=='Y')
				{
					hashit(filename,name);
					cout<<"Changes in file "<<filename<<" tracked.\nDo you want to save this version y/n?\n";
					char res2;
					cin>>res2;
					if(res2=='n' || res2=='N')
						cout<<"Current version of file "<<filename<<" not saved.\n";
					else if(res2=='y' || res2=='Y')
					{
						savefile(filename,ver+1);
						incver(filename,ver+1);
						cout<<"Current version of file "<<filename<<" saved.\n";
					}
					else
						cout<<"Undefined response.\nCurrent version of file "<<filename<<" not saved.\n";
				}
				else
					cout<<"Undefined response.\nUnsaved changes in file "<<filename<<" not tracked.\n";
			}
		}
		else
		{
			cout<<"File "<<filename<<" not tracked.\nDo you want to track it y/n?\n";
			char res;
			cin>>res;
			if(res=='n' || res=='N')
				cout<<"File "<<filename<<" not tracked.\n";
			else if(res=='y' || res=='Y')
			{
				track(filename);
				hashit(filename,name);
				cout<<"File "<<filename<<" tracked.\nDo you want to save this version y/n?\n";
				char res2;
				cin>>res2;
				if(res2=='n' || res2=='N')
					cout<<"File "<<filename<<" not saved.\n";
				else if(res2=='y' || res2=='Y')
				{
					savefile(filename,ver+2);
					incver(filename,ver+2);
					cout<<"File "<<filename<<" tracked and saved.\n";
				}
				else
					cout<<"Undefined response.\nFile "<<filename<<" not saved\n";
			}
			else
				cout<<"Undefined response.\nFile "<<filename<<" not tracked.\n";
		}
		if(argc>1)
			cout<<endl;
	}
	return 0;
}
