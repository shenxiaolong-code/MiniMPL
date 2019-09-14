命令约定
naming convention
1.	接口类前缀为I
	interface has I prefix
	e.g. ICallbacker
2.  C++类前缀为大写C
	C++ class has C prefix
	e.g. CCallbacker
3.	模板类前缀为T
	template class has T prefix
	e.g. TCallbacker
4.	枚举类型前缀为E
	Enum type has E prefix
	e.g. ECallbackType
5.	数据成员前缀为m_
	data member has m_ prefix
	e.g. m_obj

此库中有一些标准的接口约定
some standard interface convention in MiniMPL:

1.  类型接口:如果一个类型接口是一个类型包装类，则其嵌套了一个成员"type"
	Type Interface:if one type interface represent one type wrapper, it embedded one member "type"
	e.g. template<typename T>    struct Type2Type	{ typedef T type;		};

2.	如果一个类型接口表示一个值，则其嵌套了一个成员"value"
	if one type interface represent one value, it embedded one member "value"
	e.g. template<int TVal>       struct Int2Type	{ enum { value=TVal  };	};
	
3.	如果一个类型接口有一个公开的编译期函数接口，其编译期函数接口的名字一般为"apply"
	if one type interface has public compile-period function interface, the interface name is "apply"
	e.g. 
	template<typename T1>
	struct DemoInterface
	{
		template<template <class,class> class T2>
		struct apply : public Type2Type<typename T2<T1>::type> {};
	}
	
4.	如果一个类型接口有一个公开的运行期函数接口，其运行期函数接口的名字一般为"execute"
	if one type interface has public runtime function interface, the function interface name is "execute"
	e.g. 
	template<typename T1>
	struct DemoInterface
	{
		template<template <class,class> class T2>
		void execute() {};
	}	