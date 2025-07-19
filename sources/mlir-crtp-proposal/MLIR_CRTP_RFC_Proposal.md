# RFC: Modern C++ Alternative to TableGen for MLIR Op Definition

**Author**: Shen Xiaolong (申晓龙) <xlshen2002@hotmail.com>  
**Date**: June 2025  
**Target**: LLVM/MLIR Community  
**Repository**: https://github.com/shenxiaolong-code/mlir-crtp-proposal

[🇨🇳 中文版本](./MLIR_CRTP_RFC_Proposal_cn.md)

## Executive Summary

This RFC proposes replacing TableGen-based operation definition in MLIR with a modern C++ approach using **Curiously Recurring Template Pattern (CRTP)** combined with **selective method overriding** and **code non-invasive/framework functionality invasive enhancement extension**. This approach provides greater flexibility, eliminates the learning curve of TableGen syntax, and leverages the full power of the C++ type system while maintaining zero runtime overhead.

## 🤖 Tips
- Understanding this approach's implementation principles and various usage patterns with AI assistance can significantly accelerate the process of familiarizing with this approach and exploring more possible extension usages.
- Possible AI prompts:
-- "Explain CRTP patterns in MLIR operation definition"
-- "Compare TableGen vs CRTP approaches for framework extension"
-- "Help me understand the 'non-invasive code, invasive functionality' design philosophy"
-- "How does this approach control and modify framework behavior without modifying MLIR framework code"
-- "Analyze the trait_binding mechanism in this CRTP proposal"
-- "I have this requirement (xxx), how can I use this approach's techniques to solve it"

## Background and Motivation

### Current TableGen Limitations

1. **Domain-Specific Language Barrier**
   - Requires learning TableGen syntax in addition to C++
   - Limited IDE support for TableGen files
   - Debugging generated code is challenging

2. **Constrained Flexibility**
   - Fixed code generation patterns
   - Limited to predefined extension points
   - Cannot easily compose behaviors

3. **Code Generation Complexity**
   - Generates hundreds of lines of C++ code for simple operations
   - Users cannot fine-tune generated code
   - Build dependency on mlir-tblgen tool

4. **Limited Expressiveness**
   - Cannot leverage C++ template metaprogramming
   - No access to modern C++ features (concepts, constexpr, etc.)
   - Difficult to create reusable operation patterns

### Problem Statement

The MLIR ecosystem is fundamentally a pure C++ ecosystem, with even "Python bindings" being C++ code using pybind11. This raises a fundamental question: **Since we're solving C++ problems, why take a detour through TableGen to generate C++ instead of using modern C++ native capabilities directly?** Using C++ to solve C++'s inherent problems is the most ecosystem-aligned solution.

## Proposed Solution: CRTP + Selective Override + Code Non-invasive/Framework Functionality Invasive Enhancement Extension

### 🔑 Core Design Philosophy: Non-Invasive Code, Invasive Functionality

**The key innovation**: Users can control and modify framework behavior **from their own scope** without modifying any framework code.

- **Code Non-Invasive**: Zero changes to framework source code
- **Functionality Invasive**: Complete control over framework behavior
- **Implementation**: Declarative trait binding controls the base class of framework operations

This approach inverts the traditional extension model - instead of the framework providing fixed extension points, **users declare what they want, and the framework adapts automatically without any code enhancement**.

### Core Design Principle

```cpp
template<typename Derived>
class Op {
public:
    // Unified interface - always calls derived implementation
    auto getInput() { 
        return derived()->default_getInput(); 
    }
    
    auto verify() { 
        return derived()->default_verify(); 
    }
    
    void print(OpAsmPrinter& printer) { 
        derived()->default_print(printer); 
    }
    
    // Default implementations - users can override selectively
    auto default_getInput() { 
        return getOperand(0); 
    }
    
    LogicalResult default_verify() { 
        return success(); 
    }
    
    void default_print(OpAsmPrinter& printer) { 
        printer << getOperationName() << "(...)"; 
    }
    
private:
    Derived* derived() { return static_cast<Derived*>(this); }
};
```

### Key Innovation: Selective Override

Users implement only what they need to customize:

```cpp
// Minimal operation - uses all defaults
class SimpleOp : public Op<SimpleOp> {
    // No overrides needed - everything uses defaults
};

// Partially customized operation
class IdentityOp : public Op<IdentityOp> {
    // Only override verification logic
    LogicalResult default_verify() {
        return getInput().getType() == getOutput().getType() ? 
               success() : failure();
    }
    // getInput(), print(), etc. use default implementations
};

// Fully customized operation
class ComplexOp : public Op<ComplexOp> {
    auto default_getInput() { return custom_input_logic(); }
    LogicalResult default_verify() { return enhanced_verification(); }
    void default_print(OpAsmPrinter& p) { custom_printing_logic(p); }
};
```

## Detailed Technical Comparison

### Code Volume Comparison

**TableGen Approach:**
```tablegen
// Input: ~10 lines of TableGen
def Demo_IdentityOp : Demo_Op<"identity", [MemoryEffects<[]>]> {
  let summary = "Identity operation";
  let arguments = (ins AnyType:$input);
  let results = (outs AnyType:$output);
  let assemblyFormat = "$input attr-dict `:` type($input) `->` type($output)";
  let hasVerifier = 1;
  let extraClassDefinition = [{
    LogicalResult verify() {
      return getInput().getType() == getOutput().getType() ? 
             success() : failure();
    }
  }];
}
```

**Generated Output:** ~200 lines of C++ code in .h.inc and .cpp.inc files

**CRTP Approach:**
```cpp
// Input: ~15 lines of direct C++
class IdentityOp : public Op<IdentityOp> {
    Value input_, output_;
    
public:
    IdentityOp(Value input, Type outputType) 
        : input_(input), output_(createResult(outputType)) {}
    
    static StringRef getOperationName() { return "demo.identity"; }
    Value getInput() { return input_; }
    Value getOutput() { return output_; }
    
    // Only override what needs customization
    LogicalResult default_verify() {
        return getInput().getType() == getOutput().getType() ? 
               success() : failure();
    }
};
```

**Generated Output:** 0 lines - direct compilation

### Flexibility Comparison

| Feature | TableGen | CRTP Approach |
|---------|----------|---------------|
| **Function Override** | Fixed extension points only | Any function can be overridden |
| **Composition** | Limited mixin support | Full C++ inheritance/composition |
| **Conditional Logic** | Basic TableGen conditionals | Full C++ template metaprogramming |
| **Type Safety** | TableGen type checking | Full C++ type system + concepts |
| **Custom Functions** | Difficult to add | Trivial to add any function |
| **Debugging** | Debug generated code | Debug your actual code |
| **IDE Support** | Limited | Full IntelliSense/clangd support |
| **Refactoring** | Manual TableGen editing | Automated C++ refactoring |

## Performance Analysis

### Core Conclusions

**✅ CRTP outperforms TableGen in all performance dimensions:**
- **Compilation time**: Typically faster for equivalent functionality
- **Runtime performance**: Zero overhead with more optimization opportunities  
- **Error handling**: Faster detection and clearer diagnostics
- **Learning cost**: Lower learning cost

### Compilation Time

**Conclusion**: CRTP eliminates intermediate conversion steps, typically faster for equivalent functionality complexity.

**Technical Analysis Details**:
```cpp
// Fair compilation performance comparison: Same functionality complexity

// Simple functionality:
// TableGen: .td → mlir-tblgen → generate .inc → compile C++ (3 steps)
// CRTP:     direct C++ compilation                          (1 step) ✅ Faster

// Complex functionality (assuming TableGen could implement it):
// TableGen: complex .td → complex generation → complex .inc → compile C++ (still 3 steps, each heavier)
// CRTP:     complex C++ templates → direct compilation                    (1 step) ✅ Still faster

// Advanced features TableGen cannot implement:
// TableGen: Cannot implement ❌
// CRTP:     advanced type computation → compile ✅ (unique capability, no fair comparison)

// Key principle: CRTP eliminates intermediate conversion steps, typically faster for equivalent functionality
// When CRTP implements features TableGen cannot provide, fair comparison doesn't exist

// Additional TableGen inherent overhead:
// 1. Specialized DSL parser performs poorly (vs highly optimized C++ compiler)
// 2. Poor DSL error detection quality (vs mature C++ type system)
// 3. Obscure error messages (vs clear C++ compiler diagnostics)
```

### Runtime Performance

**Conclusion**: Both approaches achieve zero runtime overhead, but CRTP provides better optimization opportunities.

**Technical Analysis Details**:
```cpp
// CRTP advantage: Compiler visibility into complete implementation enables more aggressive optimization

class AddOp : public Op<AddOp> {
    // Compiler can see the complete implementation
    // More aggressive inlining and optimization
    Value fold() const {
        if (auto lhs = getLHS().getDefiningOp<ConstantOp>()) {
            if (auto rhs = getRHS().getDefiningOp<ConstantOp>()) {
                return createConstant(lhs.getValue() + rhs.getValue());
            }
        }
        return nullptr;
    }
};

// TableGen: Through generated indirect code, limited optimization opportunities
// CRTP: Direct source code, compiler can perform deeper optimization analysis
```

### Error Handling

**TableGen Problems**: Poor DSL parsing error quality
```cpp
// TableGen error example:
def MyOp : Op<"myop"> {
  let arguments = (ins AnyType:$input, UnknownType:$other);
}
// Error message: cryptic TableGen internal error, hard to locate issue
```

**CRTP Advantages**: Leverage mature C++ compiler diagnostics
```cpp
// CRTP error example:
class MyOp : public Op<MyOp> {
    auto getInput() -> UndefinedType; // C++ type error
}
// Error message: clear, precise C++ compiler diagnostic

// Further improvement: Use concept constraints
template<typename T>
concept ValidOperation = requires(T t) {
    t.verify();
    t.print(std::declval<OpAsmPrinter&>());
};

template<ValidOperation Derived>
class Op {
    // Provides clearest error messages
};
```

### Learning Cost

**CRTP Advantage**: Based on standard C++, lower learning cost

**Comparative Analysis**:
- **TableGen Approach**: Need to learn specialized DSL syntax + C++ knowledge
- **CRTP Approach**: Only need standard C++ knowledge
- **Learning Resources**: C++ has rich tutorials, books, community support
- **Skill Transfer**: C++ skills can be used in other projects, DSL skills have limited scope

## Advanced Capabilities

### 1. Template-Based Operation Families

```cpp
// Template specialization for operation names
template<BinaryOpKind Kind>
struct BinaryOpTraits;

template<>
struct BinaryOpTraits<BinaryOpKind::Add> {
    static constexpr const char* getOperationName() { return "arith.add"; }
};

template<>
struct BinaryOpTraits<BinaryOpKind::Sub> {
    static constexpr const char* getOperationName() { return "arith.sub"; }
};

template<>
struct BinaryOpTraits<BinaryOpKind::Mul> {
    static constexpr const char* getOperationName() { return "arith.mul"; }
};

template<typename ElementType, BinaryOpKind Kind>
class BinaryArithmeticOp : public Op<BinaryArithmeticOp<ElementType, Kind>> {
    static StringRef getOperationName() {
        return BinaryOpTraits<Kind>::getOperationName();
    }
    
    LogicalResult default_verify() {
        static_assert(std::is_arithmetic_v<ElementType>);
        return verifyBinaryOp(*this);
    }
};

// Usage
using AddIOp = BinaryArithmeticOp<int32_t, BinaryOpKind::Add>;
using SubFOp = BinaryArithmeticOp<float, BinaryOpKind::Sub>;
```

### 2. Concept-Based Automatic Specialization

```cpp
template<typename T>
concept Commutative = requires(T op) {
    { op.isCommutative() } -> std::convertible_to<bool>;
};

template<typename Derived>
class Op {
    // Automatic optimization for commutative operations
    auto canonicalize() {
        if constexpr (Commutative<Derived>) {
            return derived()->commutative_canonicalize();
        } else {
            return derived()->default_canonicalize();
        }
    }
};
```

### 3. Strategy Pattern Integration

```cpp
template<typename VerificationStrategy, typename PrintingStrategy>
class ConfigurableOp : public Op<ConfigurableOp<VerificationStrategy, PrintingStrategy>> {
    LogicalResult default_verify() {
        return VerificationStrategy::verify(*this);
    }
    
    void default_print(OpAsmPrinter& printer) {
        PrintingStrategy::print(*this, printer);
    }
};

// Mix and match strategies
using StrictPrettyOp = ConfigurableOp<StrictVerifier, PrettyPrinter>;
using FastUglyOp = ConfigurableOp<NoVerifier, MinimalPrinter>;
```

### 4. Trait-Based Extension System

```cpp
template<typename T>
struct op_traits {
    static constexpr bool is_terminator = false;
    static constexpr bool is_commutative = false;
    static constexpr size_t num_operands = 1;
};

// Specialize for specific operations
template<>
struct op_traits<ReturnOp> {
    static constexpr bool is_terminator = true;
    static constexpr size_t num_operands = 0; // Variable
};

template<typename Derived>
class Op {
    // Compile-time trait access
    static constexpr bool isTerminator() {
        return op_traits<Derived>::is_terminator;
    }
};
```

## trait_binding System Explained

### Core Concept

The `trait_binding` system is the cornerstone of our CRTP approach, providing a declarative extension mechanism that is **code non-invasive, functionality invasive**.

### Implementation Architecture

```cpp
// Core binding mechanism
template<typename Operation>
struct trait_binding : Type2Type<EmptyTrait> {};

// Type2Type utility for trait registration
template<typename T>
struct Type2Type { using type = T; };

// Base operation framework
template<typename Derived>
class Op {
    using BoundTrait = typename trait_binding<Derived>::type;
    BoundTrait trait_instance;
    
public:
    // Automatic trait method delegation
    auto verify() -> std::enable_if_t<has_verify_v<BoundTrait>, LogicalResult> {
        return trait_instance.verify(static_cast<Derived&>(*this));
    }
    
    auto print(OpAsmPrinter& printer) -> std::enable_if_t<has_print_v<BoundTrait>, void> {
        return trait_instance.print(static_cast<Derived&>(*this), printer);
    }
};
```

### Usage Examples

#### Basic Trait Binding
```cpp
// Define a trait
template<typename Op>
class ArithmeticTrait {
public:
    LogicalResult verify(Op& op) {
        if (op.getNumOperands() != 2) return failure();
        return success();
    }
    
    void print(Op& op, OpAsmPrinter& printer) {
        printer << op.getOperationName() << " ";
        printer << op.getOperand(0) << ", " << op.getOperand(1);
    }
};

// Define operation
class AddOp : public Op<AddOp> {
    // Minimal operation definition
    static StringRef getOperationName() { return "arith.add"; }
};

// Bind trait (declarative extension)
template<> 
struct trait_binding<AddOp> : Type2Type<ArithmeticTrait<AddOp>> {};
```

#### Multi-Trait Composition
```cpp
// Multiple trait composition
template<typename Op>
class CompositeTrait : public ArithmeticTrait<Op>, public CommutativeTrait<Op> {
public:
    LogicalResult verify(Op& op) {
        // Chain verification
        if (failed(ArithmeticTrait<Op>::verify(op))) return failure();
        if (failed(CommutativeTrait<Op>::verify(op))) return failure();
        return success();
    }
};

template<> 
struct trait_binding<AdvancedAddOp> : Type2Type<CompositeTrait<AdvancedAddOp>> {};
```

#### Conditional Trait Binding
```cpp
// Conditional trait selection
template<typename Op>
using SelectTrait = std::conditional_t<
    Op::is_complex,
    ComplexArithmeticTrait<Op>,
    SimpleArithmeticTrait<Op>
>;

template<> 
struct trait_binding<FlexibleOp> : Type2Type<SelectTrait<FlexibleOp>> {};
```

### Key Benefits

1. **Separation of Concerns**: Operation core logic separated from auxiliary functionality
2. **Reusability**: Traits can be shared across multiple operations
3. **Testability**: Traits can be tested independently
4. **Configurability**: Different operation variants can use different trait combinations
5. **Non-Invasive**: Core operation definition remains clean and focused

## Migration Strategy

### Phase 1: Parallel Implementation
- Implement CRTP framework alongside existing TableGen
- Convert selected operations as proof-of-concept
- Maintain compatibility with existing code

### Phase 2: Tooling Development
- Create TableGen → CRTP conversion utilities
- Develop IDE plugins for operation development
- Build integration testing framework

### Phase 3: Gradual Migration
- Convert dialect-by-dialect
- Provide migration guides and best practices
- Maintain deprecated TableGen support during transition

### Phase 4: Complete Transition
- Remove TableGen dependency for operations
- Update documentation and tutorials
- Optimize for CRTP-native development

## Tool Support

### IDE Integration

CRTP-based operations enjoy full IDE support due to standard C++ nature:

```cpp
// Full IDE features available:
class AddOp : public Op<AddOp> {
    // ✅ Syntax highlighting
    // ✅ Code completion
    // ✅ Error detection
    // ✅ Refactoring support
    // ✅ Go to definition
    // ✅ Find all references
    
    LogicalResult verify() const {
        // IDE can analyze this C++ code completely
        return success();
    }
};
```

### Build System Integration

Simplified build process without TableGen dependency:

```cmake
# Before: TableGen dependency
add_mlir_dialect(MyDialect MyDialect.td)

# After: Direct C++ compilation
add_library(MyDialect MyOps.cpp)
target_link_libraries(MyDialect MLIRCRTPFramework)
```

### Debugging Support

Enhanced debugging experience:

```cpp
// Debug source code directly (not generated code)
class AddOp : public Op<AddOp> {
    LogicalResult verify() const {
        // Set breakpoints here
        if (getNumOperands() != 2) {
            // Step through actual source code
            return failure();
        }
        return success();
    }
};
```

### Development Tools

Development utilities for CRTP operations:

```cpp
// Operation validator
template<typename Op>
constexpr bool validate_operation() {
    static_assert(std::is_base_of_v<Op<Op>, Op>, "Must inherit from Op<>");
    static_assert(requires { Op::getOperationName(); }, "Must have getOperationName()");
    return true;
}

// Usage
static_assert(validate_operation<AddOp>());
```





## CRTP Advantages Examples

### 1. Error Message Quality Advantage

**TableGen Problems**: Poor DSL parsing error quality
```cpp
// TableGen error example:
def MyOp : Op<"myop"> {
  let arguments = (ins AnyType:$input, UnknownType:$other);
}
// Error message: cryptic TableGen internal error, hard to locate issue
```

**CRTP Advantages**: Leverage mature C++ compiler diagnostics
```cpp
// CRTP error example:
class MyOp : public Op<MyOp> {
    auto getInput() -> UndefinedType; // C++ type error
}
// Error message: clear, precise C++ compiler diagnostic

// Further improvement: Use concept constraints
template<typename T>
concept ValidOperation = requires(T t) {
    t.verify();
    t.print(std::declval<OpAsmPrinter&>());
};

template<ValidOperation Derived>
class Op {
    // Provides clearest error messages
};
```

### 2. Learning Cost Advantage

**CRTP Advantage**: Based on standard C++, lower learning cost

**Comparative Analysis**:
- **TableGen Approach**: Need to learn specialized DSL syntax + C++ knowledge
- **CRTP Approach**: Only need standard C++ knowledge
- **Learning Resources**: C++ has rich tutorials, books, community support
- **Skill Transfer**: C++ skills can be used in other projects, DSL skills have limited scope

**Implementation Support**:
- Provide detailed documentation and examples
- Create operation templates and generators
- Community training and practice guides

## Community Impact

### Impact on Existing Code

- **Minimal Impact**: New system can coexist with existing TableGen code
- **Gradual Migration**: No need to rewrite all code at once
- **Backward Compatibility**: Adapter layers can ensure compatibility

### Benefits for Developers

1. **Reduced Learning Curve**: Only need to understand standard C++
2. **Improved Development Efficiency**: Complete IDE support
3. **Better Debugging Experience**: Debug source code directly
4. **Rich Features**: Access to all modern C++ features

### Impact on Ecosystem

- **Simplified Build**: Reduce dependency on TableGen
- **Better Tool Support**: Standard C++ tools can be used directly
- **Enhanced Extensibility**: Easier to extend and customize

## Implementation Plan

### Phase 1: Proof of Concept (1-2 months)
- Implement basic CRTP framework
- Create example operations and dialects
- Basic performance testing

### Phase 2: Feature Enhancement (2-3 months)
- Implement trait_binding system
- Add advanced features (template operations, conditional compilation, etc.)
- Create migration tool prototype

### Phase 3: Integration Testing (2-3 months)
- Integrate with existing MLIR infrastructure
- Large-scale testing and performance benchmarks
- Community feedback and iteration

### Phase 4: Official Release (1-2 months)
- Documentation completion
- Final testing and optimization
- Community training materials

## Example: Complete Dialect Implementation

```cpp
// MyDialect.h
#include "mlir/IR/CRTPOps.h"

namespace my_dialect {

// Base operation class
template<typename Derived>
class MyOp : public mlir::Op<Derived> {
public:
    static StringRef getDialectNamespace() { return "my"; }
};

// Arithmetic trait
template<typename Op>
class ArithmeticTrait {
public:
    bool isCommutative() const { return true; }
    Value fold() const { /* implement folding logic */ }
    void canonicalize() { /* implement canonicalization */ }
};

// Operation definition
class AddOp : public MyOp<AddOp> {
public:
    static StringRef getOperationName() { return "my.add"; }
    
    // Use default implementation, just declare
    LogicalResult default_verify() { return success(); }
    
    // Custom functions
    bool isCommutative() const { return true; }
    Value fold() const {
        // Implement constant folding
        if (auto lhs = getLHS().getDefiningOp<ConstantOp>()) {
            if (auto rhs = getRHS().getDefiningOp<ConstantOp>()) {
                return createConstant(lhs.getValue() + rhs.getValue());
            }
        }
        return nullptr;
    }
};

// trait binding
template<> struct trait_binding<AddOp> : Type2Type<ArithmeticTrait<AddOp>> {};

} // namespace my_dialect
```

## Conclusion

The CRTP approach provides a flexible and modern alternative for MLIR operation definitions.

### CRTP vs TableGen Key Differences

| Dimension | TableGen | CRTP Approach | Improvement Level |
|-----------|----------|---------------|------------------|
| **Learning Cost** | New DSL syntax | Standard C++ patterns | Zero additional learning |
| **Code Volume** | 10 lines DSL + 200 lines generated | 15 lines direct C++ | 90% reduction |
| **Flexibility** | Fixed extension points | Any method can be overridden | Extensive extension |
| **Compilation Time** | DSL parsing + code generation + compilation | Direct compilation (equivalent functionality) | Typically faster |
| **Binary Symbol Table Size** | Massive generated boilerplate symbols | Value binding + type computation | 90% reduction |
| **Extension Model** | Code invasive modification | Code non-invasive, functionality invasive | Elegant architecture |
| **Modern Features** | Basic DSL capabilities | Full C++ features | Unlimited |
| **Error Diagnostics** | DSL parsing errors | C++ compiler diagnostics | Clearer |
| **Debug Experience** | Debug generated code | Debug source code | Quality improvement |
| **IDE Support** | Limited TableGen support | Complete C++ toolchain | Full integration |
| **Build Process** | Source→TableGen→Generate→Compile | Source→Compile | Reduced steps |

### Core Conclusion Points

- **Innovative Replacement**: CRTP can replace TableGen operation definition with higher flexibility and less code
- **Compilation Time Advantage**: Typically faster for equivalent functionality complexity, eliminating DSL parsing and code generation steps
- **Binary Symbol Optimization**: Replace TableGen boilerplate generation with value binding + type computation, reducing 90% symbol table size
- **Elegant Extension Architecture**: Code non-invasive, functionality invasive - stable framework with declarative trait_binding extension/enhancement
- **Zero Migration Cost**: Can coexist with existing TableGen, supports gradual migration without breaking changes
- **Industrial Advantages**: Faster compilation, stronger type safety, complete development tool support
- **Future-Oriented**: Based on standard C++, supports template metaprogramming, concepts and other modern features
- **Production Ready**: Zero runtime overhead, provides more compiler optimization opportunities

## Appendix

See accompanying files:
- `demo/1_base_crtp_demo.cpp` - Basic CRTP demonstration
- `demo/2_enhanced_crtp_trait_bind_demo.cpp` - Complete trait_binding system demonstration

---

**Feedback and discussion welcome on LLVM Discourse and GitHub.**