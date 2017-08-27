#ifndef S3GOALMA_H
#define S3GOALMA_H
class  FILE_OPERATIONS 
{
	fstream  f;
	public :
	void updation (PLAYER a,House b[30],Tree c[30])
	{
		f.open("Player.dat",ios::binary|ios::out|ios::ate);
		f.seekp(a.show_ID()*sizeof(PLAYER));
		f.write((char *)&a,sizeof(PLAYER));
		f.close();
		f.open("House.dat",ios::binary|ios::out|ios::ate);
		f.seekp(a.show_ID()*sizeof(House)*30);
		f.write((char *)&b,sizeof(House)*30);
		f.close();
		f.open("Tree.dat",ios::binary|ios::out|ios::ate);
		f.seekp(a.show_ID()*sizeof(Tree)*30);
		f.write((char *)&c,sizeof(Tree)*30);
		f.close();
	}
	int New_Player (PLAYER &a,House b[30],Tree c[30])
	{
		//calculating the id of the player
		f.open("Player.dat", ios::out | ios::ate);
		int id = f.tellp();
		id = id / sizeof(PLAYER);
		a.setif(id);
		f.close();
		f.open("Player.dat",ios::binary|ios::out|ios::app);
		f.write((char *)&a,sizeof(PLAYER));
		f.close();
		f.open("House.dat",ios::binary|ios::out|ios::app);
		f.write((char *)b,sizeof(House)*30);
		f.close();
		f.open("Tree.dat",ios::binary|ios::out|ios::app);
		f.write((char *)c,sizeof(Tree)*30);
		f.close();

	}
	void Delete (int ID)
	{
		PLAYER s;
		ofstream fout("Temp.dat",ios::binary)
			int flag=0;
		f.open("Player.dat", ios::in);
		while(f.read((char*)&s,sizeof(s)))
		{
			if(ID==s.show_ID())
				flag=1;
			else
			{
				if(flag==1)
					s.setid(s.show_ID()-1);
				fout.write((char*)&s,sizeof(s));
			}
		}
		fout.close();
		f.close();
		remove("Player.dat");
		rename("Temp.dat","Player.dat");
		//House
		House b[30];
		f.open("House.dat", ios::in);
		fout.open("Temp.dat",ios::binary);
		while(f.read((char*)b,sizeof(b)))
		{
			if(ID!=s.show_ID())
				fout.write((char*)b,sizeof(b));
		}
		fout.close();
		f.close();
		remove("House.dat");
		rename("Temp.dat","House.dat");

		//Tree

		Tree c[30];
		f.open("tree.dat", ios::in);
		fout.open("Temp.dat",ios::binary)
			while(f_t.read((char*)c,sizeof(c)))
			{
				if(ID!=s.show_ID())
					fout.write((char*)c,sizeof(c));
			}
		fout.close();
		f.close();
		remove("Tree.dat");
		rename("Temp.dat","Tree.dat");
	}

} fileop;

#endif
