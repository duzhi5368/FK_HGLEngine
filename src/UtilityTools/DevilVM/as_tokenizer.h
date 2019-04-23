/*
   AngelCode Scripting Library
   Copyright (c) 2003-2007 Andreas Jonsson

   This software is provided 'as-is', without any express or implied
   warranty. In no event will the authors be held liable for any
   damages arising from the use of this software.

   Permission is granted to anyone to use this software for any
   purpose, including commercial applications, and to alter it and
   redistribute it freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you
      must not claim that you wrote the original software. If you use
      this software in a product, an acknowledgment in the product
      documentation would be appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and
      must not be misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
      distribution.

   The original version of this library can be located at:
   http://www.angelcode.com/angelscript/

   Andreas Jonsson
   andreas@angelcode.com
*/


//
// as_tokenizer.cpp
//
// This class identifies tokens from the script code
//



#ifndef AS_TOKENIZER_H
#define AS_TOKENIZER_H

#include <hgl/type/DataType.h>
#include "as_tokendef.h"

using namespace hgl;

namespace angle_script
{
	const u16char *asGetTokenDefinition(int tokenType);

	const u16char *GetTokenName(eTokenType);

	class asCTokenizer
	{
	public:

		asCTokenizer();
		~asCTokenizer();

		eTokenType GetToken(const u16char *source, hgl::uint sourceLength, hgl::uint *tokenLength);

	protected:

		int  ParseToken();
		bool IsWhiteSpace();
		bool IsComment();
		bool IsConstant();
		bool IsKeyWord();
		bool IsIdentifier();

		const u16char *source;
		hgl::uint sourceLength;

		eTokenType tokenType;
		hgl::uint tokenLength;
	};//class asCTokenizer
}//namespace angle_script
#endif//#ifndef AS_TOKENIZER_H
