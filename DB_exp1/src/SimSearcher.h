#pragma once
#include <vector>
#include <utility>
#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
const int SUCCESS = 0;
const int FAILURE = 1;

const int radix26[3]={1,58,58*58};

struct keyNode{
    int flag;
    keyNode*next;
};

class SimSearcher
{
public:
	SimSearcher();
	~SimSearcher();
    string *strSource;
    map< int, vector<int> >list;	
	int createIndex(const char *filename, unsigned q);
	int searchJaccard(const char *query, double threshold, std::vector<std::pair<unsigned, double> > &result);
	int searchED(const char *query, unsigned threshold, std::vector<std::pair<unsigned, unsigned> > &result);
   
    
  //一些辅助函数  
    int stringToInt(string s,int q){
        int sum = 0;
        for (int i=0; i<(int)s.size()&&i<q; i++)
             sum+=int(s[i]-64)*radix26[i];
        return sum;
    }
    
    int min(int a,int b){
        if (a<b)
            return a;
        else return b;
    }
    int getED(string s1,string s2){
        int len1 = s1.size();
        int len2 = s2.size();
        int **matrix = new int*[len1+1];
        for (int i=0; i<len1+1; i++)
            matrix[i] = new int [len2+1];
        for (int i=0; i<len1+1;i++)
            matrix[i][0]=i;
        for (int i=0; i<len2+1;i++)
            matrix[0][i]=i;
        
        for (int i=1; i<len1+1; i++){
            for (int j=1; j<len2+1; j++){
                int tem = min(matrix[i-1][j]+1,matrix[i][j-1]+1);
                int flag = 1-(s1[i-1]==s2[j-1]);
                matrix[i][j] = min(matrix[i-1][j-1]+flag,tem);
            }
        }
        
        //debug
       /* for (int i=0; i<len1+1; i++){
            for (int j=0; j<len2+1; j++){
                cout << matrix[i][j] << ' ';
            }
            cout << endl;
        }*/

        int ans= matrix[len1][len2];
        delete matrix;
        return ans;


    }

    vector<string> getPart(string s,int q){
        vector<string>str;
        string tem;
        for (int i=0; i<(int)s.size()-q+1; i++){
            tem="";
            for (int j=i; j<q+i; j++){
                tem += s[j];
            }
            str.push_back(tem);
        }
        
        // debug
       /* for (int i=0; i<str.size(); i++)
            cout << str.at(i) << ' ';
        cout << endl;
        */
        
        return str;
    }

    double getJaccard(string s1,string s2){
        int u_num = 0;
        int i_num = 0;
        int hash[70]={0};
        int tem1 = s1.size();
        int tem2 = s2.size();
        for (int i=0; i<(int)s1.size(); i++)
            hash[s1[i]-64]=1;

        for (int i=0; i<(int)s2.size(); i++){
            if (hash[s2[i]-64]!=0)
                tem2--;
        }

        u_num = tem1+tem2;
        i_num = s2.size()-tem2;
        
        //debug
       // cout <<"("<<u_num << "," <<i_num <<")" << endl;
       
        return double(i_num)/u_num;
    }

    string intToString(int x,int q){
        string ans="";
        int len = 0;
        int tem_q = q;
        while(tem_q>0){
            ans+=char((x%58)+64);
            x = x/58;
            len++;
            tem_q--;
        }
       
        return ans;
    }

};

