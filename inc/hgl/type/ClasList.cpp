#ifndef HGL_CLASLIST_CPP
#define HGL_CLASLIST_CPP

#include<hgl/type/ClasList.h>
namespace hgl
{
	template<typename T,int TypeCount>
	void ClasList<T,TypeCount>::Clear()
	{
		for(int i=0;i<TypeCount;i++)
			clas_object[i].Clear();

		all_object.Clear();
	}

	template<typename T,int TypeCount>
	bool ClasList<T,TypeCount>::Unlink(T *obj)
	{
		if(!obj)return(false);

		for(int i=0;i<TypeCount;i++)
			clas_object[i].DeleteByData(obj);

		return all_object.UnlinkByData(obj);
	}

	template<typename T,int TypeCount>
	void ClasList<T,TypeCount>::UnlinkAll()
	{
		for(int i=0;i<TypeCount;i++)
			clas_object[i].Clear();

		all_object.UnlinkAll();
	}

	template<typename T,int TypeCount>
	bool ClasList<T,TypeCount>::Delete(T *obj)
	{
		if(!obj)return(false);

		for(int i=0;i<TypeCount;i++)
			clas_object[i].DeleteByData(obj);

		return all_object.DeleteByData(obj);
	}

	template<typename T,int TypeCount>
	void ClasList<T,TypeCount>::Add(T *obj)
	{
		if(!obj)return;

		for(int i=0;i<TypeCount;i++)
			if(obj->CheckObjectAttrib(i))
				clas_object[i].Add(obj);

		all_object+=obj;
	}
}//namespace hgl
#endif//HGL_CLASLIST_CPP
