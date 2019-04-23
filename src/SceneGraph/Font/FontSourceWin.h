#ifndef HGL_GRAPH_FONT_SOURCE_WINDOWS_INCLUDE
#define HGL_GRAPH_FONT_SOURCE_WINDOWS_INCLUDE

#include<hgl/graph/FontSource.h>
#include<hgl/MemBlock.h>
#include<windows.h>
namespace hgl
{
	namespace graph
	{
		class WinBitmapFont:public FontSource
		{
    		HDC hdc;
			HFONT hfont;    		
			
			GLYPHMETRICS gm;
			MAT2 mat;

			unsigned int ggo;

			MemBlock<unsigned char> buffer;

		protected:

			int LineHeight;
			int LineDistance;

		public:

			WinBitmapFont(const Font &);
			~WinBitmapFont();

			bool MakeCharBitmap(wchar_t);					///<������������
			int GetLineHeight()const{return LineHeight;}	///<ȡ���и�
		};//class WinBitmapFont
	}//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_FONT_SOURCE_WINDOWS_INCLUDE
