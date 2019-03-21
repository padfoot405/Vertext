#include <bits/stdc++.h>
using namespace std;
void cleanse()
{
	string cmd="rm .file *.*";
	system(cmd.c_str());
	cmd="rm -r .folder";
	system(cmd.c_str());
}
void remake()
{
	string cmd="touch .file";
	system(cmd.c_str());
	cmd="mkdir .folder";
	system(cmd.c_str());
}
int main()
{
	cleanse();
	remake();
	return 0;
}