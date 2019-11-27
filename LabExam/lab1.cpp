#include <bits/stdc++.h>
using namespace std;
int n=8;
vector<string> prodns;
vector<char> nt;
vector<char> completedfirst;
vector<set<char> > first;
vector<char> completedfollow;
vector<set<char> > follow;
vector<vector<vector<string> > > parsingtable;
int getindex(char a)
{
								switch(a){
																case 'E':return 0;
																case 'e':return 1;
																case 'T':return 2;
																case 't':return 3;
																case 'F':return 4;
																case 'i':return 0;
																case '+':return 1;
																case '*':return 2;
																case '(':return 3;
																case ')':return 4;
																case '$':return 5;

								}

}
set<char> findFirst(char a)
{
								set<char> myset;
								if(find(nt.begin(),nt.end(),a)==nt.end())
																myset.insert(a);
								else
								{
																for(int i=0;i<n;i++)
																{ int l=prodns[i].length();


																								if(prodns[i][0]==a)
																								{
																																if(prodns[i][2]=='#')
																																{
																																								myset.insert('#');
																																								break;
																																}
																																else
																																{
																																								for(int m=2;m<l;i++)
																																								{
																																																set<char> firstnext=findFirst(prodns[i][m]);
																																																if(firstnext.find('#')==firstnext.end())
																																																{
																																																								myset.insert(firstnext.begin(),firstnext.end());
																																																								break;
																																																}
																																																else
																																																{
																																																								myset.insert(firstnext.begin(),firstnext.end());
																																																								myset.erase(myset.find('#'));
																																																}
																																								}
																																}
																								}

																}
								}
								if(find(completedfirst.begin(),completedfirst.end(),a)==completedfirst.end())
								{
																completedfirst.push_back(a);
																first.push_back(myset);
								}
								return myset;


}
set<char> findFollow(char a)
{
								set<char> myset;
								if(a==prodns[0][0])
								myset.insert('$');
								for(int i=0;i<n;i++)
								{
																int l=prodns[i].length();
																for(int m=2;m<l;m++)
																{
																								if(prodns[i][m]==a&&m==l-1)
																								{       if(prodns[i][m]!=prodns[i][0]){
																																set<char> fl=findFollow(prodns[i][0]);
																																myset.insert(fl.begin(),fl.end());
																																}

																								}
																								else if(prodns[i][m]==a)

																								{
																																int p;
																																for(p=m+1;p<l;p++)
																																{
																																								set<char> fp=findFirst(prodns[i][p]);
																																								if(fp.find('#')!=fp.end())//epsilon found
																																								{
																																																fp.erase(fp.find('#'));
																																																myset.insert(fp.begin(),fp.end());
																																								}
																																								else
																																								{
																																																myset.insert(fp.begin(),fp.end());
																																																break;
																																								}
																																}
																																if(p==l){
																																set<char> fl=findFollow(prodns[i][0]);
																																myset.insert(fl.begin(),fl.end());
																																}
			break;
																								}
																}
								}
								if(find(completedfollow.begin(),completedfollow.end(),a)==completedfollow.end())
								{
																completedfollow.push_back(a);
																follow.push_back(myset);
								}
								return myset;
}
void displayParsingTable()
{
								cout<<"\ti\t+\t*\t(\t)\t$"<<endl;
								cout<<"E\t";
								for(int i=0;i<6;i++)
								{
																for(auto rx=parsingtable[0][i].begin();rx!=parsingtable[0][i].end();rx++)
																								cout<<*rx;
																cout<<"\t";
								}
								cout<<endl;
								cout<<"e\t";
								for(int i=0;i<6;i++)
								{
																for(auto rx=parsingtable[1][i].begin();rx!=parsingtable[1][i].end();rx++)
																								cout<<*rx;
																cout<<"\t";
								}
								cout<<endl;
								cout<<"T\t";
								for(int i=0;i<6;i++)
								{
																for(auto rx=parsingtable[2][i].begin();rx!=parsingtable[2][i].end();rx++)
																								cout<<*rx;
																cout<<"\t";
								}
								cout<<endl;
								cout<<"t\t";
	for(int i=0;i<6;i++)
								{
																for(auto rx=parsingtable[3][i].begin();rx!=parsingtable[3][i].end();rx++)
																								cout<<*rx;
																cout<<"\t";
								}
								cout<<endl;
								cout<<"F\t";
								for(int i=0;i<6;i++)
								{
																for(auto rx=parsingtable[4][i].begin();rx!=parsingtable[4][i].end();rx++)
																								cout<<*rx;
																cout<<"\t";
								}
								cout<<endl;
}
void check(string input)
{
								string stack="$E";
								input+="$";
								int i=0;
								int l=stack.length()-1;
								int len=input.length();
								cout<<"Stack\t\tInput\t\tOutput"<<endl;
                                cout<<"------------------------------------------------------------------------"<<endl;
								int k=0;
								while(i<len)
								{
																cout<<stack<<"\t\t"<<input<<"\t\t";
																if(stack=="$"&&i==len-1)
																{       cout<<"Accepted;Successful"<<endl;break;}
																else if(find(nt.begin(),nt.end(),stack[l])!=nt.end())
																{
																								string prodn=parsingtable[getindex(stack[l])][getindex(input[i])][0];
																								cout<<prodn<<endl;
																								stack=stack.substr(0,l);
																								for(int m=prodn.length()-1;m>=2;m--)
																								if(prodn[m]!='#')
																								stack+=prodn[m];
																								l=stack.length()-1;
																}
																else if(stack[l]==input[i])
																{
																								stack=stack.substr(0,l);
																								l=stack.length()-1;
																								input[i]=' ';
																								i++;
																								cout<<endl;
																}
																k++;
								}

}
int main()
{

								parsingtable.resize(5);
								for(int i=0;i<5;i++)
																parsingtable[i].resize(6);
								prodns.push_back("E=Te");
								prodns.push_back("e=+Te");
								prodns.push_back("e=#");
								prodns.push_back("T=Ft");
								prodns.push_back("t=*Ft");
								prodns.push_back("t=#");
								prodns.push_back("F=(E)");
								prodns.push_back("F=i");
								nt.push_back('E');
								nt.push_back('e');
								nt.push_back('T');
								nt.push_back('t');
								nt.push_back('F');
								for(auto itr=nt.begin();itr!=nt.end();itr++)
								{
																set<char> ff=findFirst(*itr);
																cout<<"First of ";
																if(*itr=='e')
																								cout<<"E'";
																else if(*itr=='t')
																								cout<<"T'";
																else
																cout<<*itr;
																cout<<" = ";
																for(auto x=ff.begin();x!=ff.end();x++)
																								cout<<*x<<" ";
																cout<<endl;
								}
								for(auto itr=nt.begin();itr!=nt.end();itr++)
								{
																set<char> ff=findFollow(*itr);
																cout<<"Follow of ";
																if(*itr=='e')
																								cout<<"E'";
																else if(*itr=='t')
																								cout<<"T'";
																else
																cout<<*itr;
																cout<<" = ";
																for(auto x=ff.begin();x!=ff.end();x++){
																								cout<<*x<<" ";
																}
																cout<<endl;
								}
							//construction of parsing table
                                cout<<"Suppose e=E', t= T'"<<endl;
								for(int i=0;i<n;i++)
								{
																int l=prodns[i].length();
																set<char> firstin;
																int m;
																for(m=2;m<l;m++)
																{
																								set<char> temp=findFirst(prodns[i][m]);
																								if(temp.find('#')==temp.end())
																								{
																																firstin.insert(temp.begin(),temp.end());
																																break;
																								}
																								else
																								{
																																temp.erase(temp.find('#'));
																																firstin.insert(temp.begin(),temp.end());
																								}
																}
																if(m==l)
																								firstin.insert('#');
																cout<<"First of "<<prodns[i].substr(2)<<" =";
																for(auto x=firstin.begin();x!=firstin.end();x++)
																{
																								cout<<*x<<" ";
																								//cout<<endl;
																								if(*x!='#')
																								parsingtable[getindex(prodns[i][0])][getindex(*x)].push_back(prodns[i]);
																}
                                                                cout<<endl;
																if(firstin.find('#')!=firstin.end())
																{
																								set<char> follin=findFollow(prodns[i][0]);
																								for(auto ir=follin.begin();ir!=follin.end();ir++)
																																if(find(parsingtable[getindex(prodns[i][0])][getindex(*ir)].begin(),parsingtable[getindex(prodns[i][0])][getindex(*ir)].end(),prodns[i])==parsingtable[getindex(prodns[i][0])][getindex(*ir)].end())
																																parsingtable[getindex(prodns[i][0])][getindex(*ir)].push_back(prodns[i]);

																}
	if(firstin.find('#')!=firstin.end())
																{
																								set<char> follin=findFollow(prodns[i][0]);
																								if(follin.find('$')!=follin.end())
																								{
																															if(find(parsingtable[getindex(prodns[i][0])][getindex('$')].begin(),parsingtable[getindex(prodns[i][0])][getindex('$')].end(),prodns[i])==parsingtable[getindex(prodns[i][0])][getindex('$')].end())
																																parsingtable[getindex(prodns[i][0])][getindex('$')].push_back(prodns[i]);

																								}

																}
								}
                                cout<<"------------------------------------------------------------------------"<<endl;
                                cout<<"\tLL(1) Parsing Table"<<endl;
                                cout<<"------------------------------------------------------------------------"<<endl;
								displayParsingTable();
								cout<<"Enter input string :";
								string inp;
								cin>>inp;
								check(inp);
								return 0;
}