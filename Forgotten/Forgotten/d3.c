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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "d3.h"
#include "d3_internal.h"

/////////////////////////////////////////////////////////////////////
// Defines

#define MAGIC 0x00013364 // 'd' '3' 1 0 in reverse
#define MAX_TAG_LENGTH 256 // assuming sane tag length (for a single tag)

/////////////////////////////////////////////////////////////////////
// Some internal functions

static char *d3_tokenize(char *aBuf, char *aSrc)
{
	int i;
	if (aSrc == NULL || *aSrc == 0 || aBuf == NULL)
	{
		return NULL;
	}

	// Skip whitespace
	while (*aSrc == ' ' ||
		   *aSrc == '\t' ||
		   *aSrc == ',')
	{
		   aSrc++;
	}

	if (*aSrc == 0) 
	{
		return NULL;
	}

	i = 0;

	// Scan until whitespace (or null)
	while (*aSrc != ' ' &&
		   *aSrc != '\t' &&
		   *aSrc != ',' &&
		   *aSrc != 0)
	{
		*aBuf = *aSrc;
		aBuf++;
		aSrc++;
		i++;
		if (i >= MAX_TAG_LENGTH)
		{
			return NULL;
		}
	}
	*aBuf = 0;

	// Return current scan pointer so we can find next token too
	return aSrc;
}

static char d3_toupper(char c)
{
	if (c >= 'a' && c <= 'z')
		return c - ('a' - 'A');
	return c;
}

static int d3_strcasecmp(const char *a, const char *b)
{
	if (a == NULL && b == NULL)
		return 0;
	if (a == NULL || b == NULL)
		return (int)a-(int)b;

	while (*a || *b)
	{
		if (*a != *b)
			return *a - *b;
		a++;
		b++;
	}

	return 0;
}

static unsigned int d3_hash(const char *aString)
{
  unsigned int t = 0;
  
  while (*aString)
  {
	  // ROL 3
	  t = (t << 3) | (t >> 29);
	  t ^= d3_toupper(*aString);
	  aString++;
  }

  return t;
}

static char * d3_strdup(const char *aSrc)
{
	int l;
	char * buf;
	if (aSrc == NULL)
		return NULL;
	if (*aSrc == 0)
		return NULL;
	
	l = 0;
	while (aSrc[l]) l++;

	buf = malloc(l + 1);
	if (buf == NULL)
		return NULL;

	memcpy(buf, aSrc, l);
	buf[l] = 0;

	return buf;
}

/////////////////////////////////////////////////////////////////////
// Implementation

int d3_clear_all_tags(struct d3 *aD3)
{
	struct d3tag *walker;
	struct d3tag *last;

	if (aD3 == NULL)
		return -1;

	walker = aD3->mTag;
	last = NULL;
	while (walker)
	{
		last = walker;
		walker = walker->mNext;
		free(last->mTag);
	}
	aD3->mBytecount = 0;
	aD3->mTagCount = 0;
	aD3->mTag = NULL;
	return 0;
}

int d3_serialize_estimate(struct d3 *aD3)
{
	if (aD3 == NULL)
		return 0;
	
	if (aD3->mTagCount == 0)
		return 1;

	return aD3->mBytecount + aD3->mTagCount;
}

int d3_serialize(struct d3 *aD3, char *aBuffer, int *aBytesUsed, int aBufferSize)
{
	struct d3tag *walker;
	int bytes;
	if (aD3 == NULL || aBuffer == NULL)
		return -1;
	bytes = d3_serialize_estimate(aD3);
	if (aBufferSize < bytes)
		return -1;
	
	walker = aD3->mTag;
	while (walker)
	{
		int l = strlen(walker->mTag);
		memcpy(aBuffer, walker->mTag, l);
		aBuffer += l;
		aBuffer[0] = ',';
		walker = walker->mNext;
		if (walker) aBuffer++;
	}
	aBuffer[0] = 0;
	
	if (aBytesUsed)
		*aBytesUsed = bytes;

	return 0;
}

int d3_set_language(struct d3 *aD3, const char *aLanguage)
{
	if (aD3 == NULL)
		return -1;
	free(aD3->mLang);
	aD3->mLang = NULL;
	if (aLanguage)
		aD3->mLang = d3_strdup(aLanguage);
	return 0;
}

int d3_is_tag(struct d3 *aD3, const char *aTag)
{
	unsigned int t;
	struct d3tag *walker;

	if (aD3 == NULL || aTag == NULL)
		return 0;

	t = d3_hash(aTag);

	walker = aD3->mTag;
	
	while (walker)
	{
		if (walker->mHash == t)
		{
			if (d3_strcasecmp(walker->mTag, aTag) == 0)
				return 1;
		}

		walker = walker->mNext;
	}
	return 0;
}

int d3_clear_tag(struct d3 *aD3, const char *aTag)
{
	unsigned int t;
	struct d3tag *walker;
	struct d3tag *last;

	if (aD3 == NULL || aTag == NULL)
		return -1;

	t = d3_hash(aTag);

	walker = aD3->mTag;
	last = NULL;
	while (walker)
	{
		if (walker->mHash == t)
		{
			if (d3_strcasecmp(walker->mTag, aTag) == 0)
			{
				aD3->mTagCount--;
				aD3->mBytecount -= strlen(aTag);

				free(walker->mTag);
				
				if (last == NULL)
				{
					aD3->mTag = walker->mNext;
				}
				else
				{
					last->mNext = walker->mNext;
				}
				
				free(walker);

				return 0;
			}
		}

		last = walker;
		walker = walker->mNext;
	}
	return -1; // not found
}

int d3_set_tag(struct d3 *aD3, const char *aTag)
{
	struct d3tag *t;

	if (d3_is_tag(aD3, aTag))
		return -1; // already set
	if (aD3 == NULL || aTag == NULL)
		return -1;

	t = malloc(sizeof(struct d3tag));
	if (t == NULL)
		return -1;
	t->mHash = d3_hash(aTag);
	t->mTag = d3_strdup(aTag);
	t->mNext = aD3->mTag;
	aD3->mTag = t;
	aD3->mTagCount++;
	aD3->mBytecount += strlen(aTag);
	return 0;
}

int d3_deserialize(struct d3 *aD3, char *aBuffer)
{
	if (aD3 == NULL || aBuffer == NULL)
		return -1;
	if (d3_clear_all_tags(aD3))
		return -1;

	while (*aBuffer)
	{
		char *p;
		int i;
		i = 0;
		while (aBuffer[i] && aBuffer[i] != ',')
			i++;
		p = malloc(i+1);
		if (p == NULL)
			return -1;
		memcpy(p, aBuffer, i);
		p[i] = 0;
		aBuffer += i;
		if (d3_set_tag(aD3, p))
		{
			free(p);
			return -1;
		}
		free(p);
		if (*aBuffer == ',')
			aBuffer++;
	}
	return 0;
}

int d3_tag_count(struct d3 *aD3)
{
	if (aD3 == NULL)
		return 0;

	return aD3->mTagCount;
}

const char * d3_tag(struct d3 *aD3, int aTag)
{
	struct d3tag *walker;

	if (aD3 == NULL || aTag < 0 || aTag >= aD3->mTagCount)
		return NULL;

	walker = aD3->mTag;
	
	while (walker)
	{
		if (!aTag)
		{
			return walker->mTag;
		}

		aTag--;
		walker = walker->mNext;
	}
	return NULL; // shouldn't happen, but hey..
}

struct d3 * d3_init()
{
	struct d3 * d;
	d = (struct d3*)malloc(sizeof(struct d3));
	if (d == NULL)
		return NULL;
	memset(d,0,sizeof(struct d3));
	return d;
}


int d3_deinit(struct d3 *aD3)
{
	if (d3_clear_all_tags(aD3))
		return -1;

	free(aD3->mLang);

	free(aD3);
	
	return 0;
}

struct d3deck * d3_load_deck_xml(const char *aFilename)
{
	return NULL;
}

struct d3deck * d3_load_deck_json(const char *aFilename)
{
	return NULL;
}

static unsigned int readint(FILE * f)
{
	unsigned int d;
	fread(&d, sizeof(int), 1, f);
	// swap bytes here if needed
	return d;
}

void readstring(char ** aBuf, unsigned int * aBufsize, FILE * aF)
{
	unsigned int d;
	if (aBuf == NULL || 
		*aBuf == NULL ||
		aBufsize == NULL ||
		aF == NULL)
		return;
		
	d = readint(aF);
	if (d == 0)
	{
		*aBuf[0] = 0;
		return;
	}
	if (d > *aBufsize)
	{
		free(*aBuf);
		*aBufsize = d+1;
		*aBuf = (char*)malloc(*aBufsize);
		if (*aBuf == NULL)
			return;
	}
	fread(*aBuf, 1, d, aF);
	(*aBuf)[d] = 0;
}


struct d3deck * d3_load_deck_bin(const char *aFilename)
{
	FILE * f;
	char * buf;
	struct d3deck * d;
	unsigned int i, j, k, v, bufsize, cards, answers, languages;
//	fopen_s(&f, aFilename, "rw, ccs=encoding");
	f = fopen(aFilename, "rb");
	if (f == NULL)
		return NULL;

	v = readint(f);
	if (v != MAGIC)
	{		
		fclose(f);
		return NULL;
	}
	buf = (char *)malloc(4096);
	bufsize = 4096;
	if (buf == NULL)
	{
		fclose(f);
		return NULL;
	}

	readstring(&buf, &bufsize, f);

	// now we can start actually loading..
	d = malloc(sizeof(struct d3deck));
	if (d == NULL)
	{
		free(buf);
		fclose(f);
		return NULL;
	}
	memset(d, 0, sizeof(struct d3deck));
	d->mID = d3_strdup(buf);
	d->mUserData = 0;	

	readstring(&buf, &bufsize, f);
	d->mUserData = d3_strdup(buf);

	cards = readint(f);
	d->mCards = cards;
	d->mCard = malloc(sizeof(struct d3card) * cards);
	if (d->mCard == NULL)
	{
		free(buf);
		free(d);
		fclose(f);
		return NULL;
	}
	memset(d->mCard, 0, sizeof(struct d3card) * cards);
	for (i = 0; i < cards; i++)
	{
		struct d3card *c = d->mCard + i;
		
		readstring(&buf, &bufsize, f);
		c->mID = d3_strdup(buf);
		readstring(&buf, &bufsize, f);
		c->mSet = d3_strdup(buf);
		readstring(&buf, &bufsize, f);
		c->mClear = d3_strdup(buf);
		readstring(&buf, &bufsize, f);
		c->mUserData = d3_strdup(buf);
		languages = readint(f);
		c->mQuestion.mLanguageID = malloc(sizeof(char*) * languages);		
		c->mQuestion.mString = malloc(sizeof(char*) * languages);
		if (c->mQuestion.mLanguageID == NULL ||
			c->mQuestion.mString == NULL)
		{
			free(c->mQuestion.mLanguageID);
			free(c->mQuestion.mString);
			d3_free_deck(d);
			fclose(f);
			return NULL;
		}
		c->mQuestion.mLanguages = languages;

		for (j = 0; j < languages; j++)
		{
			readstring(&buf, &bufsize, f); // lang id
			c->mQuestion.mLanguageID[j] = d3_strdup(buf);

			readstring(&buf, &bufsize, f); // string
			c->mQuestion.mString[j] = d3_strdup(buf);
		}
		answers = readint(f);
		c->mAnswer = malloc(sizeof(struct d3answer) * answers);
		if (c->mAnswer == NULL)
		{
			d3_free_deck(d);
			fclose(f);
			return NULL;
		}
		c->mAnswers = answers;
		for (j = 0; j < answers; j++)
		{
			struct d3answer * answer = c->mAnswer + j;
			readstring(&buf, &bufsize, f);
			answer->mTarget = d3_strdup(buf);
			readstring(&buf, &bufsize, f);
			answer->mTags_need = d3_strdup(buf);
			readstring(&buf, &bufsize, f);
			answer->mTags_not = d3_strdup(buf);
			readstring(&buf, &bufsize, f);
			answer->mUserData = d3_strdup(buf);
			languages = readint(f);
			answer->mAnswer.mLanguageID = malloc(sizeof(char*) * languages);
			answer->mAnswer.mString = malloc(sizeof(char*) * languages);
			if (answer->mAnswer.mLanguageID == NULL ||
				answer->mAnswer.mString == NULL)
			{
				free(answer->mAnswer.mLanguageID);
				free(answer->mAnswer.mString);
				d3_free_deck(d);
				fclose(f);
				return NULL;
			}
			answer->mAnswer.mLanguages = languages;

			for (k = 0; k < languages; k++)
			{
				readstring(&buf, &bufsize, f); // lang id
				answer->mAnswer.mLanguageID[k] = d3_strdup(buf);
				readstring(&buf, &bufsize, f); // string
				answer->mAnswer.mString[k] = d3_strdup(buf);
			}
		}	
	}
	if (buf == NULL)
	{
		d3_free_deck(d);
		fclose(f);
		return NULL;
	}
	free(buf);
	fclose(f);
	return d;
}


int d3_free_deck(struct d3deck *aDeck)
{
	int i, j, k;

	if (aDeck == NULL)
		return 0;

	for (i = 0; i < aDeck->mCards; i++)
	{
		free(aDeck->mCard[i].mID);
		for (j = 0; j < aDeck->mCard[i].mQuestion.mLanguages; j++)
		{
			free(aDeck->mCard[i].mQuestion.mLanguageID[j]);
			free(aDeck->mCard[i].mQuestion.mString[j]);
		}
		free(aDeck->mCard[i].mQuestion.mLanguageID);
		free(aDeck->mCard[i].mQuestion.mString);
		for (j = 0; j < aDeck->mCard[i].mAnswers; j++)
		{
			for (k = 0; k < aDeck->mCard[i].mAnswer[j].mAnswer.mLanguages; k++)
			{
				free(aDeck->mCard[i].mAnswer[j].mAnswer.mLanguageID[k]);
				free(aDeck->mCard[i].mAnswer[j].mAnswer.mString[k]);
			}
			free(aDeck->mCard[i].mAnswer[j].mAnswer.mLanguageID);
			free(aDeck->mCard[i].mAnswer[j].mAnswer.mString);
			free(aDeck->mCard[i].mAnswer[j].mTags_need);
			free(aDeck->mCard[i].mAnswer[j].mTags_not);
			free(aDeck->mCard[i].mAnswer[j].mTarget);
			free(aDeck->mCard[i].mAnswer[j].mUserData);
		}
		free(aDeck->mCard[i].mAnswer);
		free(aDeck->mCard[i].mSet);
		free(aDeck->mCard[i].mClear);
		free(aDeck->mCard[i].mUserData);
	}
	free(aDeck->mCard);
	free(aDeck->mID);
	free(aDeck->mUserData);
	free(aDeck);
	return 0;
}


int d3_use_deck(struct d3 *aD3, struct d3deck *aDeck, const char *aCardID)
{
	if (aD3 == NULL)
	{
		return -1;
	}

	aD3->mCurrentDeck = aDeck;

	if (aDeck == NULL)
	{
		return 0;
	}	

	d3_goto(aD3, aCardID);
	
	return 0;
}


const char *d3_get_deck_id(struct d3 *aD3)
{
	if (aD3 == NULL)
		return NULL;

	return aD3->mCurrentDeck->mID;
}

const char *d3_get_deck_user_data(struct d3 *aD3)
{
	if (aD3 == NULL)
		return NULL;

	return aD3->mCurrentDeck->mUserData;
}


const char * d3_get_question(struct d3 *aD3)
{
	int i;
	if (aD3 == NULL ||
		aD3->mCurrentDeck == NULL ||
		aD3->mCurrentCard == NULL ||
		aD3->mCurrentCard->mQuestion.mLanguages == 0)
		return NULL;

	if (aD3->mCurrentCard->mQuestion.mLanguages == 1 || aD3->mLang == NULL)
		return aD3->mCurrentCard->mQuestion.mString[0];

	for (i = 0; i < aD3->mCurrentCard->mQuestion.mLanguages; i++)
	{
		if (d3_strcasecmp(aD3->mLang, aD3->mCurrentCard->mQuestion.mLanguageID[i]) == 0)
			return aD3->mCurrentCard->mQuestion.mString[i];
	}

	return aD3->mCurrentCard->mQuestion.mString[0]; 
}

const char * d3_get_card_user_data(struct d3 *aD3)
{
	if (aD3 == NULL || 
		aD3->mCurrentDeck == NULL ||
		aD3->mCurrentCard == NULL)
		return NULL;

	return aD3->mCurrentCard->mUserData;
}

const char * d3_get_card_id(struct d3 *aD3)
{
	if (aD3 == NULL || 
		aD3->mCurrentDeck == NULL ||
		aD3->mCurrentCard == NULL)
		return NULL;

	return aD3->mCurrentCard->mID;
}


int d3_goto(struct d3 *aD3, const char *aCardID)
{
	int i;
	char tagbuf[MAX_TAG_LENGTH];
	char *tok;
	
	// find card
	
	struct d3card *c = NULL;
	if (aD3 == NULL ||
		aD3->mCurrentDeck == NULL)
		return -1;
	if (aD3->mCurrentDeck->mCards == 0)
		return -1;
	if (aCardID == NULL ||
		*aCardID == 0)
	{
		c = &(aD3->mCurrentDeck->mCard[0]);
	}
	else
	{
		for (i = 0; c == NULL && i < aD3->mCurrentDeck->mCards; i++)
		{
			if (d3_strcasecmp(aCardID, aD3->mCurrentDeck->mCard[i].mID) == 0)
			{
				c = &(aD3->mCurrentDeck->mCard[i]);
			}
		}
	}
	if (c == NULL)
		return -1;
	
	aD3->mCurrentCard = c;
	
	// set / clear tags

	tok = c->mSet;
	while (tok)
	{
		tok = d3_tokenize(tagbuf, tok);
		if (tok)
		{
			d3_set_tag(aD3, tagbuf);
		}
	}

	tok = c->mClear;
	while (tok)
	{
		tok = d3_tokenize(tagbuf, tok);
		if (tok)
		{
			d3_clear_tag(aD3, tagbuf);
		}
	}

	aD3->mCurrentAnswerCount = 0;

	// validate answers
	for (i = 0; i < c->mAnswers; i++)
	{
		// check tags

		c->mAnswer[i].mValid = 1;

		tok = c->mAnswer[i].mTags_need;
		while (tok)
		{
			tok = d3_tokenize(tagbuf, tok);
			if (tok)
			{
				if (d3_is_tag(aD3, tagbuf) == 0)
					c->mAnswer[i].mValid = 0;
			}
		}

		tok = c->mAnswer[i].mTags_not;
		while (tok)
		{
			tok = d3_tokenize(tagbuf, tok);
			if (tok)
			{
				if (d3_is_tag(aD3, tagbuf) != 0)
					c->mAnswer[i].mValid = 0;
			}
		}

		if (c->mAnswer[i].mValid)
			aD3->mCurrentAnswerCount++;
	}
	return 0;
}


int d3_get_answer_count(struct d3 *aD3)
{
	if (aD3 == NULL ||
		aD3->mCurrentDeck == NULL ||
		aD3->mCurrentCard == NULL)
	{
		return 0;
	}

	return aD3->mCurrentAnswerCount;
}

const char *d3_get_answer(struct d3 *aD3, int aAnswer)
{
	int i;
	if (aD3 == NULL ||
		aD3->mCurrentDeck == NULL ||
		aD3->mCurrentCard == NULL)
	{
		return 0;
	}

	for (i = 0; i < aD3->mCurrentCard->mAnswers; i++)
	{
		if (aD3->mCurrentCard->mAnswer[i].mValid)
		{
			if (aAnswer == 0)
			{
				if (aD3->mCurrentCard->mAnswer[i].mAnswer.mLanguages == 0)
					return NULL;
				if (aD3->mCurrentCard->mAnswer[i].mAnswer.mLanguages == 1 || aD3->mLang == NULL)
					return aD3->mCurrentCard->mAnswer[i].mAnswer.mString[0];

				for (i = 0; i < aD3->mCurrentCard->mAnswer[i].mAnswer.mLanguages; i++)
				{
					if (d3_strcasecmp(aD3->mLang, aD3->mCurrentCard->mAnswer[i].mAnswer.mLanguageID[i]) == 0)
						return aD3->mCurrentCard->mAnswer[i].mAnswer.mString[i];
				}

				return aD3->mCurrentCard->mAnswer[i].mAnswer.mString[0]; 
			}
			aAnswer--;
		}
	}

	return NULL;
}

const char *d3_get_answer_user_data(struct d3 *aD3, int aAnswer)
{
	int i;
	if (aD3 == NULL ||
		aD3->mCurrentDeck == NULL ||
		aD3->mCurrentCard == NULL)
	{
		return 0;
	}

	for (i = 0; i < aD3->mCurrentCard->mAnswers; i++)
	{
		if (aD3->mCurrentCard->mAnswer[i].mValid)
		{
			if (aAnswer == 0)
				return aD3->mCurrentCard->mAnswer[i].mUserData;
			aAnswer--;
		}
	}

	return NULL;
}

int d3_choose(struct d3 *aD3, int aAnswer)
{
	int i;
	char tagbuf[MAX_TAG_LENGTH];
	char *tok;

	if (aD3 == NULL ||
		aD3->mCurrentDeck == NULL ||
		aD3->mCurrentCard == NULL)
	{
		return 0;
	}

	for (i = 0; i < aD3->mCurrentCard->mAnswers; i++)
	{
		if (aD3->mCurrentCard->mAnswer[i].mValid)
		{
			if (aAnswer == 0)
			{
				// If answer's not-list starts with a +, we have an autotag we need to enable
				if (aD3->mCurrentCard->mAnswer[i].mTags_not != NULL)
				{
					tok = aD3->mCurrentCard->mAnswer[i].mTags_not;
					while (tok)
					{
						tok = d3_tokenize(tagbuf, tok);
						if (tok)
						{
							if (tagbuf[0] == '+')
								d3_set_tag(aD3, tagbuf);
						}
					}

				}

				d3_goto(aD3, aD3->mCurrentCard->mAnswer[i].mTarget);
				return 0;
			}
			aAnswer--;
		}
	}

	return -1;
}


/////////////////////////////////////////////////////////////////////
// Some testing


/*
// tokenizer test
int main(int parc, char ** pars)
{
	char buf[256];
	char *testdata = " hello, world, oh you   ,, test test blahblah bölll   ";
	char * ptr = testdata;

	while (ptr)
	{
		ptr = d3_tokenize(buf, ptr);
		if (ptr)
			printf("\"%s\"\n", buf);
	}

	return 0;
}
*/

/*
// tag system test
int main(int parc, char **pars)
{
	struct d3 *d;
	int i;
	char temp[1024];
	temp[0] = 0;
	d = d3_init();
	printf("d3 init %08x\n", d);
	printf("Tag count: %d\n", d3_tag_count(d));
	printf("Is tag: %d\n", d3_is_tag(d, "foo"));
	printf("Delete tag: %d\n", d3_clear_tag(d, "foo"));
	printf("Tag count: %d\n", d3_tag_count(d));

	printf("Serialize estimate: %d\n", d3_serialize_estimate(d));
	printf("Serialize: %d\n", d3_serialize(d, temp, NULL, 1024));
	printf("Serialized data: \"%s\"\n", temp);
	printf("Deserialize: %d\n", d3_deserialize(d, temp));

	printf("Add tag: %d\n", d3_set_tag(d, "foo"));
	printf("Tag count: %d\n", d3_tag_count(d));
	printf("Add tag: %d\n", d3_set_tag(d, "foo"));
	printf("Tag count: %d\n", d3_tag_count(d));
	printf("Is tag: %d\n", d3_is_tag(d, "foo"));
	for (i = -3; i < 3; i++)
	{
		const char * t = d3_tag(d, i);
		printf("tag %d: '%s'\n", i, t?t:"NULL");
	}
	printf("Is tag: %d\n", d3_is_tag(d, "foo"));

	printf("Serialize estimate: %d\n", d3_serialize_estimate(d));
	printf("Serialize: %d\n", d3_serialize(d, temp, NULL, 1024));
	printf("Serialized data: \"%s\"\n", temp);
	printf("Deserialize: %d\n", d3_deserialize(d, temp));

	printf("Delete tag: %d\n", d3_clear_tag(d, "foo"));
	printf("Is tag: %d\n", d3_is_tag(d, "foo"));
	printf("Tag count: %d\n", d3_tag_count(d));

	printf("Serialize estimate: %d\n", d3_serialize_estimate(d));
	printf("Serialize: %d\n", d3_serialize(d, temp, NULL, 1024));
	printf("Serialized data: \"%s\"\n", temp);
	printf("Deserialize: %d\n", d3_deserialize(d, temp));

	printf("Add tag: %d\n", d3_set_tag(d, "foo"));
	printf("Tag count: %d\n", d3_tag_count(d));
	printf("Add tag: %d\n", d3_set_tag(d, "bar"));
	printf("Tag count: %d\n", d3_tag_count(d));
	printf("Add tag: %d\n", d3_set_tag(d, "baz"));
	printf("Tag count: %d\n", d3_tag_count(d));

	for (i = -1; i < 4; i++)
	{
		const char * t = d3_tag(d, i);
		printf("tag %d: '%s'\n", i, t?t:"NULL");
	}

	printf("Serialize estimate: %d\n", d3_serialize_estimate(d));
	printf("Serialize: %d\n", d3_serialize(d, temp, NULL, 1024));
	printf("Serialized data: \"%s\"\n", temp);
	printf("Deserialize: %d\n", d3_deserialize(d, temp));

	printf("Is tag: %d\n", d3_is_tag(d, "foo"));
	printf("Is tag: %d\n", d3_is_tag(d, "bar"));
	printf("Is tag: %d\n", d3_is_tag(d, "baz"));

	printf("Delete tag: %d\n", d3_clear_tag(d, "foo"));
	for (i = -1; i < 4; i++)
	{
		const char * t = d3_tag(d, i);
		printf("tag %d: '%s'\n", i, t?t:"NULL");
	}
	printf("Delete tag: %d\n", d3_clear_tag(d, "baz"));
	for (i = -1; i < 4; i++)
	{
		const char * t = d3_tag(d, i);
		printf("tag %d: '%s'\n", i, t?t:"NULL");
	}
	printf("Add tag: %d\n", d3_set_tag(d, "foo"));
	printf("Tag count: %d\n", d3_tag_count(d));
	printf("Add tag: %d\n", d3_set_tag(d, "baz"));
	printf("Tag count: %d\n", d3_tag_count(d));
	for (i = -1; i < 4; i++)
	{
		const char * t = d3_tag(d, i);
		printf("tag %d: '%s'\n", i, t?t:"NULL");
	}
	printf("Delete tag: %d\n", d3_clear_tag(d, "foo"));
	for (i = -1; i < 4; i++)
	{
		const char * t = d3_tag(d, i);
		printf("tag %d: '%s'\n", i, t?t:"NULL");
	}

	printf("Serialize estimate: %d\n", d3_serialize_estimate(d));
	printf("Serialize: %d\n", d3_serialize(d, temp, NULL, 1024));
	printf("Serialized data: \"%s\"\n", temp);
	printf("Deserialize: %d\n", d3_deserialize(d, temp));

	printf("deinit: %d\n",d3_deinit(d));
	return 0;
}
*/