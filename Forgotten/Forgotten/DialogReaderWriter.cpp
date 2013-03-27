#include "DialogReaderWriter.h"


DialogReaderWriter::DialogReaderWriter(string aFileName, bool isSave)
{
	if(isSave)
		m_toTxt = ofstream (aFileName);
	else
		m_Input = ifstream(aFileName);
}

void DialogReaderWriter::getTag(TagCls* aTag)
{
	if(m_Input.is_open())
	ManageLine(aTag);
}

void DialogReaderWriter::ManageLine(TagCls* aTag)
{
	string wToken = "";
	string wValue = "";
	getline(m_Input, wToken, '=');
	getline(m_Input, wValue);
	WhiteSpace(wToken);
	aTag->setValue(wValue);
	aTag->setToken(wToken);
}

void DialogReaderWriter::WhiteSpace(string& aToken)
{
	int pos = aToken.find_first_not_of(9);
	aToken.erase(0, pos);
}
int DialogReaderWriter::MapMemberName(MapVector& aVector, string& aName)
{
	int wId;

	CaseValues* wCase;
	for(int i = 0; i < aVector.size(); i++)
	{
		wCase = aVector[i];
		wId = aVector[i]->isMatch(aName);
		if(wId > -1)
			return wId;
	}
	return -1;
}

bool DialogReaderWriter::isEndOfFile()
{
	return m_Input.eof();
}

void DialogReaderWriter::WriteToTxt(string aTabs, string aToken, string aValue)
{
	m_toTxt << aTabs << aToken << "=" << aValue << "\n";
}

DialogReaderWriter::~DialogReaderWriter(void)
{
}

CaseValues::CaseValues(string aName, int aId): m_Name(aName), m_Id(aId)
{
}

int CaseValues::isMatch(string& aName)
{
	if(aName == m_Name)
		return m_Id;
	else
		return -1;
}

string TagCls::getToken()
{
	return m_Token;
}

string TagCls::getValue()
{
	return m_Value;
}

void TagCls::setToken(string aToken)
{
	m_Token = aToken;
}

void TagCls::setValue(string aValue)
{
	m_Value = aValue;
}
