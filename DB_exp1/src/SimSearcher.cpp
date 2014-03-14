#include "SimSearcher.h"
using namespace std;
SimSearcher::SimSearcher()
{


}

SimSearcher::~SimSearcher()
{
}
// q = 3;
// edThreshold = 2;
// jaccardThreshold =0.85
//string int2string(int hash);


int SimSearcher::createIndex(const char *filename, unsigned q)
{
    ifstream in;
    in.open(filename);
    string tem="";
    int len=0;
    while((in >> tem) && tem!=""){
      //  cout << len << ":" << tem << endl; 
        vector<string> temp = getPart(tem,q);
        for (int i=0; i<(int)temp.size(); i++){
           list[stringToInt(temp[i],q)].push_back(len);
        }
        len++;
    }
    //cout << "debug" << stringToInt("uio",q) << ":" <<  intToString(stringToInt("uio",q),q) << endl;
    map<int,vector<int> >::iterator iter;
    for(iter = list.begin(); iter != list.end(); iter++){
         cout << iter->first << ":" << intToString(iter->first,q)<< ":";
        for (int i=0; i<(int)(iter->second).size(); i++){
            cout << (iter->second).at(i) << "---";
        }
        cout << endl;
    }

   // cout << getED("Tom Hanks","Ton Hank") << endl;
   // vector<string> str = getPart("huioiiii",3);
   // cout << getJaccard("abc","bcd") << endl;
    
    return SUCCESS;
}

int SimSearcher::searchJaccard(const char *query, double threshold, vector<pair<unsigned, double> > &result)
{
	result.clear();
	return SUCCESS;
}

int SimSearcher::searchED(const char *query, unsigned threshold, vector<pair<unsigned, unsigned> > &result)
{
	result.clear();
	return SUCCESS;
}

