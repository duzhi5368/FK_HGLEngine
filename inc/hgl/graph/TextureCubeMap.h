﻿#ifndef HGL_GRAPH_TEXTURE_CUBEMAP_INCLUDE
#define HGL_GRAPH_TEXTURE_CUBEMAP_INCLUDE

#include<hgl/graph/Texture.h>
namespace hgl
{
	namespace graph
	{
		class Bitmap2D;

		/**
		* CubeMap贴图
		*/
		class TextureCubeMap:public Texture
		{
		protected:

			int width,height;																							///<宽、高

		public:
					int		GetWidth		()const{return width;}														///<取得纹理宽度
					int		GetHeight		()const{return height;}														///<取得纹理高度

		public:

							TextureCubeMap();
			virtual			~TextureCubeMap();

					bool	LoadFile		(const OSString &,uint vf=0,uint ltp=0);									///<从文件加载一个贴图

			virtual bool	SetImage		(uint w,uint h,void_pointer data[6],uint size,TSF sf,uint vf=0,uint ltp=0);	///<创建2D贴图数据
			virtual bool	ChangeImage		(uint f,uint l,uint t,uint w,uint h,void *data,uint bytes,TSF sf);			///<更改2D贴图数据

					bool	SetImage		(Bitmap2D *,uint vf=0,uint ltp=0);											///<从位图创建一个贴图
					bool	ChangeImage		(Bitmap2D *,uint l,uint t);													///<更改贴图数据

			virtual int		GetImage		(void *data_pointer,TSF fmt,int level=0);									///<取得2D贴图数据
		};//class TextureCubeMap
	}//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_TEXTURE_CUBEMAP_INCLUDE
