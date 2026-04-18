#!/usr/bin/env python3
"""Patch Zig's build.zig for a PowerPC-only LLVM build.

Two changes are made:

1. REMOVE non-PowerPC LLVM target backend library entries from the hardcoded
   static library list (llvm_libs / clang_libs / lld_libs arrays).  The cross
   LLVM only contains PowerPC-target objects, so asking the linker to find
   libLLVMAArch64CodeGen.a etc. would fail.

2. ADD a stubs C file to zig_cpp_sources.  Zig's own source (zig_zcu.o) calls
   LLVMInitializeAArch64Target() etc. unconditionally from its Zig-language
   initializeLLVMTarget() function — there are no C #ifdef guards here.
   We provide empty stub implementations that satisfy the linker without
   providing any real backend functionality.  The resulting PowerPC Zig binary
   simply cannot generate code for non-PowerPC targets, which is intentional.

Usage: patch-build-zig-ppc-only.py <path/to/build.zig> <path/to/stubs.c>
"""
import os
import re
import sys

NON_PPC_TARGETS = [
    'AArch64', 'AMDGPU', 'ARM', 'AVR', 'BPF', 'Hexagon',
    'Lanai', 'LoongArch', 'Mips', 'MSP430', 'NVPTX',
    'RISCV', 'Sparc', 'SPIRV', 'SystemZ', 'VE',
    'WebAssembly', 'X86', 'XCore',
]

# Relative path from bootstrap/zig/ (where build.zig lives) to the stubs file
# at .github/stubs/llvm-target-stubs.c in the repo root.
STUBS_RELATIVE = '../../.github/stubs/llvm-target-stubs.c'

# The last entry in zig_cpp_sources that we insert our stubs file after.
LAST_CPP_SOURCE = '"src/zig_clang_cc1as_main.cpp",'


def remove_non_ppc_libs(lines):
    pattern = re.compile(
        r'"LLVM(' + '|'.join(NON_PPC_TARGETS) + r')[A-Za-z0-9_]*"'
    )
    kept, removed = [], []
    for line in lines:
        if pattern.search(line):
            removed.append(line.rstrip())
        else:
            kept.append(line)
    return kept, removed


def inject_stubs(lines, stubs_path):
    """Insert the stubs file into zig_cpp_sources after the last known entry."""
    # Determine the path to use in the source: prefer a relative path (cleaner),
    # fall back to the absolute path passed on the command line.
    inject_path = STUBS_RELATIVE

    new_lines = []
    injected = False
    for line in lines:
        new_lines.append(line)
        if not injected and LAST_CPP_SOURCE in line:
            # Preserve indentation of the existing entry.
            indent = len(line) - len(line.lstrip())
            new_lines.append(' ' * indent + f'"{inject_path}",\n')
            injected = True
    return new_lines, injected


def main():
    if len(sys.argv) < 3:
        print(f'Usage: {sys.argv[0]} <path/to/build.zig> <path/to/stubs.c>')
        sys.exit(1)

    build_zig = sys.argv[1]
    stubs_c = sys.argv[2]

    with open(build_zig) as f:
        lines = f.readlines()

    # --- Step 1: remove non-PowerPC library entries ---
    lines, removed = remove_non_ppc_libs(lines)
    if not removed:
        print(f'WARNING: no non-PowerPC LLVM target libs found in {build_zig}')
        print('The hardcoded list format may have changed — manual review needed.')
        sys.exit(1)
    print(f'Removed {len(removed)} non-PowerPC target library entries:')
    for line in removed[:10]:
        print(f'  {line}')
    if len(removed) > 10:
        print(f'  ...and {len(removed) - 10} more')

    # --- Step 2: inject stubs file into zig_cpp_sources ---
    lines, injected = inject_stubs(lines, stubs_c)
    if not injected:
        print(f'WARNING: could not find insertion point "{LAST_CPP_SOURCE}" in {build_zig}')
        print('The zig_cpp_sources array format may have changed — manual review needed.')
        sys.exit(1)
    print(f'\nInjected stubs file: {STUBS_RELATIVE}')

    with open(build_zig, 'w') as f:
        f.writelines(lines)

    print(f'Done. Patched {build_zig}')


if __name__ == '__main__':
    main()
