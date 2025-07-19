# MLIR CRTP 替代方案：操作定义的现代 C++ 方法

使用 **CRTP (奇异递归模板模式)** 作为 TableGen 的替代方案来定义 MLIR 操作的综合提案，提供增强的灵活性、更低的学习门槛和更好的开发体验。

[🌍 English Version](./README.md)

MLIR 社区讨论 : [rfc-modern-c-alternative-to-tablegen-for-mlir-operation-definition](https://discourse.llvm.org/t/rfc-modern-c-alternative-to-tablegen-for-mlir-operation-definition/86800)


## 🔑 核心设计理念：代码非侵入，功能侵入

**关键创新**：用户可以在**自己的作用域内**控制和修改框架行为，而无需修改任何框架代码。

- **代码非侵入**：对框架源代码零修改
- **功能侵入**：完全控制框架行为
- **实现方式**：声明式trait绑定控制框架操作的基类

这种方法颠倒了传统的扩展模型 - 不是框架提供固定的扩展点，而是**用户声明他们想要什么，框架不需要代码增强就能自动适应**。
## 🤖 提示
- 在AI辅助下了解这个方案的实现方法原理，及各种可能的用法变种，可以显著地加速熟悉这个方案的的过程，及探索更多可能的扩展用法。
- 可能的AI提示词
-- "解释MLIR操作定义中的CRTP模式"
-- "对比TableGen与CRTP方案的框架扩展方式"
-- "帮我理解'代码非侵入，功能侵入'的设计理念"
-- "这个方案是怎么在不修改MLIR框架代码的情况下，控制和改变框架的行为及功能的"
-- "分析这个CRTP提案中的trait_binding机制"
-- "我有这样的一个需求(xxx),怎么利用这个方案的技术来解决"

## ⚠️ 错误/异常处理

**错误/异常处理**：本项目的演示代码专注于展示核心技术思想和实质性功能，为了保持简洁和突出重点，省略了详细的错误处理（边界检查、异常处理等）。在生产环境中请添加适当的错误处理机制。

## 🎯 核心概念

不再从 DSL 生成 C++，而是直接使用现代模式编写 C++：

```cpp
// 传统 TableGen 方法
def AddOp : Op<"add", [Commutative]> {
  let hasFolder = 1;  // 仅限于预定义扩展点
}
// 生成约 200 行 C++ 代码

// CRTP 方法  
template<> struct trait_binding<AddOp> : Type2Type<ArithmeticTrait<AddOp>> {};

class AddOp : public Op<AddOp> {
    // 自动继承 ArithmeticTrait 能力
    // 可以重写任何基类方法
    // 可以添加自定义方法
};
// 总共约 15 行，直接的 C++ 代码
```

## 📊 主要优势

| 方面 | TableGen | CRTP 方案 |
|------|----------|-----------|
| **学习曲线** | 新的 DSL 语法 | 基于标准 C++ 模式 |
| **定制化** | 固定扩展点 | 任意方法可重写 |
| **代码生成** | 每个操作 200+ 行 | 0 行生成 |
| **IDE 支持** | 有限 | 完整 C++ 工具链 |
| **调试** | 生成的代码 | 您的实际代码 |
| **模板支持** | 基础 | 完整 C++ 模板 |
| **性能** | 零开销 | 零开销 |

## 🚀 快速开始

### 克隆并运行演示

```bash
git clone https://github.com/shenxiaolong-code/mlir-crtp-proposal
cd mlir-crtp-proposal
cd test

# 方法 1：使用 Makefile（推荐）
make all          # 构建所有演示
make test         # 运行高级 value-binding 演示
make help         # 显示所有可用目标

# 方法 2：手动编译
g++ -std=c++17 base_crtp_demo.cpp -o base_demo && ./base_demo
g++ -std=c++17 demo/1_base_crtp_demo.cpp -o enhanced_demo && ./enhanced_demo
g++ -std=c++17 advanced_bind_demo.cpp -o advanced_demo && ./advanced_demo
```

### 预期输出
演示展示了：
- **选择性重写**：只实现您需要的部分
- **Trait 绑定**：声明式 trait 应用
- **编译时安全**：完整的类型检查和优化

## 🏗️ 架构概览

### 1. 选择性重写模式
```cpp
template<typename Derived>
class OpBase {
public:
    // 统一接口 - 总是委托给派生类
    auto getInput() { return derived()->default_getInput(); }
    bool verify() { return derived()->default_verify(); }
    
    // 默认实现 - 可选择性重写
    auto default_getInput() { /* 框架默认 */ }
    bool default_verify() { return true; }
    
private:
    Derived* derived() { return static_cast<Derived*>(this); }
};
```

### 2. Trait 绑定系统
```cpp
// 框架提供智能默认值
template<typename T>
struct trait_binding : Type2Type<DefaultTrait<T>> {};

// 用户声明性地指定替换
template<> struct trait_binding<AddOp> : Type2Type<ArithmeticTrait<AddOp>> {};
template<> struct trait_binding<LoadOp> : Type2Type<MemoryTrait<LoadOp>> {};

// 操作自动继承相应的 trait
class AddOp : public Op<AddOp> {
    // 自动获得 ArithmeticTrait 能力
};
```

## 📁 项目结构

```
mlir-crtp-proposal/
├── 1_base_crtp.hpp                                 # 基础源文件
├── 2_enhanced_crtp_trait_bind.hpp                  # 增强源文件
├── 3_symbol_bloat_optimize.hpp                     # 符号优化源文件
├── demo
│   ├── 1_base_crtp_demo.cpp                        # 基础 CRTP 模式演示
│   ├── 2_enhanced_crtp_trait_bind_demo.cpp         # 完整 trait_binding 系统演示
│   ├── 3_symbol_bloat_optimize_demo.cpp            # 符号优化演示
│   ├── build.sh                                    # 构建脚本
│   ├── Makefile                                    # 构建makefile
│   └── mlir_demo_types.h                           # 演示类型
├── doc
│   ├── 1_base_crtp_cn.md                           # 基础演示指南（中文）
│   ├── 1_base_crtp.md                              # 基础演示指南（英文）
│   ├── 2_enhanced_crtp_trait_bind_cn.md            # 增强演示指南（中文）
│   ├── 2_enhanced_crtp_trait_bind.md               # 增强演示指南（英文）
│   ├── 3_symbol_bloat_optimize_cn.md               # 符号优化演示指南（中文）
│   └── 3_symbol_bloat_optimize.md                  # 符号优化演示指南（中文）
├── LICENSE                                         # MIT 许可证
├── MLIR_CRTP_RFC_Proposal_cn.md                    # 完整技术 RFC（中文）
├── MLIR_CRTP_RFC_Proposal.md                       # 完整技术 RFC（英文）
├── README_cn.md                                    # 中文版（本文件）
├── README.md                                       # 英文版（本文件的英文版）
└── mpl_api.hpp                                  # 模板元函数工具
```

## 📚 文档

### 面向开发者
- [`1_base_crtp_cn.md`](./doc/1_base_crtp_cn.md) - CRTP 模式介绍
- [`2_enhanced_crtp_trait_bind_cn.md`](./doc/2_enhanced_crtp_trait_bind_cn.md) - 完整 trait_binding 系统
- [`3_symbol_bloat_optimize_cn.md`](./doc/3_symbol_bloat_optimize_cn.md) - 🔥 **工业级 type-to-value-binding 技术**
- [`MLIR_CRTP_RFC_Proposal_cn.md`](./MLIR_CRTP_RFC_Proposal_cn.md) - 综合技术提案

### 演示的关键特性
- **降低学习门槛**：基于标准 C++ 模式，无需额外学习 TableGen DSL
- **高度灵活性**：重写任何方法，而不仅仅是扩展点  
- **非侵入式设计**：框架不变，用户添加特化
- **类型安全**：编译时 trait 检测和验证
- **现代 C++**：模板特化、constexpr、概念
- **🚀 高级值绑定**：符号优化技术（概念验证阶段）
- **🔥 符号表减少**：理论分析显示可大幅减少模板膨胀（需实际验证）
- **🎨 高级类型计算**：使用 [MiniMPL](https://github.com/shenxiaolong-code/MiniMPL) 模板元编程技术

### 性能声明说明
本项目中的性能优势主要基于：
- **理论分析**：基于 C++ 模板机制的编译时优化特性
- **概念验证**：小规模演示代码的测试结果
- **需要验证**：大规模实际项目中的性能表现尚待验证

建议在实际项目中进行基准测试以验证具体性能收益。

## 🔬 技术亮点

### 高级类型计算框架
我们的方法利用了 [MiniMPL TypeList 库](https://github.com/shenxiaolong-code/MiniMPL/blob/master/sources/MiniMPL/include/MiniMPL/typeList_cpp11.hpp) 的模板元编程技术，实现了：

- **工业级类型操作**：编译时类型操作的高级算法
- **动态方言生成**：通过类型变换自动创建操作变体
- **编译时优化**：通过复杂的编译时分发实现零运行时开销

### 模板特化的优雅
替代复杂的条件逻辑：
```cpp
// 清晰的 trait 层次结构
template<BinaryOpKind Kind> struct BinaryOpTraits;
template<> struct BinaryOpTraits<BinaryOpKind::Add> { 
    static constexpr const char* name = "add"; 
    static constexpr bool commutative = true;
};
template<> struct BinaryOpTraits<BinaryOpKind::Sub> { 
    static constexpr const char* name = "sub"; 
    static constexpr bool commutative = false;
};
```

### 编译时 Trait 检测
```cpp
template<typename OpType>
void analyzeOperation(OpType& op) {
    if constexpr (OpType::template hasTrait<ArithmeticTrait<OpType>>()) {
        op.getTrait()->fold();  // 仅为算术操作编译
    }
    
    if constexpr (OpType::template hasTrait<MemoryTrait<OpType>>()) {
        op.getTrait()->getMemorySlots();  // 仅为内存操作编译
    }
}
```

## 🎯 为什么这个替代方案很重要

1. **零代码生成**：直接 C++ 意味着消除中间生成代码
2. **更好的开发体验**：完整的 IDE 支持、直接调试、标准重构
3. **现代 C++ 特性**：模板特化、constexpr、概念等完整支持
4. **渐进迁移**：可以在过渡期间与 TableGen 共存
5. **社区熟悉度**：基于每个 MLIR 开发者都熟悉的 C++
6. **完整替代能力**：覆盖 TableGen 的所有核心功能，同时提供更高灵活性

## ⚠️ 学习曲线和适用性评估

### 前置知识要求
虽然本方案基于标准 C++，但有效使用仍需要：

- **C++ 模板编程**：理解模板特化、CRTP 模式
- **MLIR 架构知识**：熟悉 MLIR 的操作、trait、类型系统
- **现代 C++ 特性**：constexpr、concept、模板元编程基础

### 替代方案的优势场景
本 CRTP 替代方案特别适合：
- ✅ 需要高度定制化的操作定义
- ✅ 团队具备较强 C++ 模板编程能力
- ✅ 希望减少代码生成工具依赖
- ✅ 需要频繁调试和修改操作实现
- ✅ 追求更现代的 C++ 开发体验

### 继续使用 TableGen 的场景
以下情况下 TableGen 可能仍是更好的选择：
- ❌ 团队对 C++ 模板编程不够熟悉
- ❌ 主要使用标准 MLIR 操作模式
- ❌ 项目已经基于 TableGen 且运行良好
- ❌ 需要与现有 TableGen 工具链深度集成

**注意**: 这是一个完整的替代方案，可以处理 TableGen 能处理的所有操作定义场景，但需要团队具备相应的 C++ 技能。

## 🤝 贡献

欢迎为这个项目做贡献！无论您感兴趣的是：
- 扩展演示实现
- 改进文档
- 使用真实 MLIR 方言测试
- 性能基准测试
- 迁移工具开发

请随时提交 issue、pull request 或开始讨论。

## 📬 社区讨论

此提案是 MLIR 社区正在进行的讨论的一部分。详细的技术分析和社区反馈：

- **LLVM Discourse**：[RFC 讨论主题](https://discourse.llvm.org/c/mlir/31)
- **GitHub Issues**：[技术问题和功能请求](https://github.com/shenxiaolong-code/mlir-crtp-proposal/issues)
- **Pull Requests**：[代码改进和扩展](https://github.com/shenxiaolong-code/mlir-crtp-proposal/pulls)

## 📄 许可证

此项目采用 MIT 许可证 - 详情请参阅 [LICENSE](LICENSE) 文件。

## 🙏 致谢

- **MLIR 社区**：构建了优秀的基础设施
- **LLVM 项目**：提供了基础
- **现代 C++ 社区**：推进模板元编程技术

---

**🔗 链接**
- [完整 RFC 文档](./MLIR_CRTP_RFC_Proposal_cn.md)
- [基础演示指南](./base_crtp_demo_cn.md)  
- [增强演示指南](./enhanced_crtp_trait_bind_demo_cn.md)
- [GitHub 仓库](https://github.com/shenxiaolong-code/mlir-crtp-proposal)

 