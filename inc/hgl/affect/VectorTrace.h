#ifndef HGL_AFFECTOR_VECTOR_TRACE_INCLUDE
#define HGL_AFFECTOR_VECTOR_TRACE_INCLUDE

#include<hgl/affect/AffectorObject.h>
#include<hgl/VectorMath.h>
namespace hgl
{
	namespace affect
	{
		class Timer;

		/**
		* 矢量跟踪影响器
		*/
		template<typename T>
		class VectorTrace:public AffectorObject														///矢量跟踪影响器
		{
			Timer *time;																			///<时间记录器

			T Speed;

			float TraceRate;

		public:	//属性

			T Coord;																				///<当前坐标点
			T Target;																				///<目标点

			float MaxSpeed;                                                                         ///<最大速度(默认20)
			float MinDistance;                                                                      ///<最小距离(默认10)
			float MaxSpeedDistance;																	///<最大速度所需距离(默认1000)
			float DecSpeed;																			///<减速幅度(默认0.75)

		public:	//事件

    		DefEvent(void,OnToEnd,(VectorTrace<T> *));												///<到达目的地事件

		public:

			VectorTrace2D(Timer *,const T &coord,const T &speed);
			virtual ~VectorTrace()HGL_DEFAULT_MEMFUNC;

			virtual const u16char *GetClassName()const{return u"VectorTrace";}						///<取得类名

			virtual void Update();                                                                  ///<更新坐标点
		};//class VectorTrace

		using VectorTrace2f=VectorTrace<Vector2f>;
		using VectorTrace3f=VectorTrace<Vector3f>;
	}//namespace affect
}//namespace hgl
#include<hgl/affect/VectorTrace.cpp>
#endif//HGL_AFFECTOR_VECTOR_TRACE_INCLUDE
