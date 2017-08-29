#ifndef S3GOALMA_H
#define S3GOALMA_H
class  FILE_OPERATIONS 
{
	fstream  f("Player.dat",ios::binary|ios::in|ios::out);
	fstream f_h("House.dat",ios::binary|ios::in|ios::out);
	fstream f_t("Tree.dat",ios::binary|ios::in|ios::out);
	public :
	void updation (PLAYER a,House b[30],Tree c[30])
	{
		f.seekp(a.show_ID()*sizeof(PLAYER));
		f.write((char *)&a,sizeof(PLAYER));
		f.seekp(a.show_ID()*sizeof(House)*30);
		f.write((char *)&b,sizeof(House)*30);
		f.seekp(a.show_ID()*sizeof(Tree)*30);
		f.write((char *)&c,sizeof(Tree)*30);
	}
	int New_Player (PLAYER a,House b[30],Tree c[30])
	{
		f.seekp(0,ios::end);
		f.write((char *)&a,sizeof(PLAYER));
		f_h.seekp(0,ios::end);
		f_h.write((char *)&b,sizeof(House)*30);
		f_t.seekp(0,ios::end);
		f_t.write((char *)&c,sizeof(Tree)*30);
		return a.show_ID();
	}
	void Delete (int ID)
	{
		PLAYER s;
		ofstream fout("Temp.dat",ios::binary)
			int flag=0;
		while(f.read((char*)&s,sizeof(s)))
		{
			if(ID==s.show_ID())
				flag=1;
			else
			{
				if(flag==1)
					s.setid(s.show_ID()-1);
				fout.write(char*)&s,sizeof(s));
			}
		}
		fout.close();
		f.close();
		remove("Player.dat");
		rename("Temp.dat","Player.dat");
		//House
		House b[30];
		fout.open("Temp.dat",ios::binary)
			int flag=0;
		while(f_h.read((char*)&b,sizeof(b)*30))
		{
			if(ID!=s.show_ID())
				fout.write((char*)&s,sizeof(c)*30);
		}
		fout.close();
		f_h.close();
		remove("House.dat");
		rename("Temp.dat","House.dat");

		//Tree

		Tree c[30];
		fout.open("Temp.dat",ios::binary)
			int flag=0;
		while(f_t.read((char*)&c,sizeof(b)*30))
		{
			if(ID!=s.show_ID())
				fout.write((char*)&c,sizeof(c)*30);
		}
		fout.close();
		f_t.close();
		remove("Tree.dat");
		rename("Temp.dat","Tree.dat");
	}

};

#endif
