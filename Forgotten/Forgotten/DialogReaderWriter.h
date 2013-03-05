#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
const string TAB1 = "\t";
const string TAB2 = "\t\t";
const string TAB3 = "\t\t\t";

const string TARGETSTR = "TARGET";
const string TEXT_PLACESTR = "TEXTPLACE";
const string ANSWERSTR = "ANSWER";
const string QUESTIONSTR = "QUESTION";
const string ANSWERTEXTSTR = "ANSWERTEXT";
const string CARD_ID = "CARD";
const string DECK_ID = "DECK";

class TagCls
{
private:
	string m_Token;
	string m_Value;
public:
	string getValue();
	string getToken();
	void setValue(string aValue);
	void setToken(string aToken);
};

class CaseValues
{
public:
	CaseValues(string aName, int aId);
	int isMatch(string& aName);
private:
	string m_Name;
	int m_Id;
};

typedef vector<CaseValues*> MapVector;

class DialogReaderWriter
{
public:
	DialogReaderWriter(string aFileName, bool isSave);
	void getTag(TagCls* aTag);
//	void getKeyWord(string& aValue, string& aToken);
	bool isEndOfFile();
	virtual ~DialogReaderWriter(void);
	int MapMemberName(MapVector& aVector, string& aName);
	void WriteToTxt(string aTabs, string aToken, string aValue);
private:
	ifstream m_Input;
	ofstream m_toTxt;
	void ManageLine(TagCls* aTag);
	void WhiteSpace(string& aToken);
};




