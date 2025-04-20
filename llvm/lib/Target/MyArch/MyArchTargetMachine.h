#ifndef LLVM_LIB_TARGET_MYARCH_MYARCHTARGETMACHINE_H
#define LLVM_LIB_TARGET_MYARCH_MYARCHTARGETMACHINE_H

#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include <optional>

namespace llvm {
extern Target MyArchTarget;

class MyArchTargetMachine : public CodeGenTargetMachineImpl {
public:
  MyArchTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, const TargetOptions &Options,
                   std::optional<Reloc::Model> RM,
                   std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                   bool JIT);
};
} // end namespace llvm

#endif // LLVM_LIB_TARGET_SIM_SIMTARGETMACHINE_H
