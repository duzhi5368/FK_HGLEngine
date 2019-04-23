#include<hgl/graph/TileFont.H>
#include<hgl/graph/Render.H>
#include<hgl/graph/Material.H>
#include<hgl/graph/Renderable.H>
#include<stdarg.h>

namespace hgl
{
	namespace graph
	{
		TileFont::TileFont(int fh,TileData *td,FontSource *cfs,FontSource *efs):fud(td->GetMaxCount())
		{
			font_height=fh;
			line_distance=font_height*0.15;

			tile_data=td;

			chs_source=cfs;
			eng_source=efs;

			if(!efs)
				eng_source=cfs;

			if(!cfs)
				chs_source=efs;

			const int max_count=td->GetMaxCount();

			vertex2d=new VB2f(6*max_count,0,HGL_DYNAMIC_DRAW);
			tex_coord=new VB2f(6*max_count,0,HGL_DYNAMIC_DRAW);

			fnt_mtl=CreateMaterial();

			fnt_mtl->SetColorMaterial(true);
			fnt_mtl->SetColor(1,1,1,1);

			fnt_draw=CreateRenderable();
			fnt_draw->SetPrimitive(HGL_PRIM_TRIANGLES);
			fnt_draw->SetMaterial(fnt_mtl,true);

			fnt_mtl->SetTexture(mtcAlpha,tile_data->GetTexture());

			fnt_mtl->SetBlend(true);
			fnt_mtl->SetBlend(HGL_BLEND_SRC_ALPHA,HGL_BLEND_ONE_MINUS_SRC_ALPHA);

			fnt_mtl->SetDepthMask(false);
			fnt_mtl->SetDepthTest(false);

			fnt_mtl->SetLight(false);

			fnt_draw->SetVertex(vertex2d);
			fnt_draw->SetTexCoord(mtcAlpha,vbtAlphaTexCoord,tex_coord);

			fnt_draw->AutoCreateShader(true
#ifdef _DEBUG
				,L"TileFont"
#endif//_DEBUG
				);

			tile_width=td->GetWidth();
			tile_height=td->GetHeight();

			char_bitmap_bytes=tile_width*tile_height;
			char_bitmap_buffer=new uint8[char_bitmap_bytes];
		}

		TileFont::~TileFont()
		{
			//FontSource�����ͷ�

			delete[] char_bitmap_buffer;
			delete fnt_draw;

			delete tile_data;
		}

		FontSource::Bitmap *TileFont::MakeCharBitmap(const wchar_t &ch)
		{
			FontSource::Bitmap *bmp=GetCharBitmap(ch);

			if(!bmp)
				return(false);

			memset(char_bitmap_buffer,0,char_bitmap_bytes);

			int copy_rows=(bmp->h>tile_height?tile_height:bmp->h);
			int copy_cols=(bmp->w>tile_width?tile_width:bmp->w);

			uint8 *sp=bmp->data;
			uint8 *tp=char_bitmap_buffer;

			for(int row=0;row<copy_rows;row++)
			{
				memcpy(tp,sp,copy_cols);

				tp+=tile_width;
				sp+=bmp->w;
			}

			return(bmp);
		}

		TileData::Object *TileFont::GetCharData(const wchar_t &ch)
		{
			FudItem<wchar_t,TileData::Object *> *obj;

			TileData::Object *tile;

			if(fud.Find(ch,tile,true))		//���Ҳ��Զ��Ƶ���ǰ
				return(tile);

			FontSource::Bitmap *bmp=MakeCharBitmap(ch);

			if(!bmp)
				return(NULL);

			if(fud.GetFreeCount())			//��ʣ��ռ�
			{
				tile=tile_data->Add(char_bitmap_buffer,char_bitmap_bytes,HGL_SF_R8,bmp->w,bmp->h);

				obj=fud.Add(ch,tile);
			}
			else
			{
				obj=fud.GetEnd();

				obj->flag=ch;

				tile_data->Change(obj->data,char_bitmap_buffer,char_bitmap_bytes,HGL_SF_R8,bmp->w,bmp->h);
			}

			return(obj->data);
		}

		/**
		* ���ַ����
		* @param ch �ַ�
		* @return �ַ������ؼ����
		*/
		float TileFont::CharWidth(wchar_t ch)
		{
			if(ch==0)return(0);

			const FontSource::Bitmap *bmp=GetCharBitmap(ch);

			return bmp?bmp->adv_x:0;
		}

		/**
		* ���ַ������
		* @param str �ַ���
		* @param limit ���Ƶ��ַ���
		* @return �ַ��������ؼ����
		*/
		float TileFont::GetStringWidth(const wchar_t *str,int limit)
		{
			if(!str||!(*str)||limit==0)return(0);

			const wchar_t *p=str;
			int w=0;

			while(*p&&limit--)
			{
				const FontSource::Bitmap *bmp=GetCharBitmap(*p++);

				if(bmp)
					w+=bmp->adv_x;
				else
				{
					if(*p==L'\t')w+=font_height*2;else
					if(*p>0xFF	)w+=font_height;else
								 w+=font_height/2;
				}
			}

			return(w);
		}

		/**
		* �Ű��ַ���(���Զ�����,��\n����)
		* @param makeup �Ű�����
		* @param x ��ʼX����
		* @param y ��ʼY����
		* @param str �ַ���
		* @param limit ������ַ�����
		*/
		bool TileFont::MakeupText(Makeup &makeup,int x,int y,const wchar_t *str,int limit)
		{
			if(!str||!(*str)||limit==0)return(false);

			double w;
			Makeup::CharMakeup cm;

			while(*str&&limit--)
			{
				const FontSource::Bitmap *bmp=GetCharBitmap(*str);

				if(bmp)
				{
					w=bmp->adv_x;

					cm.left	=bmp->x;
					cm.top	=bmp->y;
				}
				else
				{
					if(*str==L'\t')w=font_height*2;else
					if(*str==L'\r')w=0;else
					if(*str>0xFF  )w=font_height;else
								   w=font_height/2;

					cm.left	=0;
					cm.top	=0;
				}

				cm.scope.Set(x,y,w,font_height);
				cm.ch=*str;

				x+=w;

				makeup+=cm;

				str++;
			}

			return(true);
		}

		/**
		* �Ű��ַ���(���Զ�����,����\nΪ����)
		* @param makeup ��¼�Ű���Ϣ�����ݽṹ
		* @param str Ҫ�Ű���ַ���
		* @param limit �ַ�����,-1��ʾ�浽����Ϊֹ
		*/
		bool TileFont::MakeupText(Makeup &makeup,const wchar_t *str,int limit)
		{
			if(!str||!(*str)||limit==0)return(false);

			makeup.Clear();

			const wchar_t *p=str;
			int x=0,y=0,w;
			int max_w=0,max_h=0;
			Makeup::CharMakeup cm;

			while(*p&&limit)
			{
				if(*p==L'\n')
				{
					cm.scope.Set(x,y,0,0);

					if(x>max_w)
						max_w=x;

					x=0;
					y+=font_height+line_distance;

					if(y>max_h)
                		max_h=y;
				}
				else
				if(*p==L'\t')
				{
					cm.scope.Set(x,y,font_height*2,font_height);

					x+=font_height*2;	//4�ָ���
				}
				else
				{
					const FontSource::Bitmap *bmp=GetCharBitmap(*p);

					if(bmp)
					{
						w=bmp->adv_x;

						cm.scope.Set(x,y,w,font_height);
						cm.left	=bmp->x;
						cm.top	=bmp->y;
					}
					else
					{
						if(*p<0xFF)
							w=font_height/2;
						else
							w=font_height;

						cm.scope.Set(x,y,w,0);
					}

					x+=w;
				}

				cm.ch=*p;
				makeup+=cm;

				p++;
				limit--;
			}

			if(x>max_w)
        		max_w=x;

			if(max_h)
			{
				if(x==0)					//���һ���ǿյ�
					max_h-=line_distance;
				else						//���ǿյ�
            		max_h+=font_height;
			}
			else	//ֻ��һ��
			{
				max_h=font_height;
			}

			makeup.Width =max_w;
			makeup.Height=max_h;

			makeup.ProcEnd(font_height/2);

			return(true);
		}

		const wchar_t 	BeginSymbol[]=	L"!),.:;?]}���������D���������á����������������������9�8�9�0�������������������ݣ��������";
		const wchar_t 	EndSymbol[]=	L"([{���������������������9�7�9�9�����ۣ��꣤";

		const int 		BeginSymbolCount=sizeof(BeginSymbol)/sizeof(wchar_t);
		const int 		EndSymbolCount	=sizeof(EndSymbol)/sizeof(wchar_t);

		/**
		* �Ű��ַ���(���Զ�����,�Զ�����������β��㣻\n����Ϊǿ�ƻ��У���������)
		* @param makeup ��¼�Ű���Ϣ�����ݽṹ
		* @param str Ҫ�Ű���ַ���
		* @param max_width �����
		* @param align ���뷽ʽ
		*/
		bool TileFont::MakeupText(Makeup &makeup,const wchar_t *str,int max_width,TextAlignment align)
		{
			if(!str||!(*str)||max_width<=font_height||align<=taNone||align>=taEnd)return(false);

			makeup.Clear();
			makeup.Width=max_width;

			const wchar_t *p,*sp;
			int row=0,w=0,tw=0,pos;
			Makeup::CharMakeup cm;

			p=sp=str;
			while(*p)
			{
				if(*p==L'\n')		//ǿ�ƻ���
				{
					if(align==taCenter	)pos=(max_width-tw)/2;else
					if(align==taRight	)pos=max_width-tw;else pos=0;

					MakeupText(makeup,pos,row,sp,p-sp);

					cm.scope.Width=0;
					cm.scope.Height=0;
					cm.ch=*p;

					makeup+=cm;	//�յ�ҲҪ��

					tw=0;
					row+=font_height+line_distance;

					p++;
					sp=p;
				}
				else
				{
					const FontSource::Bitmap *bmp=GetCharBitmap(*p);

					if(bmp)
					{
						w=bmp->adv_x;
					}
					else
					{
						if(*p==L'\t')w=font_height*2;else
						if(*p==L'\r')w=0;else
						if(*p>0xFF  )w=font_height;else
									 w=font_height/2;
					}

					if(tw+w>max_width)		//����
					{
						while(p>sp)
						{
							bool result=false;

							if(strchr(EndSymbol,	*(p-1),	EndSymbolCount	))result=true;		//���ҵ�ǰ�ַ��Ƿ��������β���÷���
							if(strchr(BeginSymbol,	*p,		BeginSymbolCount))result=true;		//���ҵ�ǰ�ַ��Ƿ���������׽��÷���

							if(result)								//����������β���֣����ǻ���ǰ��һ���ַ�
							{
								const FontSource::Bitmap *prev_bmp=GetCharBitmap(*(p-1));

								tw-=prev_bmp->adv_x;				//ɾ���ַ����
								p--;								//pǰ��

								continue;
							}

							break;									//��û�в鵽���˳�����
						}

						if(align==taCenter	)pos=(max_width-tw)/2;else
						if(align==taRight	)pos=max_width-tw;else pos=0;

						MakeupText(makeup,pos,row,sp,p-sp);

						tw=0;
						row+=font_height+line_distance;

						sp=p;
					}
					else
					{
						tw+=w;

						p++;
					}
				}
			}

			if(align==taCenter	)pos=(max_width-tw)/2;else
			if(align==taRight	)pos=max_width-tw;else pos=0;

			MakeupText(makeup,pos,row,sp,p-sp);

			makeup.ProcEnd(font_height/2);

			return(true);
		}

		/**
		* ����һ���Ű�õ��ı�
		* @param mat modelview�任����
		* @param makeup �Ű���Ϣ
		* @param limit ����
		*/
		void TileFont::Draw(const Matrix4f *mat,const Makeup &makeup,int limit)
		{
			if(limit==0)return;

			const Makeup::CharMakeup *cm=makeup.MakeupString.Data;

			int n=makeup.MakeupString.Count;
			int i=0;
			int count=0;

			if(limit>0&&n>limit)
				n=limit;

			vertex2d->Begin();
			tex_coord->Begin();

			while(n--)
			{
				TileData::Object *to=GetCharData(cm->ch);

				if(!to||cm->scope.Width<=0||cm->scope.Height<=0)			//����Ϊ0
				{
					cm++;
					continue;
				}

				RenderToVB2DRect(	vertex2d,
									tex_coord,
									to,
									cm->scope.Left+cm->left,
									cm->scope.Top +cm->top);
				count++;

				cm++;
			}

			tex_coord->End();
			vertex2d->End();

//#ifdef _DEBUG
//			Texture2D *tex=tile_data->GetTexture();
//
//			uint8 *buf;
//			int size;
//
//			size=tex->GetImage(HGL_SF_R8,NULL);
//
//			buf=new uint8[size];
//
//			tex->GetImage(HGL_SF_R8,buf);
//
//			SaveMemoryToFile(L"TileFont.RAW",buf,size);
//
//			delete[] buf;
//#endif//_DEBUG

			fnt_mtl->SetColor(Color);
			fnt_draw->SetDrawCount(0,count*6);
			DirectRender2D(fnt_draw,mat);
		}

		/**
		* �Ը�ʽ����ʽ�����ַ���
		* @param l,t �����ַ���������
		* @param fmt ��ʽ���ִ�
		* @return �ַ��������ؼ����
		*/
		float TileFont::DrawFormat(const Matrix4f *mat,const wchar_t *fmt,...)
		{
			va_list va;
			wchar_t str[1024];

			va_start(va,fmt);
			vswprintf_s(str,1023,fmt,va);
			va_end(va);

			return DrawString(mat,str);
		}

		/**
		* �Ը�ʽ����ʽ�����ַ���
		* @param l,t �����ַ���������
		* @param fmt ��ʽ���ִ�
		* @return �ַ��������ؼ����
		*/
		float TileFont::DrawFormat(float l,float t,const wchar_t *fmt,...)
		{
			va_list va;
			wchar_t str[1024];

			va_start(va,fmt);
			vswprintf_s(str,1023,fmt,va);
			va_end(va);

			const Matrix4f pos=translate(l,t,0);

			return DrawString(&pos,str);
		}
	}//namespace graph
}//namespace hgl
