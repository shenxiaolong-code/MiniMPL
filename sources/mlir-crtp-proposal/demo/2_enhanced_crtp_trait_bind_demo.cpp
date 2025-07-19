#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <2_enhanced_crtp_trait_bind.hpp>
#include <mpl_api.hpp>
#include <MiniMPL/macro_assert.h>

// ================== FRAMEWORK BASE (Framework Base Section) ==================
// This part is the core of CRTP + trait_binding framework, usually users don't need to modify

using namespace mlir_crtp;
// ================== USER EXPAND (User Extension Section) ==================
// Divided into two usage patterns: default trait_binding and user-replaced trait_binding

// ================== Operation Implementations ==================

// ========== Part 1: Users don't provide trait_binding (use default) ==========
// Part 1 demonstration: using default trait_binding (DefaultTrait)
class SimpleOp;
class CustomOp;
// SimpleOp and CustomOp have no specialization (trait_binding), use default DefaultTrait

// 1. SimpleOp - doesn't provide trait_binding, automatically uses DefaultTrait
class SimpleOp : public Op<SimpleOp> {
    Value data_;
    
public:
    SimpleOp(Value val) : data_(val) {}
    
    // Only need to implement basic methods, automatically get DefaultTrait capabilities
    Value default_getInput() { return data_; }
    Value default_getOutput() { return data_; }
    std::string default_getOpName() { return "simple"; }
    
    void default_print() { 
        std::cout << "simple(" << data_ << ")"; 
    }
};

// 5. CustomOp - uses DefaultTrait (no special binding)
class CustomOp : public Op<CustomOp> {
    Value data_;
    
public:
    CustomOp(Value data) : data_(data) {}
    
    Value getOperand(int /* index */) { return data_; }
    Value getResult(int /* index */) { return data_ * 2; }
    
    Value default_getInput() { return data_; }
    Value default_getOutput() { return data_ * 2; }
    std::string default_getOpName() { return "custom"; }
    
    void default_print() { 
        std::cout << "custom(" << data_ << ") -> " << (data_ * 2); 
    }
};

// ========== Part 2: Users define custom traits and replace default trait_binding ==========
// Part 2 demonstration: users provide custom trait_binding to replace default implementation
// Users define their own traits, then replace default behavior through trait_binding specialization

// ========== Part 2-0: Forward declarations or definitions: user-defined traits in user scope or framework-provided trait declarations ==========
// 1. Arithmetic Trait - arithmetic operation trait
template<typename Op>
class ArithmeticTrait {
public:
    bool isCommutative() { return true; }
    bool isAssociative() { return true; }
    
    Value fold() {
        auto* op = static_cast<Op*>(this);
        return op->getOperand(0) + op->getOperand(1); // Simple constant folding
    }
    
    std::string getTraitName() { return "Arithmetic"; }
};

// 2. Memory Trait - memory operation trait
template<typename Op>
class MemoryTrait {
public:
    bool hasSideEffects() { return true; }
    bool canSpeculate() { return false; }
    
    std::vector<Value> getMemorySlots() {
        auto* op = static_cast<Op*>(this);
        return {op->getOperand(0)}; // Memory address
    }
    
    std::string getTraitName() { return "Memory"; }
};

// 3. Control Flow Trait - control flow trait
template<typename Op>  
class ControlFlowTrait {
public:
    bool isTerminator() { return true; }
    bool hasSuccessors() { return true; }
    
    std::vector<Value> getSuccessors() {
        auto* op = static_cast<Op*>(this);
        return {op->getOperand(0), op->getOperand(1)}; // Branch targets
    }
    
    std::string getTraitName() { return "ControlFlow"; }
};

// 4. Pure Function Trait - pure function trait
template<typename Op>
class PureTrait {
public:
    bool hasSideEffects() { return false; }
    bool canSpeculate() { return true; }
    bool isIdempotent() { return true; }
    
    std::string getTraitName() { return "Pure"; }
};

// ========== Part 2-1 Implementation: user-set trait_binding ==========
class AddOp;
class LoadOp; 
class BranchOp;
class ConstOp;

// Users replace default DefaultTrait through trait_binding specialization, non-code-invasive feature addition or modification
// (These trait_bindings should be close to user-defined OPs, but placed together here for demonstration)
template<> struct trait_binding<AddOp> : Type2Type<ArithmeticTrait<AddOp>> {};
template<> struct trait_binding<LoadOp> : Type2Type<MemoryTrait<LoadOp>> {};
template<> struct trait_binding<BranchOp> : Type2Type<ControlFlowTrait<BranchOp>> {};
template<> struct trait_binding<ConstOp> : Type2Type<PureTrait<ConstOp>> {};

// 2. AddOp - user specializes trait_binding, gets ArithmeticTrait
class AddOp : public Op<AddOp> {
    Value lhs_, rhs_;
    
public:
    AddOp(Value lhs, Value rhs) : lhs_(lhs), rhs_(rhs) {}
    
    Value getOperand(int index) { return index == 0 ? lhs_ : rhs_; }
    Value getResult(int /* index */) { return lhs_ + rhs_; }
    
    // Override defaults
    Value default_getInput() { return lhs_; }
    Value default_getOutput() { return getResult(0); }
    std::string default_getOpName() { return "add"; }
    
    void default_print() { 
        std::cout << "add(" << lhs_ << ", " << rhs_ << ") -> " << getResult(0); 
    }
    
    // AddOp-specific methods
    Value getLHS() const { return lhs_; }
    Value getRHS() const { return rhs_; }
};

// 2. LoadOp - automatically gets MemoryTrait  
class LoadOp : public Op<LoadOp> {
    Value address_;
    Value loaded_value_;
    
public:
    LoadOp(Value addr, Value val) : address_(addr), loaded_value_(val) {}
    
    Value getOperand(int /* index */) { return address_; }
    Value getResult(int /* index */) { return loaded_value_; }
    
    Value default_getInput() { return address_; }
    Value default_getOutput() { return loaded_value_; }
    std::string default_getOpName() { return "load"; }
    
    void default_print() { 
        std::cout << "load(" << address_ << ") -> " << loaded_value_; 
    }
    
    Value getAddress() const { return address_; }
};

// 3. BranchOp - automatically gets ControlFlowTrait
class BranchOp : public Op<BranchOp> {
    Value condition_;
    Value true_target_, false_target_;
    
public:
    BranchOp(Value cond, Value t_target, Value f_target) 
        : condition_(cond), true_target_(t_target), false_target_(f_target) {}
    
    Value getOperand(int index) { 
        return index == 0 ? condition_ : (index == 1 ? true_target_ : false_target_); 
    }
    Value getResult(int /* index */) { return 0; } // Branches don't produce values
    
    Value default_getInput() { return condition_; }
    Value default_getOutput() { return 0; }
    std::string default_getOpName() { return "branch"; }
    
    void default_print() { 
        std::cout << "branch(" << condition_ << " ? " << true_target_ << " : " << false_target_ << ")"; 
    }
};

// 4. ConstOp - automatically gets PureTrait
class ConstOp : public Op<ConstOp> {
    Value value_;
    
public:
    ConstOp(Value val) : value_(val) {}
    
    Value getOperand(int /* index */) { return 0; } // No operands
    Value getResult(int /* index */) { return value_; }
    
    Value default_getInput() { return 0; }
    Value default_getOutput() { return value_; }
    std::string default_getOpName() { return "const"; }
    
    void default_print() { 
        std::cout << "const(" << value_ << ")"; 
    }
    
    Value getValue() const { return value_; }
};

// ================== Advanced Trait Composition ==================

// Multiple trait support through CRTP composition
template<typename Op>
class CompositeArithmeticMemoryTrait : public ArithmeticTrait<Op>, public MemoryTrait<Op> {
public:
    std::string getTraitName() { return "ArithmeticMemory"; }
    
    // Combine arithmetic and memory capabilities
    bool isArithmeticMemoryOp() { return true; }
    
    LogicalResult verifyArithmeticMemory() {
        // Custom verification combining both traits
        // auto* op = static_cast<Op*>(this);
        return ArithmeticTrait<Op>::isCommutative() && !MemoryTrait<Op>::canSpeculate() 
               ? success() : failure();
    }
};

// Specialized operation with composite trait
class AtomicAddOp;
template<> struct trait_binding<AtomicAddOp> : Type2Type<CompositeArithmeticMemoryTrait<AtomicAddOp>> {};

class AtomicAddOp : public Op<AtomicAddOp> {
    Value address_, increment_;
    
public:
    AtomicAddOp(Value addr, Value inc) : address_(addr), increment_(inc) {}
    
    Value getOperand(int index) { return index == 0 ? address_ : increment_; }
    Value getResult(int /* index */) { return address_ + increment_; }
    
    Value default_getInput() { return address_; }
    Value default_getOutput() { return address_ + increment_; }
    std::string default_getOpName() { return "atomic_add"; }
    
    void default_print() { 
        std::cout << "atomic_add(" << address_ << ", " << increment_ << ")"; 
    }
};

// ================== Demonstration Functions ==================

// Trait-specific demonstration functions using elegant array-based SFINAE
template<typename OpType>
void demonstrateSpecificTrait(OpType& op, ENABLEFUNC_IF((std::is_same_v<typename OpType::TraitType, ArithmeticTrait<OpType>>))) {
    auto* trait = op.getTrait();
    std::cout << "✓ Arithmetic Trait:\n";
    std::cout << "  - Commutative: " << (trait->isCommutative() ? "true" : "false") << "\n";
    std::cout << "  - Associative: " << (trait->isAssociative() ? "true" : "false") << "\n";
    std::cout << "  - Folded Value: " << trait->fold() << "\n";
}

template<typename OpType>
void demonstrateSpecificTrait(OpType& op, ENABLEFUNC_IF((std::is_same_v<typename OpType::TraitType, MemoryTrait<OpType>>))) {
    auto* trait = op.getTrait();
    std::cout << "✓ Memory Trait:\n";
    std::cout << "  - Has Side Effects: " << (trait->hasSideEffects() ? "true" : "false") << "\n";
    std::cout << "  - Can Speculate: " << (trait->canSpeculate() ? "true" : "false") << "\n";
    auto slots = trait->getMemorySlots();
    std::cout << "  - Memory Slots: [";
    for (auto slot : slots) std::cout << slot << " ";
    std::cout << "]\n";
}

template<typename OpType>
void demonstrateSpecificTrait(OpType& op, ENABLEFUNC_IF((std::is_same_v<typename OpType::TraitType, ControlFlowTrait<OpType>>))) {
    auto* trait = op.getTrait();
    std::cout << "✓ Control Flow Trait:\n";
    std::cout << "  - Is Terminator: " << (trait->isTerminator() ? "true" : "false") << "\n";
    std::cout << "  - Has Successors: " << (trait->hasSuccessors() ? "true" : "false") << "\n";
    auto successors = trait->getSuccessors();
    std::cout << "  - Successors: [";
    for (auto succ : successors) std::cout << succ << " ";
    std::cout << "]\n";
}

template<typename OpType>
void demonstrateSpecificTrait(OpType& op, ENABLEFUNC_IF((std::is_same_v<typename OpType::TraitType, PureTrait<OpType>>))) {
    auto* trait = op.getTrait();
    std::cout << "✓ Pure Trait:\n";
    std::cout << "  - Has Side Effects: " << (trait->hasSideEffects() ? "true" : "false") << "\n";
    std::cout << "  - Can Speculate: " << (trait->canSpeculate() ? "true" : "false") << "\n";
    std::cout << "  - Is Idempotent: " << (trait->isIdempotent() ? "true" : "false") << "\n";
}

template<typename OpType>
void demonstrateSpecificTrait(OpType& op, ENABLEFUNC_IF((std::is_same_v<typename OpType::TraitType, DefaultTrait<OpType>>))) {
    auto* trait = op.getTrait();
    std::cout << "✓ Default Trait:\n";
    std::cout << "  - Trait Name: " << trait->getTraitName() << "\n";
    std::cout << "  - Basic functionality only" << "\n";
}

template<typename OpType>
void demonstrateTraitCapabilities(OpType& op) {
    std::cout << "\n=== " << op.getOpName() << " Operation Analysis ===\n";
    std::cout << "Trait Info: " << op.getTraitInfo() << "\n";
    std::cout << "Print: "; op.print(); std::cout << "\n";
    std::cout << "Input: " << op.getInput() << ", Output: " << op.getOutput() << "\n";
    
    // Use SFINAE-based function overloading to call the correct trait-specific function
    demonstrateSpecificTrait(op);
}

void demonstrateCompositeTraits() {
    std::cout << "\n\n=== Composite Trait Demonstration ===\n";
    
    AtomicAddOp atomic_add(100, 5);
    std::cout << "Trait Info: " << atomic_add.getTraitInfo() << "\n";
    std::cout << "Print: "; atomic_add.print(); std::cout << "\n";
    
    // Access both arithmetic and memory capabilities
    auto* trait = atomic_add.getTrait();
    std::cout << "✓ Composite ArithmeticMemory Trait:\n";
    std::cout << "  - Is Arithmetic+Memory Op: " << (trait->isArithmeticMemoryOp() ? "true" : "false") << "\n";
    std::cout << "  - Commutative (Arith): " << (trait->ArithmeticTrait<AtomicAddOp>::isCommutative() ? "true" : "false") << "\n";
    std::cout << "  - Has Side Effects (Mem): " << (trait->MemoryTrait<AtomicAddOp>::hasSideEffects() ? "true" : "false") << "\n";
    std::cout << "  - Combined Verification: " << (trait->verifyArithmeticMemory() ? "✓" : "✗") << "\n";
}

int main() {
    std::cout << "======= Enhanced CRTP + trait_binding System Demo =======" << std::endl;
    std::cout << "Demonstrates two usage patterns: default trait_binding and user-replaced trait_binding\n\n";
    
    std::cout << "=== Part 1: Using default trait_binding (DefaultTrait) ===\n";
    std::cout << "Users don't need to provide trait_binding specialization, automatically uses framework's default DefaultTrait\n";
    
    SimpleOp simple(42);         // -> DefaultTrait (no specialization)
    CustomOp custom(50);         // -> DefaultTrait (no specialization)
    
    demonstrateTraitCapabilities(simple);
    demonstrateTraitCapabilities(custom);
    
    std::cout << "\n=== Part 2: User-replaced trait_binding ===\n";
    std::cout << "Users replace default behavior through trait_binding specialization, gaining specialized trait capabilities\n";
    
    AddOp add(10, 20);           // -> ArithmeticTrait (user specialization)
    LoadOp load(0x1000, 42);     // -> MemoryTrait (user specialization)
    BranchOp branch(1, 100, 200); // -> ControlFlowTrait (user specialization)
    ConstOp const_val(123);      // -> PureTrait (user specialization)
    
    demonstrateTraitCapabilities(add);
    demonstrateTraitCapabilities(load);
    demonstrateTraitCapabilities(branch);
    demonstrateTraitCapabilities(const_val);
    
    // Part 3: Advanced composite traits
    demonstrateCompositeTraits();
    
    std::cout << "\n=== Trait Binding System Summary ===\n";
    std::cout << "🔧 Default mode: No configuration needed, directly uses DefaultTrait\n";
    std::cout << "🚀 Replacement mode: Users specialize trait_binding, gain specialized capabilities\n";
    std::cout << "💡 Key advantage: Code non-invasive + functionality invasive\n";
    std::cout << "✅ Framework code never modified, user gains unlimited extension power!\n";
    
    return 0;
} 