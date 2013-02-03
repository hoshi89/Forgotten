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

#ifndef D3_H
#define D3_H
#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
#if defined(D3_DLL)
#define D3DECL __declspec(dllexport) 
#elif defined(D3_USE_DLL)
#define D3DECL __declspec(dllimport)
#else
#define D3DECL
#endif
#else
#define D3DECL
#endif

struct d3;
struct d3deck;

D3DECL struct d3 * d3_init();
D3DECL int d3_deinit(struct d3 *aD3);
D3DECL int d3_set_language(struct d3 *aD3, const char *aLanguage);

D3DECL int d3_serialize_estimate(struct d3 *aD3);
D3DECL int d3_serialize(struct d3 *aD3, char *aBuffer, int *aBytesUsed, int aBufferSize);
D3DECL int d3_deserialize(struct d3 *aD3, char *aBuffer);

D3DECL int d3_set_tag(struct d3 *aD3, const char *aTag);
D3DECL int d3_clear_tag(struct d3 *aD3, const char *aTag);
D3DECL int d3_is_tag(struct d3 *aD3, const char *aTag);
D3DECL int d3_clear_all_tags(struct d3 *aD3);
D3DECL int d3_tag_count(struct d3 *aD3);
D3DECL const char * d3_tag(struct d3 *aD3, int aTag);
 
D3DECL struct d3deck * d3_load_deck_xml(const char *aFilename);
D3DECL struct d3deck * d3_load_deck_json(const char *aFilename);
D3DECL struct d3deck * d3_load_deck_bin(const char *aFilename);

D3DECL int d3_free_deck(struct d3deck *aDeck);

D3DECL int d3_use_deck(struct d3 *aD3, struct d3deck *aDeck, const char *aCardID);

D3DECL const char *d3_get_deck_id(struct d3 *aD3);
D3DECL const char *d3_get_deck_user_data(struct d3 *aD3);

D3DECL const char * d3_get_question(struct d3 *aD3);
D3DECL const char * d3_get_card_user_data(struct d3 *aD3);
D3DECL const char * d3_get_card_id(struct d3 *aD3);

D3DECL int d3_goto(struct d3 *aD3, const char *aCardID);

D3DECL int d3_get_answer_count(struct d3 *aD3);
D3DECL const char *d3_get_answer(struct d3 *aD3, int aAnswer);
D3DECL const char *d3_get_answer_user_data(struct d3 *aD3, int aAnswer);
D3DECL int d3_choose(struct d3 *aD3, int aAnswer);

#ifdef __cplusplus
}
#endif
#endif