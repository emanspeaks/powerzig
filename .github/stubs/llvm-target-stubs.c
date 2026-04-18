/*
 * Empty stub implementations for LLVM target initialization functions that are
 * absent from a PowerPC-only LLVM build.
 *
 * Zig's codegen/llvm.zig calls LLVMInitialize*() for every target it knows
 * about inside initializeLLVMTarget().  Because the Zig source is compiled
 * unconditionally (no C #ifdef guards), all symbols must be resolvable at link
 * time even when those LLVM backends were not compiled in.
 *
 * These stubs satisfy the linker.  The PowerPC Zig binary will call them for
 * non-PowerPC targets and silently do nothing, meaning it cannot generate code
 * for those targets — which is the intended behaviour for a PowerPC-only build.
 */

/* AArch64 */
void LLVMInitializeAArch64Target(void) {}
void LLVMInitializeAArch64TargetInfo(void) {}
void LLVMInitializeAArch64TargetMC(void) {}
void LLVMInitializeAArch64AsmPrinter(void) {}
void LLVMInitializeAArch64AsmParser(void) {}
void LLVMInitializeAArch64Disassembler(void) {}

/* AMDGPU */
void LLVMInitializeAMDGPUTarget(void) {}
void LLVMInitializeAMDGPUTargetInfo(void) {}
void LLVMInitializeAMDGPUTargetMC(void) {}
void LLVMInitializeAMDGPUAsmPrinter(void) {}
void LLVMInitializeAMDGPUAsmParser(void) {}
void LLVMInitializeAMDGPUDisassembler(void) {}

/* ARM */
void LLVMInitializeARMTarget(void) {}
void LLVMInitializeARMTargetInfo(void) {}
void LLVMInitializeARMTargetMC(void) {}
void LLVMInitializeARMAsmPrinter(void) {}
void LLVMInitializeARMAsmParser(void) {}
void LLVMInitializeARMDisassembler(void) {}

/* AVR */
void LLVMInitializeAVRTarget(void) {}
void LLVMInitializeAVRTargetInfo(void) {}
void LLVMInitializeAVRTargetMC(void) {}
void LLVMInitializeAVRAsmPrinter(void) {}
void LLVMInitializeAVRAsmParser(void) {}
void LLVMInitializeAVRDisassembler(void) {}

/* BPF */
void LLVMInitializeBPFTarget(void) {}
void LLVMInitializeBPFTargetInfo(void) {}
void LLVMInitializeBPFTargetMC(void) {}
void LLVMInitializeBPFAsmPrinter(void) {}
void LLVMInitializeBPFAsmParser(void) {}
void LLVMInitializeBPFDisassembler(void) {}

/* Hexagon */
void LLVMInitializeHexagonTarget(void) {}
void LLVMInitializeHexagonTargetInfo(void) {}
void LLVMInitializeHexagonTargetMC(void) {}
void LLVMInitializeHexagonAsmPrinter(void) {}
void LLVMInitializeHexagonAsmParser(void) {}
void LLVMInitializeHexagonDisassembler(void) {}

/* Lanai */
void LLVMInitializeLanaiTarget(void) {}
void LLVMInitializeLanaiTargetInfo(void) {}
void LLVMInitializeLanaiTargetMC(void) {}
void LLVMInitializeLanaiAsmPrinter(void) {}
void LLVMInitializeLanaiAsmParser(void) {}
void LLVMInitializeLanaiDisassembler(void) {}

/* LoongArch */
void LLVMInitializeLoongArchTarget(void) {}
void LLVMInitializeLoongArchTargetInfo(void) {}
void LLVMInitializeLoongArchTargetMC(void) {}
void LLVMInitializeLoongArchAsmPrinter(void) {}
void LLVMInitializeLoongArchAsmParser(void) {}
void LLVMInitializeLoongArchDisassembler(void) {}

/* Mips */
void LLVMInitializeMipsTarget(void) {}
void LLVMInitializeMipsTargetInfo(void) {}
void LLVMInitializeMipsTargetMC(void) {}
void LLVMInitializeMipsAsmPrinter(void) {}
void LLVMInitializeMipsAsmParser(void) {}
void LLVMInitializeMipsDisassembler(void) {}

/* MSP430 */
void LLVMInitializeMSP430Target(void) {}
void LLVMInitializeMSP430TargetInfo(void) {}
void LLVMInitializeMSP430TargetMC(void) {}
void LLVMInitializeMSP430AsmPrinter(void) {}
void LLVMInitializeMSP430AsmParser(void) {}
void LLVMInitializeMSP430Disassembler(void) {}

/* NVPTX (no AsmParser or Disassembler in LLVM's public C API) */
void LLVMInitializeNVPTXTarget(void) {}
void LLVMInitializeNVPTXTargetInfo(void) {}
void LLVMInitializeNVPTXTargetMC(void) {}
void LLVMInitializeNVPTXAsmPrinter(void) {}

/* RISCV */
void LLVMInitializeRISCVTarget(void) {}
void LLVMInitializeRISCVTargetInfo(void) {}
void LLVMInitializeRISCVTargetMC(void) {}
void LLVMInitializeRISCVAsmPrinter(void) {}
void LLVMInitializeRISCVAsmParser(void) {}
void LLVMInitializeRISCVDisassembler(void) {}

/* Sparc */
void LLVMInitializeSparcTarget(void) {}
void LLVMInitializeSparcTargetInfo(void) {}
void LLVMInitializeSparcTargetMC(void) {}
void LLVMInitializeSparcAsmPrinter(void) {}
void LLVMInitializeSparcAsmParser(void) {}
void LLVMInitializeSparcDisassembler(void) {}

/* SPIRV (no AsmParser or Disassembler in LLVM's public C API) */
void LLVMInitializeSPIRVTarget(void) {}
void LLVMInitializeSPIRVTargetInfo(void) {}
void LLVMInitializeSPIRVTargetMC(void) {}
void LLVMInitializeSPIRVAsmPrinter(void) {}

/* SystemZ */
void LLVMInitializeSystemZTarget(void) {}
void LLVMInitializeSystemZTargetInfo(void) {}
void LLVMInitializeSystemZTargetMC(void) {}
void LLVMInitializeSystemZAsmPrinter(void) {}
void LLVMInitializeSystemZAsmParser(void) {}
void LLVMInitializeSystemZDisassembler(void) {}

/* VE */
void LLVMInitializeVETarget(void) {}
void LLVMInitializeVETargetInfo(void) {}
void LLVMInitializeVETargetMC(void) {}
void LLVMInitializeVEAsmPrinter(void) {}
void LLVMInitializeVEAsmParser(void) {}
void LLVMInitializeVEDisassembler(void) {}

/* WebAssembly */
void LLVMInitializeWebAssemblyTarget(void) {}
void LLVMInitializeWebAssemblyTargetInfo(void) {}
void LLVMInitializeWebAssemblyTargetMC(void) {}
void LLVMInitializeWebAssemblyAsmPrinter(void) {}
void LLVMInitializeWebAssemblyAsmParser(void) {}
void LLVMInitializeWebAssemblyDisassembler(void) {}

/* X86 */
void LLVMInitializeX86Target(void) {}
void LLVMInitializeX86TargetInfo(void) {}
void LLVMInitializeX86TargetMC(void) {}
void LLVMInitializeX86AsmPrinter(void) {}
void LLVMInitializeX86AsmParser(void) {}
void LLVMInitializeX86Disassembler(void) {}

/* XCore (no AsmParser or Disassembler in LLVM's public C API) */
void LLVMInitializeXCoreTarget(void) {}
void LLVMInitializeXCoreTargetInfo(void) {}
void LLVMInitializeXCoreTargetMC(void) {}
void LLVMInitializeXCoreAsmPrinter(void) {}
