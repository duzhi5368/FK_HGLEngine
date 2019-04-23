#include<hgl/graph/FontSource.h>
#include<string.h>

namespace hgl
{
	namespace graph
	{
		FontSource::FontSource(const Font &f)
		{
			fnt=f;

			memset(char_bitmap,0,sizeof(char_bitmap));
		}

		FontSource::~FontSource()
		{
			for(int i=0;i<0xffff;i++)
				delete[] char_bitmap[i].data;		//delete[] NULL;���Ǵ������Բ��õ���
		}
		
		FontSource::Bitmap *FontSource::GetCharBitmap(wchar_t ch)
		{
			if(!this)
				return(NULL);

			if(ch==0
			 ||ch==L' '		//��ǿո�
			 ||ch==L'��'	//ȫ�ǿո�
			 ||ch==L'\n'
			 ||ch==L'\r'
			 ||ch==L'\t')return(NULL);	//������ʾ�����ݻ��ǿո�

			if(!char_bitmap[ch].data)
			{
				if(char_bitmap[ch].h==-1)
					return(NULL);

				if(!MakeCharBitmap(ch))
				{
					char_bitmap[ch].h=-1;		//���Ϊ-1�Ա�֤δ��Ҳ��ȡ��
					return(NULL);
				}
			}

			return char_bitmap+ch;
		}
	}//namespace graph
}//namespace hgl
