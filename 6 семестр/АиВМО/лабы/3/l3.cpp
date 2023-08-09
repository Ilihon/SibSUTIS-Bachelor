#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void yourinput(vector<vector<int>> table, int* needs, int m, int n)
{
	cout<<"\nSup-s";
	for(int i = 0; i < n; ++i)
		cout<<"\tB"<<i+1;
	cout<<"\tStock\n";
	for(int i = 0; i < m; ++i)
	{
		cout<<"A"<<i+1<<"\t";
		for(int j = 0; j < n+1; ++j)
		{
			cout << table[i][j] << "\t"; 
		}
		cout<<"\n";
	}
	cout << "Needs\t";
	for(int i = 0; i < n; ++i)
		cout<<needs[i]<<"\t";
	cout<<endl;
}
void yourdupinput(vector<vector<int>> table, int* needs, int m, int n,vector<vector<int>> table2)
{
	cout<<"\nSup-s";
	for(int i = 0; i < n; ++i)
		cout<<"\tB"<<i+1;
	cout<<"\tStock\n";
	for(int i = 0; i < m; ++i)
	{
		cout<<"A"<<i+1<<"\t";
		for(int j = 0; j < n+1; ++j)
		{
			if(j == n)
			{
				table[i][j] = table2[i][j];
			}
			if(table[i][j] >= 0)
				cout << table[i][j] << "\t"; 
			else
				cout << "-\t";
		}
		cout<<"\n";
	}
	cout << "Needs\t";
	for(int i = 0; i < n; ++i)
		cout<<needs[i]<<"\t";
	cout<<endl;
}

int main()
{
	ifstream in("1a.in");
	int m, n;
	//cout << "Input amount of providers: ";
	in >> m;
	//cout << "\nInput amount of consumers: ";
	in >> n;
	
	vector < vector <int>> table, duptable;
	int needs[n];
	for(int i = 0; i < m; ++i)
	{
		vector <int> temptable, tempduptable;
		for(int j = 0; j < n+1; ++j)
		{
			/*if(j != n)
			{
				cout<<"A"<<i+1<<"B"<<j+1<<" = ";
			}
			else
			{
				cout<<"Stocks for A"<<i+1<<" = ";
			}*/
			int temp;
			in >> temp;
			//cout<<endl;
			temptable.push_back(temp);
			if(j != n)
				tempduptable.push_back(-1);
			else
				tempduptable.push_back(temp);
		}
		table.push_back(temptable);
		duptable.push_back(tempduptable);
	}
	for(int i = 0; i < n; ++i)
	{
		//cout<<"Needs for B"<<i+1<<" = ";
		in >> needs[i];
		//cout<<endl;
	}
	
	cout << "\tYour input: "<<endl;
	yourinput(table,needs, m, n);
	
	int Zai = 0, Zbj = 0;
	for(int i = 0; i < m; ++i)
	{
		Zai+=table[i][n];
	}
	for(int i = 0; i < n; ++i)
	{
		Zbj+=needs[i];
	}
	cout<<"\n\tZai = "<<Zai<<"\t\tZbj = "<<Zbj<<"\n";
	int dif = abs(Zai-Zbj);
	bool add = false;
	if(dif == 0)
	{
		cout<<"\n\tClosed model. No need for addition\n";
	}
	else
	{
		cout<<"\n\tModel is opened("<<dif<<"). Adding new provider";
		vector <int> newpro;
		for(int i = 0; i < n; ++i)
			newpro.push_back(0);
		newpro.push_back(dif);
		table.push_back(newpro);
		vector <int> newduppro;
		for(int i = 0; i < n; ++i)
			newduppro.push_back(-1);
		newduppro.push_back(dif);
		duptable.push_back(newduppro);
		m++;
		add = true;
		cout<<"\n\n\tNew table: \n";
		yourinput(table,needs,m,n);
	}
	vector<vector<int>>restable;
	restable = table;
	int stolbdif[n], strdif[m];
	for(int i = 0; i < m; ++i)
	{
		vector <int> temp;
				for(int j = 0; j < n; ++j)
				{
					if(table[i][j] >= 0)
						temp.push_back(table[i][j]);
				}
				sort(temp.begin(),temp.end());
				int min = temp[0], secondmin = temp[1];
				strdif[i] = abs(min-secondmin);
	}
	for(int i = 0; i < n; ++i)
	{
		vector <int> temp;
				for(int j = 0; j < m; ++j)
				{
					if(table[j][i] > 0)
						temp.push_back(table[j][i]);
				}
				sort(temp.begin(),temp.end());
				if(temp.size() > 1)
				{
					int min = temp[0], secondmin = temp[1];
					stolbdif[i] = abs(min-secondmin);
				}
				else 
					stolbdif[i] = 0;
	}
	
	vector <int> checkedstolbs, checkedstrs;
	vector <pair<int,int>> indexes;
	int t = m+n;
	while(--t)
	{		
		cout<<"\nSup-s";
		for(int i = 0; i < n; ++i)
			cout<<"\tB"<<i+1;
		cout<<"\tStock\n";
		for(int i = 0; i < m; ++i)
		{
			cout<<"A"<<i+1<<"\t";
			for(int j = 0; j < n+1; ++j)
			{
				if(table[i][j] >= 0)
					cout << table[i][j] << "\t"; 
				else
					cout << "-\t";
			}
			if(strdif[i] >= 0)
				cout<<strdif[i]<<"\n";
			else
				cout<<"-\n";
		}
		cout << "Needs\t";
		for(int i = 0; i < n; ++i)
			cout<<needs[i]<<"\t";
		cout<<"\n\n\t";
		for(int i = 0; i < n; ++i)
		{
			if(stolbdif[i] >= 0)
				cout<<stolbdif[i]<<"\t";
			else
				cout<<"-\t";
		}
			
			
		vector <int> maxindstolb, maxindstr;
		int max = -1000000000;
		int ind;
		cout<<endl;
		for(int i = 0; i < n; ++i)
		{
			if(stolbdif[i] > max)
			{
				ind = i;
				max = stolbdif[i];
			}
		}	
		int compare1 = max;  
		maxindstolb.push_back(ind);
		max = -1000000000;
		cout<<endl;
		for(int i = 0; i < m; ++i)
		{
			if(strdif[i] > max)
			{
				max = strdif[i];
				ind = i;
			}
		}	
		int compare2 = max;
		maxindstr.push_back(ind);
		
		int ind_i, ind_j;
		if(compare1 > compare2)
		{
			//cout<<"\n\tMaximum is in the stolbrow";
			for(int i = 0; i < n; ++i)
			{
				if(stolbdif[i] == compare1)
				{
					maxindstolb.push_back(i);
				}
			}
			int min = 1000000000;
			for(int i = 0; i < maxindstolb.size(); ++i)
			{
				for(int j = 0; j < m; ++j)
				{
					if(table[j][maxindstolb[i]] < min && table[j][maxindstolb[i]] > 0)
					{
						min = table[j][maxindstolb[i]];
						ind_i = j;
						ind_j = maxindstolb[i];
					}
				}
			}
		}
		else if(compare1 < compare2)
		{
			//cout<<"\n\tMaximum is in the strrow";
			for(int i = 0; i < m; ++i)
			{
				if(strdif[i] == compare2)
				{
					maxindstr.push_back(i);
				}
			}
			int min = 1000000000;
			for(int i = 0; i < maxindstr.size(); ++i)
			{
				for(int j = 0; j < n; ++j)
				{
					if(table[maxindstr[i]][j] < min && table[maxindstr[i]][j] > 0)
					{
						min = table[maxindstr[i]][j];
						ind_i = maxindstr[i];
						ind_j = j;
					}
				}
			}
		}
		else
		{
			//cout<<"\n\tMaximum is in both";
			for(int i = 0; i < n; ++i)
			{
				if(stolbdif[i] == compare1)
				{
					maxindstolb.push_back(i);
				}
			}
			for(int i = 0; i < m; ++i)
			{
				if(strdif[i] == compare1)
				{
					maxindstr.push_back(i);
				}
			}
			int min = 1000000000;
			for(int i = 0; i < maxindstolb.size(); ++i)
			{
				for(int j = 0; j < m; ++j)
				{
					if(table[j][maxindstolb[i]] < min && table[j][maxindstolb[i]] > 0)
					{
						min = table[j][maxindstolb[i]];
						ind_i = j;
						ind_j = maxindstolb[i];
					}
				}
			}
			for(int i = 0; i < maxindstr.size(); ++i)
			{
				for(int j = 0; j < n; ++j)
				{
					if(table[maxindstr[i]][j] < min && table[maxindstr[i]][j] > 0)
					{
						min = table[maxindstr[i]][j];
						ind_i = maxindstr[i];
						ind_j = j;
					}
				}
			}
			if(min == 1000000000)
			{
				ind_i = maxindstr[0];
				ind_j = maxindstolb[0];
			}
		}
		cout<<"\n\t  MINIMAL ELEMENT: A"<<ind_i+1<<"B"<<ind_j+1<<endl;
		indexes.push_back(make_pair(ind_i,ind_j));
		if(needs[ind_j] > table[ind_i][n])
		{			
			duptable[ind_i][ind_j] = table[ind_i][n];
			needs[ind_j] -= table[ind_i][n];
			table[ind_i][n] = 0;
			for(int i = 0; i < n; ++i)
			{
				if(table[ind_i][i] >= 0)
					table[ind_i][i] = -1;
			}
			checkedstrs.push_back(ind_i);
		}
		else if(needs[ind_j] < table[ind_i][n])
		{
			duptable[ind_i][ind_j] = needs[ind_j];
			duptable[ind_i][n] -= needs[ind_j];
			table[ind_i][n] -= needs[ind_j];
			needs[ind_j] = 0;
			for(int i = 0; i < m; ++i)
			{
				if(table[i][ind_j] >= 0)
					table[i][ind_j] = -1;
			}
			checkedstolbs.push_back(ind_j);
		}
		else
		{
			duptable[ind_i][ind_j] = needs[ind_j];
			table[ind_i][n] = 0;
			needs[ind_j] = 0;
			for(int i = 0; i < n; ++i)
			{
				if(table[ind_i][i] >= 0)
					table[ind_i][i] = -1;
			}
			for(int i = 0; i < m; ++i)
			{
				if(table[i][ind_j] >= 0)
					table[i][ind_j] = -1;
				if(i+1 == m && t != 1)
				{
					duptable[i][ind_j] = 0;
					t--;
					indexes.push_back(make_pair(i,ind_j));
				}
			}
			checkedstrs.push_back(ind_i);
			checkedstolbs.push_back(ind_j);
		}
		
		yourdupinput(duptable,needs,m,n,table);
		
		for(int i = 0; i < m; ++i)
		{
			if(find(checkedstrs.begin(),checkedstrs.end(),i) == checkedstrs.end())
			{
				vector <int> temp;
				for(int j = 0; j < n; ++j)
				{
					if(table[i][j] >= 0)
						temp.push_back(table[i][j]);
				}
				sort(temp.begin(),temp.end());
				int min = temp[0], secondmin = temp[1];
				strdif[i] = abs(min-secondmin);
			}
			else
				strdif[i] = -1;
		}
		for(int i = 0; i < n; ++i)
		{
			if(find(checkedstolbs.begin(),checkedstolbs.end(),i) == checkedstolbs.end())
			{
				vector <int> temp;
				for(int j = 0; j < m; ++j)
				{
					if(table[j][i] > 0)
						temp.push_back(table[j][i]);
				}
				sort(temp.begin(),temp.end());
				if(temp.size() > 1)
				{
					int min = temp[0], secondmin = temp[1];
					stolbdif[i] = abs(min-secondmin);
				}
				else 
					stolbdif[i] = 0;
			}
			else
				stolbdif[i] = -1;
		}
	}
	int Z = 0;
	cout<<"\n\n\tZ = ";
	t = m+n-1;
	for(int i = 0; i < t; ++i)
	{
		if(duptable[indexes[i].first][indexes[i].second] != 0 && restable[indexes[i].first][indexes[i].second] != 0)
		{
			cout<<duptable[indexes[i].first][indexes[i].second] << " * " << restable[indexes[i].first][indexes[i].second];
			Z += duptable[indexes[i].first][indexes[i].second] * restable[indexes[i].first][indexes[i].second];
		}
		else 
		{
			cout<<0;
		}
		if(i+1 != t) cout<<" + ";
	}
	cout << " = " << Z;
	
	return 0;
}
