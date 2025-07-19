#include <iostream>
#include <string>
#include <type_traits>

// =================== Part 1: Framework Base ===================
// Simulated MLIR Type/Value
struct Type { std::string name; };
struct Value { Type type; std::string name; };

template<typename Derived>
class OpBase {
private:
    Derived* derived() { return static_cast<Derived*>(this); }

public:
    // Unified interface methods - always delegate to derived
    auto getInput() { return derived()->default_getInput(); }
    std::string getOperationName() { return derived()->default_getOperationName(); }
    bool verify() { return derived()->default_verify(); }
    void print() { derived()->default_print(); }
    
    // Default implementations - derived classes can selectively override
    auto default_getInput() {
        std::cout << "Using default input access" << std::endl;
        return Value{Type{"unknown"}, "default_input"}; 
    }
    
    std::string default_getOperationName() {
        std::cout << "Using default operation name" << std::endl;
        return "generic_op";
    }
    
    bool default_verify() {
        std::cout << "Using default verification" << std::endl;
        return true;
    }
    
    void default_print() {
        std::cout << "Op: " << getOperationName() << " (default print)" << std::endl;
    }
};

// =================== Part 3: Advanced Features ===================

// Binary operation kinds
enum class BinaryOpKind { Add, Sub, Mul };

// Template specialization - more elegant than if constexpr
template<BinaryOpKind Kind> struct BinaryOpTraits;
template<> struct BinaryOpTraits<BinaryOpKind::Add> { 
    static constexpr const char* name = "add"; 
    static constexpr bool commutative = true;
};
template<> struct BinaryOpTraits<BinaryOpKind::Sub> { 
    static constexpr const char* name = "sub"; 
    static constexpr bool commutative = false;
};
template<> struct BinaryOpTraits<BinaryOpKind::Mul> { 
    static constexpr const char* name = "mul"; 
    static constexpr bool commutative = true;
};

// Template operation with compile-time polymorphism
template<BinaryOpKind Kind>
class BinaryOp : public OpBase<BinaryOp<Kind>> {
public:
    std::string default_getOperationName() {
        std::cout << "BinaryOp: Template-based operation name" << std::endl;
        return BinaryOpTraits<Kind>::name;
    }
    
    bool default_verify() {
        std::cout << "BinaryOp: Validating " << BinaryOpTraits<Kind>::name 
                  << " (commutative: " << BinaryOpTraits<Kind>::commutative << ")" << std::endl;
        return true;
    }
    
    void demo() {
        std::cout << "\n=== BinaryOp<" << BinaryOpTraits<Kind>::name << "> ===" << std::endl;
        this->getInput();
        std::cout << "Operation: " << this->getOperationName() << std::endl;
        std::cout << "Valid: " << this->verify() << std::endl;
        this->print();
    }
};


// ================== Comparison Summary ==================

/*
TableGen Approach:
------------------
def IdentityOp : Op<"identity"> {
  let arguments = (ins AnyType:$input);
  let results = (outs AnyType:$output);
  let hasVerifier = 1;
  let extraClassDefinition = [{
    LogicalResult verify() {
      return getInput().getType() == getOutput().getType() ? success() : failure();
    }
  }];
}
// Generates ~200 lines of C++ code

CRTP Approach:
--------------
class IdentityOp : public Op<IdentityOp> {
    LogicalResult default_verify() {
        return (getInput() == getOutput()) ? success() : failure();
    }
    // ~15 lines total, direct C++ code
}

Result: Same functionality, 90% less code, 100% more flexibility!
*/ 