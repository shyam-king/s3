#include<iostream.h>
#include<string.h>
#include<fstream.h>
#include<conio.h>

void fn()
{

	ifstream fin("C:\\s\\example.txt");
	if(!fin)
		cout<<"File does not exist ";
	else
	{
		int co=0;
		char c[80];
		while(fin.getline(c,80))
		{
			for(int i=0;c[i];i++)
				if(c[i]==' ')
					co++;
			if(co+1>=4)
				cout<<c;
		}
	}
}

void main()
{
	clrscr();
	fn();
	getch();
}