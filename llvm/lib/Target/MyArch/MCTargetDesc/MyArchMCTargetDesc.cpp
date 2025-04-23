#include "MCTargetDesc/MyArchInfo.h"
#include "MyArch.h"
#include "MyArchInstPrinter.h"
#include "MyArchMCAsmInfo.h"
#include "TargetInfo/MyArchTargetInfo.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "MyArchGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#include "MyArchGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "MyArchGenSubtargetInfo.inc"

static MCRegisterInfo *createMyArchMCRegisterInfo(const Triple &TT) {
  MYARCH_DUMP_MAGENTA
  MCRegisterInfo *X = new MCRegisterInfo();
  InitMyArchMCRegisterInfo(X, MyArch::X0);
  return X;
}

static MCInstrInfo *createMyArchMCInstrInfo() {
  MYARCH_DUMP_MAGENTA
  MCInstrInfo *X = new MCInstrInfo();
  InitMyArchMCInstrInfo(X);
  return X;
}

static MCSubtargetInfo *createMyArchMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  MYARCH_DUMP_MAGENTA
  return createMyArchMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}

static MCAsmInfo *createMyArchMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT,
                                     const MCTargetOptions &Options) {
  MYARCH_DUMP_MAGENTA
  MCAsmInfo *MAI = new MyArchELFMCAsmInfo(TT);
  unsigned SP = MRI.getDwarfRegNum(MyArch::X1, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

static MCInstPrinter *createMyArchMCInstPrinter(const Triple &T,
                                             unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI,
                                             const MCInstrInfo &MII,
                                             const MCRegisterInfo &MRI) {
  MYARCH_DUMP_MAGENTA
  return new MyArchInstPrinter(MAI, MII, MRI);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMyArchTargetMC() {
  MYARCH_DUMP_MAGENTA
  Target &MyArchTarget = getMyArchTarget();
  RegisterMCAsmInfoFn X(MyArchTarget, createMyArchMCAsmInfo);
  TargetRegistry::RegisterMCRegInfo(MyArchTarget, createMyArchMCRegisterInfo);
  TargetRegistry::RegisterMCInstrInfo(MyArchTarget, createMyArchMCInstrInfo);
  TargetRegistry::RegisterMCSubtargetInfo(MyArchTarget,
	                                             createMyArchMCSubtargetInfo);
  TargetRegistry::RegisterMCInstPrinter(MyArchTarget, createMyArchMCInstPrinter);

}