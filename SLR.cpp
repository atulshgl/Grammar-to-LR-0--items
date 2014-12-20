#include<iostream>
#include<cstdio>
#include<list>
#include<queue>
#include<set>
using namespace std;

struct node
{
    list<string> lhs;
    list<string> rhs;
};
node I[102];
queue<string> q;
int total,k;
char adj[20][20];
void self_prod(int x,node ini)
{
    string temp,ch;
    while(!q.empty())
    {
        ch="zxcxzsx";
        temp=q.front();
        q.pop();
        int i,l=temp.size();
        for(i=0;i<l;i++)
        {
            if(temp[i]=='.' && i<l-1)
            {
                ch=temp[i+1];
                break;
            }
        }
        if(i<l)
        {
            list<string>::iterator it1=ini.lhs.begin(),it2=ini.rhs.begin(),jt1,jt2;
            for(;it1!=ini.lhs.end();it1++,it2++)
            {
                if((*it1)==ch)
                {
                    jt1=I[x].lhs.begin();
                    jt2=I[x].rhs.begin();
                    for(;jt1!=I[x].lhs.end();jt1++,jt2++)
                    {
                        if((*jt1)==(*it1) && (*jt2)==("."+(*it2)))
                            break;
                    }
                    if(jt1==I[x].lhs.end())
                    {
                        I[x].lhs.push_back((*it1));
                        I[x].rhs.push_back("."+(*it2));
                        q.push("."+(*it2));
                    }
                }
            }
        }
    }
}
void next_prod(int x,node ini)
{
    node temp;
    string str="",ch="",lhs,rhs;
    int i,j;
    set<string> st;
    cout<<"During next_prod of I"<<x<<endl;
    list<string>::iterator it1=I[x].lhs.begin(),it2=I[x].rhs.begin(),jt1,jt2,kt1,kt2;
    for(;it1!=I[x].lhs.end();it1++,it2++)
    {
        str=(*it2);
        int l=str.size();
        for(i=0;i<l;i++)
        {
            if(str[i]=='.' && i<l-1)
            {
                ch=str[i+1];
                break;
            }
        }
        if(i<l)
        {
            int sz=st.size();
            st.insert(ch);
            if(st.size()==sz+1)
            {
                jt1=I[x].lhs.begin();
                jt2=I[x].rhs.begin();
                for(;jt1!=I[x].lhs.end();jt1++,jt2++)
                {
                    rhs=(*jt2);
                    l=rhs.size();
                    string so_far="";
                    for(j=0;j<l-1;j++)
                    {
                        if(j>0)
                            so_far+=rhs[j-1];
                        if(rhs[j]=='.' && rhs[j+1]==ch[0])
                        {
                           
                            so_far+=rhs[j+1];
                            so_far+=".";
                            j+=2;
                            while(j<l)
                            {
                                so_far+=rhs[j];
                                j++;
                            }
                            temp.lhs.push_back((*jt1));
                            temp.rhs.push_back(so_far);
                            break;
                        }
                    }
                }
                I[101]=temp;
                jt1=I[101].lhs.begin();
                jt2=I[101].rhs.begin();
                cout<<"Initial I"<<total<<" state:\n";
                for(;jt1!=I[101].lhs.end();jt1++,jt2++)
                {
                    cout<<*jt1<<"->"<<*jt2<<endl;
                    q.push(*jt2);
                }
                self_prod(101,ini);
                for(i=0;i<=total;i++)
                {
                    jt1=I[101].lhs.begin();
                    jt2=I[101].rhs.begin();
                    for(;jt1!=I[101].lhs.end();jt1++,jt2++)
                    {
                        kt1=I[i].lhs.begin();
                        kt2=I[i].rhs.begin();
                        for(;kt1!=I[i].lhs.end();kt1++,kt2++)
                        {
                            if((*kt1)==(*jt1) && (*kt2)==(*jt2))
                                break;
                        }
                        if(kt1==I[i].lhs.end())
                            break;
                    }
                    if(jt1==I[101].lhs.end())
                        break;
                }
                if(i>total)
                {
                    total++;
                   // cout<<"Total is : "<<total<<endl;
                    I[total]=I[101];
                    adj[x][total]=ch[0];
                }
                else
                    adj[x][i]=ch[0];
                I[101].lhs.clear();
                I[101].rhs.clear();
                temp.lhs.clear();
                temp.rhs.clear();
            }
        }
    }
}
int main()
{
    string p;
    node ini;
    string lhs;
    string rhs;
    int i,j,n,curr=0;
    for(i=0;i<100;i++)
    {
        I[i].lhs.clear();
        I[i].rhs.clear();
    }
    for(i=0;i<20;i++)
        for(j=0;j<20;j++)
            adj[i][j]=' ';
    cout<<"Enter the number of productions: ";
    cin>>n;
    for(i=0;i<n;i++)
    {
        cin>>lhs>>rhs;
        ini.lhs.push_back(lhs);
        ini.rhs.push_back(rhs);
    }
    I[0].lhs.push_back("Z");
    I[0].rhs.push_back(".S");
    q.push(*(I[0].rhs.begin()));
    self_prod(0,ini);
    while(curr<=total)
    {
        next_prod(curr,ini);
        curr++;
    }
    cout<<"\nSLR :\n";
    cout<<"   ";
    for(i=0;i<=total;i++)
        cout<<"I"<<i<<" ";
    cout<<endl;
    for(i=0;i<=total;i++)
    {
        cout<<"I"<<i;
        for(j=0;j<=total;j++)
            cout<<" "<<adj[i][j]<<" ";
        cout<<endl;
    }
    cout<<"\n State description:\n";
    for(i=0;i<=total;i++)
    {
        cout<<"I"<<i<<" :\n";
        list<string>::iterator kt1,kt2;
        kt1=I[i].lhs.begin();
        kt2=I[i].rhs.begin();
        for(;kt1!=I[i].lhs.end();kt1++,kt2++)
            cout<<"\t"<<*kt1<<"->"<<*kt2<<endl;
        cout<<endl;
    }
    return 0;
}
/*
Test cases:

3
S AA
A aA
A b

6
S dA
S aB
A bA
A c
B bB
B c
*/
