
## 项目简介
1. 提供高价值的C++模板元编程基础支持组件，核心功能仅依赖C++03编译器，无需任何标准库或第三方库。
2. 为应用开发者提供基础系统组件（线程、同步、通讯等），简化跨平台开发。

本库最初在C++03(VS2008)+WinCE环境下开发，所有模板代码无需C++11及以上标准支持。
- 使用 MiniMPL::ParamPackage 实现可变模板参数
- 使用 MiniMPL::CGetType::xxx 实现多输入类型推导（类似C++11 decltype）

目前已逐步转向C++11及以上标准，因其提供了更简洁和强大的语言特性（但C++03下的可变模板和类型推导依然可用）。

# MiniMPL
本库为大型C++项目提供高效、灵活的模板元编程工具集。
[核心组件] 2009年4月（C++11诞生前）项目驱动开发，在VS2008(C++03)+WinCE环境下实现，无任何标准库和三方库依赖，提供高价值的模板元编程工具集：
- 非递归实现扁平可变模板参数([paramPack.hpp](./sources/MiniMPL/include/MiniMPL/paramPack.hpp))及其删除/插入/更新元函数
- 基于concept的编程模板元组件([functionParams](./sources/MiniMPL/include/MiniMPL/functionParams.hpp))、模板回调([traverseCallbackMacro.hpp](./sources/MiniMPL/include/MiniMPL/traverseCallbackMacro.hpp))
- 通用对象工厂（类似MFC DYNAMIC_CREATE，无需继承特定基类）([classRegister.hpp](./sources/MiniMPL/include/MiniMPL/classRegister.hpp))
- 多元函数向一元/二元函数转换的元组件([unaryFunction.hpp](./sources/MiniMPL/include/MiniMPL/unaryFunction.hpp))
- 完善的原生type traits类型萃取与变换，无需标准库，仅依赖C++03 ([addRemove.hpp](./sources/MiniMPL/include/MiniMPL/addRemove.hpp)、[isXXX.hpp](./sources/MiniMPL/include/MiniMPL/isXXX.hpp)、[isXXXEx.hpp](./sources/MiniMPL/include/MiniMPL/isXXXEx.hpp))
- 枚举类型reflection功能的基础元编程组件([enumTrait](./sources/MiniMPL/include/MiniMPL/enumTrait.hpp)、[CEnumRange](./sources/MiniMPL/include/MiniMPL/enumTrait.hpp)、[CEnumValue](./sources/MiniMPL/include/MiniMPL/enumTrait.hpp))
- 类型安全、纯编译期计算、static dispatch、零运行时开销的类型容器遍历([traverseTypeContainer.hpp](./sources/MiniMPL/include/MiniMPL/traverseTypeContainer.hpp))
- 统一容器初始化/重初始化接口，无需C++11 ([containerInitializer.hpp](./sources/MiniMPL/include/MiniMPL/containerInitializer.hpp))
- 枚举值自动压缩、静态边界检查、动态值转换([bitsetEnum.hpp](./sources/MiniMPL/include/MiniMPL/bitsetEnum.hpp))
- 多级结构体成员指针，通用快速数据成员存取([memberPtr.hpp](./sources/MiniMPL/include/MiniMPL/memberPtr.hpp))
- 任意类型与字符串互转接口(toString/fromString)，基类static dispatch，性能优于std::cin/std::cout ([fromToString.hpp](./sources/MiniMPL/include/MiniMPL/fromToString.hpp))
- 配套工具集自动生成新代码/测试框架及自动更新测试配置 ([creatNewFiles.bat](./sources/mlir-crtp-proposal/tools/creatNewFiles.bat))

自C++11后，增加了少量基于C++11的新特性，主要用于简化代码、提升性能和可读性。
可通过VS运行 UT_MiniMPL 检查用法和示例。

## OsBase
提供基于OS的跨平台运行时功能（OsBase），实现部分基础功能的C++封装。  
- 提供线程、同步、异步、网络、串口等基础系统封装
- 常用OS工具（如Windows注册表工具）
- 可通过VS运行 UT_OsBase 检查用法和示例

## crtp_trait_bind
- 利用CRTP演示用C++替换MLIR tabgen的可行性 ([1_base_crtp.hpp](./sources/mlir-crtp-proposal/1_base_crtp.hpp))
- 利用CRTP+trait bind演示用户非侵入式增强外部平台框架功能 ([2_enhanced_crtp_trait_bind.hpp](./sources/mlir-crtp-proposal/2_enhanced_crtp_trait_bind.hpp))
- 利用value-type trait方法将复杂长符号转为短符号，解决大型模板项目（如mlir）符号膨胀问题 ([3_symbol_bloat_optimize.hpp](./sources/mlir-crtp-proposal/3_symbol_bloat_optimize.hpp))
- 为MLIR等大规模模板项目提供符号优化和扩展性支持

---

**兼容性说明**：本库已逐步转向C++11及以上标准，部分新特性仅在C++11及以上可用。

**贡献与开源**：欢迎提交issue和PR，详见[CONTRIBUTING.md](./CONTRIBUTING.md)和[LICENSE](./LICENSE)。

详细用法和示例请参考各子目录[README](./README.md)和源码注释。
