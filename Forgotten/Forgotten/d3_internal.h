/*
	For documentation, tools & latest version:
	http://iki.fi/sol/d3/
	
	
	
	DialogTree (D3) License (based on the XFree86 1.1 license)
	
	Copyright (C) 2011 Jari Komppa, All rights reserved.
	
	Permission is hereby granted, free of charge, to any person obtaining 
	a copy of this software and associated documentation files (the 
	"Software"), to deal in the Software without restriction, including 
	without limitation the rights to use, copy, modify, merge, publish, 
	distribute, sublicence, and/or sell copies of the Software, and to 
	permit persons to whom the Software is furnished to do so, subject 
	to the following conditions:
	
	1. Redistributions of source code must retain the above copyright 
	notice, this list of conditions, and the following disclaimer.
	
	2. Redistributions in binary form must reproduce the above copyright 
	notice, this list of conditions and the following disclaimer in the 
	documentation and/or other materials provided with the distribution, 
	and in the same place and form as other copyright, license and 
	disclaimer information.
	
	3. The end-user documentation included with the redistribution, if 
	any, must include the following acknowledgment: "This product uses
	the DialogTree (D3) engine by Jari Komppa (http://iki.fi/sol)", in 
	the same place and form as other third-party acknowledgments. 
	Alternately, this acknowledgment may appear in the software itself, 
	in the same form and location as other such third-party 
	acknowledgments.
	
	4. Except as contained in this notice, the name of Jari Komppa shall
	not be used in advertising or otherwise to promote the sale, use or 
	other dealings in this Software without prior authorization from 
	Jari Komppa.
	
	THIS SOFTWARE IS PROVIDED 'AS IS' AND ANY EXPRESSED OR IMPLIED 
	WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
	DISCLAIMED. IN NO EVENT SHALL JARI KOMPPA BE LIABLE FOR ANY 
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
	GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
	WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
	OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
	EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
*/

#ifndef D3_INTERNAL_H
#define D3_INTERNAL_H

struct d3localizedstring
{
	int mLanguages;
	char **mLanguageID;
	char **mString;
};

struct d3answer
{
	char *mTarget;
	struct d3localizedstring mAnswer;
	char *mTags_need;
	char *mTags_not;
	char *mUserData;
	int mValid;
};

struct d3card
{
	char *mID;
	struct d3localizedstring mQuestion;
	char *mSet;
	char *mClear;
	char *mUserData;
	int mAnswers;
	struct d3answer *mAnswer;
};

struct d3deck
{
	char *mID;
	char *mUserData;
	int mCards;
	struct d3card *mCard;
};

struct d3tag
{
	struct d3tag *mNext;
	unsigned int mHash;
	char *mTag;
};

struct d3
{
	struct d3tag *mTag;
	int mTagCount;
	int mBytecount;
	char *mLang;
	struct d3deck *mCurrentDeck;
	struct d3card *mCurrentCard;
	unsigned int mCurrentAnswerCount;
};

#endif