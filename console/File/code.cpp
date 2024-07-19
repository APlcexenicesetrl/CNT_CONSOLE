// CNT - Code List
//Copyrights (C) 2024
//By TaimWay

//Change
/*
	1.TaimWay Upload ("First Create") 
*/
#include <bits/stdc++.h>
#include "strings.cpp"
using namespace std;
class code{
	private:
		void getCodeObject(const string& code, vector<string>& ReturnList){
			strings strings;
			vector <string> Object;
			
			strings.split(code,' ', Object);
		} 
	public:
		void run(string code){
			vector <string> Object;
			getCodeObject(code, Object);
		}
};

