#include<hgl/graph/TileFont.H>
#include<hgl/graph/Font.H>
#include<hgl/graph/Render.H>
#include<hgl/type/IndexData.H>
#include"FontSourceWin.H"

namespace hgl
{
	namespace graph
	{
		class FontSourceStorage:public IndexObject<Font,FontSource>
		{
			FontSource *CreateObject(const Font &fnt)
			{
				return(new WinBitmapFont(fnt));
			}

			void DeleteObject(const Font &,FontSource *source)
			{
				if(source)
					delete source;
			}

		public:
		};//class FontSourceStorage

		static FontSourceStorage FontStorage;

		void InitFontStorage()
		{
		}

		void ClearFontStorage()
		{
			FontStorage.Clear();
		}

		FontSource *GetFontSource(const Font &fnt)
		{
			FontSource *source;

			if(FontStorage.Get(fnt,source))
				return(source);
			
			source=new WinBitmapFont(fnt);

			FontStorage.Add(fnt,source);
			return(source);
		}

		/**
		* ͨ��ϵͳ���崴��һ��Tile����,�����С�Խϴ��Ϊ׼
		* @param chs_fnt Ӣ������
		* @param eng_fnt ��������
		* @param count �������ڱ�����ַ�����,-1��ʾ�Զ�ȡ(�������Ļ��Сȡ���ֵ)
		*/
		TileFont *CreateTileFont(const Font &chs_fnt,const Font &eng_fnt,int count)
		{
			int font_height;
			int height;

			if(chs_fnt.height>eng_fnt.height)
				height=chs_fnt.height;
			else
				height=eng_fnt.height;

			font_height=height;

			if(chs_fnt.bold		||eng_fnt.bold
			 ||chs_fnt.italic	||eng_fnt.italic)height+=height/4;

			height+=3;
			height-=height&3;						//��С�����ܱ�4����

//			if(height<16)
//				height=16;

			if(count==-1)							//�Զ�,����Ļ�����ּ���
			{
				int sw,sh;

				GetScreenSize(sw,sh);

				count=((sw+height-1)/height)
					 *((sh+height-1)/height);
			}

			TileData *td=new TileData(height,height,count,HGL_R8);

			FontSource *cfs=GetFontSource(chs_fnt);
			FontSource *efs=GetFontSource(eng_fnt);

			return(new TileFont(font_height,td,cfs,efs));
		}

		/**
		* ͨ��ϵͳ���崴��һ��Tile����
		* @param chs_fontname ������������
		* @param eng_fontname Ӣ����������
		* @param width ��,����Ϊ0,��ʾĬ�ϡ�
		* @param height ��
		* @param bold �Ӵ�,Ĭ��false
		* @param italic б��,Ĭ��false
		* @param count �������ڱ�����ַ�����
		*/
		TileFont *CreateTileFont(const wchar_t *chs_fontname,const wchar_t *eng_fontname,int width,int height,bool bold,bool italic,int count)
		{
			Font chs_fnt(chs_fontname,width,height,bold,italic);
			Font eng_fnt(eng_fontname,width,height,bold,italic);

			return CreateTileFont(chs_fnt,eng_fnt,count);
		}
	}//namespace graph
}//namespace hgl
