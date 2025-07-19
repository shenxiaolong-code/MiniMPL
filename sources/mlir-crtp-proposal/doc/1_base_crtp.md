# Basic CRTP Demo Guide

This document accompanies `base_crtp_demo.cpp` to demonstrate the basic concepts of CRTP (Curiously Recurring Template Pattern) and selective method overriding patterns.

[🇨🇳 中文版本](./base_crtp_demo_cn.md)

## 🎯 Demo Objectives

- Understand the fundamental principles of CRTP pattern
- Master the "default implementation + selective override" design pattern
- Experience more flexible operation definition compared to TableGen

## 📚 Core Concepts

### 1. Basic CRTP Pattern

```cpp
template<typename Derived>
class OpBase {
public:
    // Unified interface - always calls derived implementation
    auto getInput() {
        return derived()->default_getInput();
    }
    
    // Default implementation - derived can selectively override
    auto default_getInput() {
        return this->getOperand(0);
    }
    
private:
    Derived* derived() { return static_cast<Derived*>(this); }
};
```

### 2. Selective Override Principles

- **No override**: Use framework-provided default behavior
- **Selective override**: Only override methods that need customization
- **Full control**: Can override any method

## 🔍 Demo Code Structure

### Part 1: Framework Base
```cpp
// Core CRTP base class
template<typename Derived> class OpBase
// Unified operation interface and default implementations
```

### Part 2: Basic Usage Examples  
```cpp
// SimpleOp: Uses all default implementations
// IdentityOp: Only overrides verification logic
// ComplexOp: Overrides multiple methods
```

### Part 3: Advanced Features
```cpp
// Template operations: BinaryOp<OpKind>
// Compile-time polymorphism and type safety
```

## 🚀 Learning Path

### Step 1: Run the Demo
```bash
cd /home/xiaolongs/scratch/tmp/crtp_trait_bind
g++ -std=c++17 base_crtp_demo.cpp -o base_crtp_demo
./base_crtp_demo
```

### Step 2: Understand the Output
Observe the behavior of different operations:
- Which ones use default implementations
- Which ones use custom implementations
- How verification logic works

### Step 3: Modify the Code
Try:
- Add custom verification to `SimpleOp`
- Override print method for `IdentityOp`
- Create your own operation class

## 💡 Key Advantages Demonstrated

### vs TableGen
| Aspect | TableGen | CRTP (This Demo) |
|--------|----------|------------------|
| **Customization Level** | Fixed extension points | Any method overridable |
| **Learning Cost** | New DSL syntax | Standard C++ patterns |
| **Debugging Experience** | Generated code | Direct source code |
| **IDE Support** | Limited | Full support |

### Flexibility Showcase
```cpp
// Template specialization - more elegant type dispatch
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

## 🔧 Practice Exercises

### Exercise 1: Custom Operation
Create a `SquareOp` class:
- Takes one input value, outputs its square
- Override verification: ensure input is numeric type
- Override print: display "square(%input) -> %output"

### Exercise 2: Conditional Override
Create a templated operation with conditional behavior:
```cpp
template<bool HasCustomPrint>
class ConditionalOp : public OpBase<ConditionalOp<HasCustomPrint>> {
    // Decide whether to override print method based on template parameter
};
```

### Exercise 3: Composition Pattern
Try making an operation inherit from multiple CRTP base classes:
```cpp
class MultiTraitOp : public OpBase<MultiTraitOp>, 
                     public Verifiable<MultiTraitOp>,
                     public Printable<MultiTraitOp> {
    // Combine multiple capabilities
};
```

## 🎓 Advanced Learning

After completing the basic demo, continue learning:
- `enhanced_crtp_trait_bind_demo.cpp` - trait_binding system
- `MLIR_CRTP_RFC_Proposal.md` - Complete technical proposal

## 🔗 Related Resources

- [C++ CRTP Explained](https://en.cppreference.com/w/cpp/language/crtp)
- [MLIR Operations Overview](https://mlir.llvm.org/docs/LangRef/#operations)
- [Modern C++ Design Patterns](https://github.com/AnthonyCalandra/modern-cpp-features)

---

**Remember**: The core of CRTP is "compile-time polymorphism" + "selective override", which is more flexible than TableGen's fixed patterns while maintaining zero runtime overhead! 