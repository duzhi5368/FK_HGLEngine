﻿#ifndef HGL_TYPE_SET_INCLUDE
#define HGL_TYPE_SET_INCLUDE

#include<hgl/type/List.h>
namespace hgl
{
	/**
	* 集合数据列表中不允许数据出现重复性，同时它会将数据排序，所以也可以当做有序列表使用
	*/
	template<typename T> class Set
	{
	protected:

		List<T> data_list;

		bool	FindPos(const T &,int &)const;														///<查找数据如果插入后，会所在的位置，返回是否存在这个数据
		int		FindPos(const T &flag)const{int pos;FindPos(flag,pos);return(pos);}					///<查找数据如果插入后，会所在的位置

	public:	//属性

				List<T> &	GetList		()const{return data_list;}									///<取得数据原始列表
				T *			GetData		()const{return data_list.GetData();}						///<取得数据指针
				int			GetCount	()const{return data_list.GetCount();}						///<取得数据总量

	public:

		Set();
		virtual ~Set()HGL_DEFAULT_MEMFUNC;

				void	SetCount		(int count){data_list.SetCount(count);}						///<指定数据数量，一般用于批量加载前的处理
				void	Malloc			(int count){data_list.Malloc(count);}						///<预分配指定数量的数据空间

				template<typename S>
		const	int		Find			(const S &)const;											///<查找数据位置,不存在返回-1
		const	bool	IsMember		(const T &v)const{return(Find(v)!=-1);}						///<确认是否成员
				int		Add				(const T &);												///<添加一个数据,返回索引号,返回-1表示数据已存在
				int		Add				(const T *,const int);										///<添加一批数据
				int		Add				(const Set<T> &s){return Add(s.GetData(),s.GetCount());}	///<添加一批数据
				bool	Update			(const T &);												///<更新一个数据
				bool	Delete			(const T &);												///<删除一个数据
				int		Delete			(T *,const int);											///<删除一批数据
				bool	DeleteBySerial	(int);														///<删除一个数据,使用序号
				void	Clear			();                                                         ///<清除数据
				void	ClearData		();															///<清除数据，但不释放内存
            	void	DeleteClear		(){data_list.DeleteClear();}								///<清除所有数据并全部调用delete

				T &		operator[]		(int n)const{return data_list[n];}							///<按序列号取得一个数据

				bool	Rand			(T &)const;													///<随机取得一个
	};//template<typename T> class Set
}//namespace hgl
#include<hgl/type/Set.cpp>
#endif//HGL_TYPE_SET_INCLUDE
