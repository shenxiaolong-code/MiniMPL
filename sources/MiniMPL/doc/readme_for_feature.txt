
⑴ 需求(requirements)
重量级的BOOST非常强大，但有时候项目中没有引入它，这时候我们需要自己的模板库。
BOOST is very powerful, but some projects have not include BOOST library.
So we need out own template type trait library -- it is the responsibility of this lightweight library.
即使BOOST非常强大，但有些常用的功能其也没有，而经常性的代码中又需要这些功能。比如把运行期数据转换为元程序需要的编译期数据。
Even if BOOST is very powerful,it can't still meet all requirements. e.g. convert runtime data into compile period data needed by metaprogramming.

/*************************************************************************************************************************************/
⑵ 益处(advantage)
此泛型库抽象了一些常用的业务需求，可以避免大量的重复工作。
它是完全泛型的并且是类型安全的(没有强制类型转换)，如果使用错误将导致编译失败，从而提高了正确率(正确性由编译器保证)。
这个库的很多模板类型推导不需要C++11的支持，这是一个大的优势(VS2010才开始支持C++11)。
this general library draws out some common business and avoid unnecessary repeat work.
it is completed general and type-safe(without any type cast), mistake(s) will cause compile failure, so it improves correctness.
In this library , type deduce need't C++11's support, it is big advantage. (VS2010 begin to support C++11)

/*************************************************************************************************************************************/
⑶ 用法(usage)
下载这个库后，使用VS打开.\CodeLib\testcase\TestCodeLib\TestCodeLib.sln，直接按F5启动，即可以看到许多单元测试的用法/测试用例的输出。
如果需要使用某功能，可以参考其对应的测试代码的用法。(每个功能文件.\CodeLib\include\MiniMPL\xxx.hpp，都对应一个测试文件.\CodeLib\testcase\MiniMPL\test_xxx.hpp)
(这个库的使用及修改是完全自由的，只需要保留文件头中的注释即可)
usage: download this library, open .\CodeLib\testcase\TestCodeLib\TestCodeLib.sln with VS,you can see many usage/test output of unit test.
every feature has according unit test file, it shows its usage. e.g. .\CodeLib\include\MiniMPL\xxx.hpp has according ".\CodeLib\testcase\MiniMPL\test_xxx.hpp" 
this library is all free, the only requirement is that you need to keep the comments in header file.

/*********************************************************************************************************************************************************/
⑷ 本库提供的主要功能介绍：
major feature in this lib:
◆  [typeTraits.hpp]
★	测试类型的基本属性，比如IsConst/IsVoliate/IsRef/isAtomType/isBuildInType/isEnumType/IsIterator/IsPointer/isString/isInnerFloat/isArray/IsBaseDerive/....
★	转换类型的基本属性，比如AddConst/AddVoliate/AddRef/AddPointer,..,RemoveConst/RemoveVoliate/RemoveRef/RemovePointer,...
	这类功能是元程序库的基本支持组件，其它库(比如boost)也提供了，但本库时提供的检测属性更多。
☆	detect type property. e.g.IsConst/IsVoliate/IsRef/isAtomType/isBuildInType/isEnumType/IsIterator/IsPointer/isString/isInnerFloat/isArray/IsBaseDerive/....
☆	convert type basic qualifier,e.g. AddConst/AddVoliate/AddRef/AddPointer,..,RemoveConst/RemoveVoliate/RemoveRef/RemovePointer,...
	get type traits.e.g.const/voliate/ref/isAtomType/isBuildInType/isEnumType/isString/isInnerFloat/isArray/IsBaseDerive/....
	It is base support component of metaprogramming system,it is similiar with BOOST , but this lib provide more.

◆  [typeConvert.hpp]
★	实现类型的修饰符转换。比如让输出参数类型的修饰符(const/voliate/ref/*)和输入参数类型的修饰符一样。
	SameConst/SameVoliate/SameRef/SamePointer/SameAllQualifier/RefAdapter
	应用场景：存取结构体的某类成员，当输入参数有某种const/voliate/ref修饰符时，通常要求返回值也有类似的修饰符。
★	当把"智能指针/stl迭代器/C指针/前三者嵌套"都视为指针时，其内的最终值(非指针值)是一致的，在模板函数中，某些场景需要取得其最终的非指针值。
	应用场景：转发模板函数，如 template<typename T> void transmit(T p) { receive(p); }  //void receive(int&);	
	如果transmit的传入实参p为指针类型(比如smartpointer<vector<int*>::iterator>*或者vector<int*>::iterator)，
	但是转发的接收函数receive的形参为非指针类型(比如int&)，理论上是可以实现转换的。
	Get::finalValue接口提供了这种自动的转: template<typename T> void transmit(T p) { receive(Get::finalValue(p)); }
☆	Convert type qualifiers,e.g. addConst/removeConst.. , keep same output qualifier (const/voliate/ref/*) with input type. 
	apply scenario: get member of one structure object.
☆	Think "stlSmartptr<T>/StlContainer<T>::iterator/T*" as pointer, their inner non-pointer value is same. in some scenario, the final non-pointer value is needed.
	e.g. template<typename T> void transmit(T p) { receive(p); }  //void receive(int&);	
	if real paremeter "p" is smartpointer<vector<int*>::iterator>* or vector<int*>::iterator , but needed parameter by "receive" is int&, in theory it is OK.
	Get::finalValue provide this conversion: template<typename T> void transmit(T p) { receive(Get::finalValue(p)); }

◆  [traverseTypeSet.hpp]
★	C++语法不支持模板函数/模板成员函数作为回调函数。本库采用了封装，可以支持模板函数的回调，并且支持最多7个可变参数（可以简易扩充参数个数）。
	可以遍历一个TypeList或者枚举值范围CEnumRange，然后以满足条件的类型回调用户的模板函数。
	其广泛的应用场景即是把运行期数据以一种非hard-code的方式转化为编译期数据，从而满足元程序对编译期数据的需求。
☆	C++ doesn't support template-based callback function. this lib package support template-based callback function(MAX 7 various parameters,easy to expand).
	It can traverse one TypeList or enum value , then call user's template function by suitable type/enum value.
	This feature converts runtime data into compile data to meet metaprogramming requirement without hard-code way, it is one big advantage.
	
◆	[functionTraits.hpp]
★	获取任意类型函数的各种特征，比如函数的所有参数Params_T，返回值类型Return_T，对象类型Object_T(如果是成员函数)，第N个参数的类型GetFunctionParam<F,N>，
	这些类型都是包含修饰符(const/voliate/ref)的完整类型。
	这些组件对于操作函数非常重要。
☆	get some traits of any function, include all parameter type "Params_T",return type "Return_T", host type "Object_T"(if member-function) , No.x parameter type "GetFunctionParam<F,x>".
	this type include all signature qualifiers.
	This component is very important for metaprogramming based on function. 

◆	有时候STL的算法并不好用，经常是为了第三个参数需要自己写一个专用的琐碎的小函数。
	虽然可以用std的bind或者boost的lambda，但是对于某些嵌套情况，用起来非常麻烦，这个库提供了下面的一些解决方式：
	sometimes STL algorithm is not good and it needs one traival function object(third parameter) , 
	althrough std::bind/boost::lambda is available, but for some nest case, it is very hard to be used.this library provide below features：
	[function.hpp]
★	把既有的多元函数转换为一元函数对象UnaryFunction。它通常应用于泛型(比较/排序/遍历)算法的第三个参数。
☆	convert existing multi-parameters into unary function, it is general used as 3rd parameter in general algorithm. e.g. stl::for_each
	[functionobject.hpp] 
★	把一些常用目的的函数封装成函数对象，比如"比较器/测试器"
☆	function object with special abstract targart. e.g. "comparer/Tester"

◆	[functionCreater.hpp]
★	把多元函数封装为一元函数的帮助函数。(一元函数对象的类型通常不易于书写)
☆	helper function to pack multi-parameters into unary function.(it is hard to write unary function object type)

◆	[paramPackage.hpp] 
★	实现了把任意多个(最多7个，可简易扩充)，任意类型的参数封装成一个参数以利于数据传递。
☆	pack any number parameter (max 7,easy expand) into one parameter . it is easy to transfer.
	
◆	[classregister.hpp] 
★	MFC的动态创建不是泛型的，创造出来的对象必须是CObject的派生类，而且支持的创造方式单一，不够灵活有时候甚至不能满足需求。
	本库里提供了一个泛型的动态创建方式，可以以多种灵活的方式甚至用户自定义的方式来匿名动态创建对象，创建的对象基类可以由用户指定(必须存在派生关系)。 
☆	like MFC's DYNAMIC_CREATE, but the one of MFC is not general,the instance MUST be drived from class CObject，
	MFC dynamic creation has only one create way，sometimes it is not enough。
	this library provides general dynamic create way, can create object by multiple ways , even customized way.and base class can be specified by user.

◆	[callbackWorker.hpp] 
★	最易于使用的回调函数是无参数的回调函数。
	此功能可以把任意多个参数的多元(成员/非成员)函数封装成一个无参数函数，作为简单的回调函数。
☆	best callback function is non-parameter function.
	This feature packs multiple-parameter function into one no-parameter function, it is easy to be used as callback function.

◆	[memberPtr.hpp] 
★	以统一的方式实现了任意级数的结构体成员的存和取，比如多级结构体嵌套。例子：a.m_b.m_c.m_d.....m_x，非常易于在模板设计中使用。
☆	access any level member of structure object by one unified way. e.g：a.m_b.m_c.m_d.....m_x，it is easy to be used in template componment.

◆	[anyObject.hpp]
★	任意对象类(CAnyObject)。提供模板化的指针操作符，如果不支持用户指定指针类型，则转换结果为NULL，从而保证正确性。
☆	package any object(CAnyObject), it operator function is template-based. if it doesn't support conversion, it return NULL.

◆	[dataset.hpp]
★	把STL容器和经典数组封装成统一的形式，在使用上不再区别对待。对于C数组，将会自动检测越界情况。
★	可以使用初始化列表对数组，STL容器进行(反复)初始化。例如：vector<int> a={1,2,3,45,2};
☆	pack STL container and class array into unified object with several same interfaces. 
☆	can initialize array/stl container with initalization list repeated. e.g. vector<int> a={1,2,3,45,2};

◆	[macroLoop.hpp]
★	当多条语句的差别仅仅是一个数字时，可以利用提供的循环宏简化成一条宏语句，从而简化书写。用法可参见对应的单元测试例子。
☆	if only one number is different in multiple statements, can use one macro loop to simplify them (one macro statement)
	usage refer to unit test.
	
◆	[mathOperator.hpp]
★	泛型的数学操作符。"equal/lesser/NotBinary/NotUnary/notEqual/lesserEqual/greater/greaterEqual及交换函数swap/swapif"
☆	general math operator. "equal/lesser/NotBinary/NotUnary/notEqual/lesserEqual/greater/greaterEqual and swap/swapif"

/*************************************************************************************************************************************/
⑸ 感谢及借鉴：
本库中的占位符[placeHolder.hpp]借鉴于boost库，感谢boost库的大师们的灵感。
typelist来自loki库，但是把命名空间Loki改为MiniMPL以避免频繁的命名域切入/切出，感谢Andrei Alexandrescu的精彩演绎与启发.
thanks and borrow:
Args [placeHolder.h] comes from BOOST::MPL. thanks for BOOST team.
typelist comes from loki lib with tiny modification(rename namespace loki to MiniMPL to avoid field switch frequently).thanks for Andrei Alexandrescu