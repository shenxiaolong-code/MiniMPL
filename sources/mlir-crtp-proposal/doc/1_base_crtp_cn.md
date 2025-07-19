# 基础 CRTP 演示指南

本文档配合 `base_crtp_demo.cpp` 演示 CRTP (奇异递归模板模式) 的基本概念和选择性方法重写模式。

[🌍 English Version](./base_crtp_demo.md)

## 🎯 演示目标

- 理解 CRTP 模式的基本原理
- 掌握"默认实现 + 选择性重写"的设计模式
- 体验相比 TableGen 更灵活的操作定义方式

## 📚 核心概念

### 1. 基础 CRTP 模式

```cpp
template<typename Derived>
class OpBase {
public:
    // 统一接口 - 总是调用派生实现
    auto getInput() {
        return derived()->default_getInput();
    }
    
    // 默认实现 - 派生类可以选择性重写
    auto default_getInput() {
        return this->getOperand(0);
    }
    
private:
    Derived* derived() { return static_cast<Derived*>(this); }
};
```

### 2. 选择性重写原则

- **不重写**：使用框架提供的默认行为
- **选择性重写**：只重写需要定制的方法
- **灵活控制**：可以重写任意方法

## 🔍 演示代码结构

### 第一部分：框架基础
```cpp
// 核心 CRTP 基类
template<typename Derived> class OpBase
// 统一的操作接口和默认实现
```

### 第二部分：基础使用示例  
```cpp
// SimpleOp: 使用所有默认实现
// IdentityOp: 只重写验证逻辑
// ComplexOp: 重写多个方法
```

### 第三部分：高级特性
```cpp
// 模板操作：BinaryOp<OpKind>
// 编译时多态和类型安全
```

## 🚀 学习路径

### 第一步：运行演示
```bash
cd /home/xiaolongs/scratch/tmp/crtp_trait_bind
g++ -std=c++17 base_crtp_demo.cpp -o base_crtp_demo
./base_crtp_demo
```

### 第二步：理解输出
观察不同操作的行为：
- 哪些使用了默认实现
- 哪些使用了自定义实现
- 验证逻辑如何工作

### 第三步：修改代码
尝试：
- 为 `SimpleOp` 添加自定义验证
- 为 `IdentityOp` 重写打印方法
- 创建自己的操作类

## 💡 关键优势演示

### vs TableGen
| 方面 | TableGen | CRTP (本演示) |
|------|----------|---------------|
| **定制程度** | 固定扩展点 | 任意方法可重写 |
| **学习成本** | 新 DSL 语法 | 标准 C++ 模式 |
| **调试体验** | 生成代码 | 直接源码 |
| **IDE 支持** | 有限 | 完整支持 |

### 灵活性展示
```cpp
// 模板特化 - 更优雅的类型分发
template<BinaryOpKind Kind> struct BinaryOpTraits;
template<> struct BinaryOpTraits<BinaryOpKind::Add> { 
    static constexpr const char* name = "add"; 
};
template<> struct BinaryOpTraits<BinaryOpKind::Sub> { 
    static constexpr const char* name = "sub"; 
};

template<BinaryOpKind Kind>
class BinaryOp : public OpBase<BinaryOp<Kind>> {
    static StringRef getOperationName() {
        return BinaryOpTraits<Kind>::name;
    }
};
```

## 🔧 实践练习

### 练习1：自定义操作
创建一个 `SquareOp` 类：
- 接受一个输入值，输出其平方
- 重写验证：确保输入是数值类型
- 重写打印：显示 "square(%input) -> %output"

### 练习2：条件重写
创建一个带模板参数的操作：
```cpp
template<bool HasCustomPrint>
class ConditionalOp : public OpBase<ConditionalOp<HasCustomPrint>> {
    // 根据模板参数决定是否重写 print 方法
};
```

### 练习3：组合模式
尝试让一个操作继承多个 CRTP 基类：
```cpp
class MultiTraitOp : public OpBase<MultiTraitOp>, 
                     public Verifiable<MultiTraitOp>,
                     public Printable<MultiTraitOp> {
    // 组合多种能力
};
```

## 🎓 进阶学习

完成基础演示后，继续学习：
- `enhanced_crtp_trait_bind_demo.cpp` - trait_binding 系统
- `MLIR_CRTP_RFC_Proposal_cn.md` - 完整技术提案

## 🔗 相关资源

- [C++ CRTP 详解](https://en.cppreference.com/w/cpp/language/crtp)
- [MLIR 操作概览](https://mlir.llvm.org/docs/LangRef/#operations)
- [现代 C++ 设计模式](https://github.com/AnthonyCalandra/modern-cpp-features)

---

**记住**：CRTP 的核心是"编译时多态" + "选择性重写"，这比 TableGen 的固定模式更灵活，同时保持零运行时开销！ 