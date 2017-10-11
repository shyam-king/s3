#ifndef S3GOALMA_H
#define S3GOALMA_H
class  FILE_OPERATIONS 
{
	public :

		PLAYER loadPlayer(int n)
		{
			fstream f;
			f.open("Player.dat", ios::binary | ios::in);
			f.seekg(n * sizeof(PLAYER));
			PLAYER a;
			f.read((char*)&a, sizeof(PLAYER));
			f.close();
			return a;
		}

		void saveRoad (Road *roads, int n)
		{
			fstream f;
			f.open("ROADS.DAT", ios::binary | ios::in | ios::out);
			f.seekp(n * sizeof(Road) * 10);
			f.write((char*)roads, sizeof(Road)*10);
			f.close();
		}

		void loadRoad (Road *roads, int n)
		{
			fstream f;
			f.open("ROADS.BAT", ios::binary | ios::in);
			f.seekg(n * sizeof(Road)* 10);
			f.read((char*)roads, sizeof(Road)*10);
			f.close();
		}

		void loadLayout(House *h, Road *r, Tree *t, int n)
		{
			fstream f("layouts\\HOUSE.DAT", ios::binary | ios::in);
			f.seekg(n * sizeof(House)*30);
			f.read((char*)h, sizeof(House)*30);
			f.close();
			//roads
			f.open("layouts\\ROADS.DAT", ios::binary | ios::in);
			f.seekg(n*sizeof(Road)*10);
			f.read((char*)r, sizeof(Road)*10);
			f.close();
			//trees
			f.open("layouts\\TREE.DAT", ios::binary | ios::in);
			f.seekg(n * sizeof(Tree) * 30);
			f.read((char*)t, sizeof(Tree)*30);
			f.close();
		}

		void loadHouse (House *h, int n)
		{
			fstream f;
			f.open("House.dat", ios::binary | ios::in  );
			f.seekg(n * sizeof(House) * 30);
			f.read((char*)h, sizeof(House) * 30);
			f.close();
		}

		int loadGoalIndex(int n)
		{
			fstream f;
			f.open("goals.dat", ios::binary | ios::in );
			f.seekg(sizeof(n) * n);
			f.read((char*)&n, sizeof(n));
			f.close();
			return n;
		}

		void loadTrees (Tree *t, int n)
		{
			fstream f;
			f.open("Tree.dat", ios::binary | ios::in );
			f.seekg(n * sizeof(Tree) * 30);
			f.read((char*)t, sizeof(Tree) * 30);
			f.close();
		}

		int noOfPlayers()
		{
			fstream f;
			f.open("Player.dat", ios::binary | ios::in);
			f.seekg(0, ios::end);
			int n = f.tellg() / sizeof(PLAYER);
			f.close();

			return n;
		}
		void updation (PLAYER *a,House *b, Tree *c, Road *r, int n)
		{
			//for troubleshooting
			ofstream fout("ts.dat");
			fout << a->show_ID();
			fout.close();

			fstream f;
			//player details
			f.open("Player.dat",ios::binary|ios::out|ios::in);
			f.seekp(a->show_ID()*sizeof(PLAYER));
			f.write((char *)a,sizeof(PLAYER));
			f.close();
			//houses
			f.open("House.dat",ios::binary|ios::out|ios::in);
			f.seekp(a->show_ID()*sizeof(House)*30);
			f.write((char *)b,sizeof(House)*30);
			f.close();
			//trees
			f.open("Tree.dat",ios::binary|ios::out|ios::in);
			f.seekp(a->show_ID()*sizeof(Tree)*30);
			f.write((char *)c,sizeof(Tree)*30);
			f.close();
			//goalindex
			f.open("goals.dat", ios::binary | ios::in | ios::out);
			f.seekp(a->show_ID() * sizeof(n));
			f.write((char*)&n, sizeof(n));
			f.close();
			//roads
			f.open("ROADS.dat",ios::binary|ios::out|ios::in);
			f.seekp(a->show_ID()*sizeof(Road)*10);
			f.write((char *)r,sizeof(Road)*10);
			f.close();
		}
		void New_Player (PLAYER *a,House *b, Tree *c, Road *d)
		{
			//calculating the id of the player
			fstream f;
			f.open("Player.dat", ios::out | ios::in);
			int id = noOfPlayers();
			a->setid(id);
			a->setWalls(0);

			f.close();
			f.open("Player.dat",ios::binary|ios::out|ios::app);
			f.write((char *)a,sizeof(PLAYER));
			f.close();
			f.open("House.dat",ios::binary|ios::out|ios::app);
			f.write((char *)b,sizeof(House)*30);
			f.close();
			f.open("Tree.dat",ios::binary|ios::out|ios::app);
			f.write((char *)c,sizeof(Tree)*30);
			f.close();
			f.open("goals.dat", ios::binary | ios::app);
			int n = 0;
			f.write((char*)&n, sizeof(n));
			f.close();
			f.open("ROADS.dat",ios::binary|ios::out|ios::app);
			f.write((char *)d,sizeof(Road)*10);
			f.close();
		}
		void Delete (int ID)
		{
			fstream f;
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
