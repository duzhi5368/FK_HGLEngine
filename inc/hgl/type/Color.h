﻿#ifndef	HGL_COLOR_TABLE_INCLUDE
#define	HGL_COLOR_TABLE_INCLUDE

#include<hgl/platform/Platform.h>
namespace hgl
{
	/**
	* 颜色数据定义
	*/
	struct COLOR_DEF			///颜色数据定义
	{
		int red,green,blue;		///<三原色
		int yum;                ///<亮度

		float r,g,b;            ///<三原色浮点值
        float y;                ///<亮度浮点值

		u16char	name[16];	    ///<中文名称
	};

	/**
	* 颜色枚举
	*/
	enum COLOR_ENUM				///颜色枚举
	{
		ceNone,

		ceAliceBlue,			///<艾利斯兰
		ceAntiqueWhite,			///<古董白
		ceAqua,					///<浅绿色
		ceAquaMarine,			///<碧绿色

		ceArdenRed,				///<雅顿红(注：商业使用需获得Elizabeth Arden公司授权)

		ceAzure,				///<天蓝色
		ceBeige,				///<米色
		ceBisque,				///<桔黄色
		ceBlack,				///<黑色
		ceBlanchedAlmond,		///<白杏色
		ceBlue,					///<蓝色
		ceBlueViolet,			///<紫罗兰色
		ceBrown,				///<褐色
		ceBurlyWood,			///<实木色
		ceCadetBlue,			///<军兰色
		ceChartreuse,			///<黄绿色
		ceChocolate,			///<巧克力色
		ceCoral,				///<珊瑚色
		ceCornflowerBlue,		///<菊花兰
		ceCornsilk,				///<米绸色
		ceCrimson,				///<暗深红
		ceCyan,					///<青色
		ceDarkBlue,				///<暗蓝色
		ceDarkCyan,				///<暗青色
		ceDarkGoldenrod,		///<暗金黄
		ceDarkGray,				///<暗灰色
		ceDarkGreen,			///<暗绿色
		ceDarkGrey,				///<暗白色
		ceDarkKhaki,			///<暗黄褐色
		ceDarkMagenta,			///<暗洋红
		ceDarkOliveGreen,		///<暗橄榄绿
		ceDarkOrange,			///<暗桔黄
		ceDarkOrchid,			///<暗紫色
		ceDarkRed,				///<暗红色
		ceDarkSalmon,			///<暗肉色
		ceDarkSeaGreen,			///<暗海兰
		ceDarkSlateBlue,		///<暗灰兰
		ceDarkSlateGray,		///<墨绿色
		ceDarkSlateGrey,		///<暗灰绿
		ceDarkTurquoise,		///<暗宝石绿
		ceDarkViolet,			///<暗紫罗兰
		ceDeepPink,				///<深粉红
		ceDeepSkyBlue,			///<深天蓝
		ceDimGray,				///<暗灰色
		ceDimGrey,				///<暗灰白
		ceDodgerBlue,			///<闪兰色
		ceFireBrick,			///<火砖色
		ceFloralWhite,			///<花白色
		ceForestGreen,			///<森林绿
		ceFuchsia,				///<紫红色
		ceGainsboro,			///<淡灰色
		ceGhostWhite,			///<幽灵白
		ceGold,					///<金色
		ceGoldenrod,			///<金麒麟色
		ceGray,					///<灰色
		ceGreen,				///<绿色
		ceGreenYellow,			///<蓝绿色
		ceGrey,					///<灰白色
		ceHoneydew,				///<蜜色
		ceHotPink,				///<热粉红
		ceIndianRed,			///<印第安红
		ceIndigo,				///<靛青色
		ceIvory,				///<象牙白
		ceKhaki,				///<黄褐色
		ceLavender,				///<淡紫色
		ceLavenderBlush,		///<淡紫红
		ceLawnGreen,			///<草绿色
		ceLemonChiffon,			///<柠檬绸
		ceLightBlue,			///<亮蓝色
		ceLightCoral,			///<亮珊瑚色
		ceLightCyan,			///<亮青色
		ceLightGoldenrodYellow,	///<亮金黄
		ceLightGray,			///<亮灰色
		ceLightGreen,			///<亮绿色
		ceLightGrey,			///<亮灰白
		ceLightPink,			///<亮粉红
		ceLightSalmon,			///<亮肉色
		ceLightSeaGreen,		///<亮海蓝
		ceLightSkyBlue,			///<亮天蓝
		ceLightSlateGray,		///<亮蓝灰
		ceLightSlateGrey,		///<亮蓝白
		ceLightSteelBlue,		///<亮钢兰
		ceLightYellow,			///<亮黄色
		ceLime,					///<酸橙色
		ceLimeGreen,			///<橙绿色
		ceLinen,				///<亚麻色
		ceMagenta,				///<红紫色
		ceMaroon,				///<粟色
		ceMediumAquamarine,		///<间绿色
		ceMediumBlue,			///<间兰色
		ceMediumOrchid,			///<间淡紫
		ceMediumPurple,			///<间紫色
		ceMediumSeaGreen,		///<间海蓝
		ceMediumSlateBlue,		///<间暗蓝
		ceMediumSpringGreen,	///<间春绿
		ceMediumTurquoise,		///<间绿宝石
		ceMediumVioletRed,		///<间紫罗兰
		ceMidNightBlue,			///<中灰蓝
		ceMintCream,			///<薄荷色
		ceMistyRose,			///<浅玫瑰
		ceMoccasin,				///<鹿皮色

		ceMozillaRed,			///<Mozilla red
		ceMozillaSand,			///<Mozilla sand
		ceMozillaCharcoal,		///<Mozilla charcoal

		ceNavajoWhite,			///<纳瓦白
		ceNavy,					///<海军色

        ceNiveaBlue,            ///<妮维雅蓝(注：商业使用需获得Beiersdorf AG授权)

        ceNokiaBlue,            ///<诺基亚蓝

		ceOldLace,				///<老花色
		ceOlive,				///<橄榄色
		ceOlivedrab,			///<深绿褐色
		ceOrange,				///<橙色
		ceOrangeRed,			///<红橙色
		ceOrchid,				///<淡紫色
		cePaleGoldenrod,		///<苍麒麟色
		cePaleGreen,			///<苍绿色
		cePaleTurquoise,		///<苍宝石绿
		cePaleVioletRed,		///<苍紫罗兰色
		cePapayawhip,			///<番木色
		cePeachpuff,			///<桃色
		cePeru,					///<秘鲁色
		cePink,					///<粉红色
		cePlum,					///<洋李色
		cePowderBlue,			///<粉蓝色
		cePurple,				///<紫色
		ceRed,					///<红色
		ceRosyBrown,			///<褐玫瑰红
		ceRoyalBlue,			///<皇家蓝
		ceSaddleBrown,			///<重褐色
		ceSalmon,				///<鲜肉色

        ceSamsungBlue,          ///<三星蓝

		ceSandyBrown,			///<沙褐色
		ceSeaGreen,				///<海绿色
		ceSeaShell,				///<海贝色
		ceSienna,				///<赭色
		ceSilver,				///<银色
		ceSkyBlue,				///<天蓝色
		ceSlateBlue,			///<石蓝色
		ceSlateGray,			///<灰石色
		ceSlateGrey,			///<白灰石色
		ceSnow,					///<雪白色
		ceSpringGreen,			///<春绿色
		ceSteelBlue,			///<钢兰色
		ceTan,					///<茶色
		ceTeal,					///<水鸭色
		ceThistle,				///<蓟色

        ceTiffanyBlue,          ///<蒂芙尼蓝(知更鸟蛋蓝/勿忘我蓝)(注：商业使用需获取Tiffany公司授权)

		ceTomato,				///<西红柿色
		ceTurquoise,			///<青绿色
		ceViolet,				///<紫罗兰色
		ceWheat,				///<浅黄色
		ceWhite,				///<白色
		ceWhiteSmoke,			///<烟白色
		ceYellow,				///<黄色
		ceYellowGreen,			///<黄绿色

		ceEnd
	};//enum COLOR_ENUM

	extern COLOR_DEF prv_color[ceEnd+1];
}//namespace hgl
#endif//HGL_COLOR_TABLE_INCLUDE
