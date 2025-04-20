#include "TargetInfo/MyArchTargetInfo.h"
#include "MyArch.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getMyArchTarget() {
  MYARCH_DUMP_YELLOW
  static Target MyArchTarget;
  return MyArchTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMyArchTargetInfo() {
  MYARCH_DUMP_YELLOW
  RegisterTarget<Triple::my_arch> X(getMyArchTarget(), "MyArch",
                                "Simulator target for LLVM course", "MYARCH");
}
