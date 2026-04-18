#!/usr/bin/env python3
"""Remove non-PowerPC LLVM target backend libraries from Zig's build.zig.

When cross-compiling Zig with a PowerPC-only LLVM build, the hardcoded
static library list in build.zig references all 20 LLVM target backends.
This script strips the 19 non-PowerPC entries so the linker only looks
for libraries that actually exist in the cross LLVM install.

The C++ bridge source files are compiled using the cross LLVM's include
directory (via --search-prefix), so llvm/Config/llvm-config.h has only
LLVM_HAS_POWERPC_TARGET defined, and #ifdef guards in Zig's C++ code
prevent any non-PowerPC target initialization from being compiled in.
Removing the corresponding link entries therefore causes no undefined
symbol errors.

Usage: patch-build-zig-ppc-only.py <path/to/build.zig>
"""
import re
import sys

NON_PPC_TARGETS = [
    'AArch64', 'AMDGPU', 'ARM', 'AVR', 'BPF', 'Hexagon',
    'Lanai', 'LoongArch', 'Mips', 'MSP430', 'NVPTX',
    'RISCV', 'Sparc', 'SPIRV', 'SystemZ', 'VE',
    'WebAssembly', 'X86', 'XCore',
]

def main():
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} <path/to/build.zig>')
        sys.exit(1)

    path = sys.argv[1]
    pattern = re.compile(
        r'"LLVM(' + '|'.join(NON_PPC_TARGETS) + r')[A-Za-z0-9_]*"'
    )

    with open(path) as f:
        lines = f.readlines()

    kept, removed = [], []
    for line in lines:
        if pattern.search(line):
            removed.append(line.rstrip())
        else:
            kept.append(line)

    if not removed:
        print(f'WARNING: no non-PowerPC LLVM target libs found in {path}')
        print('The hardcoded list format may have changed — manual review needed.')
        sys.exit(1)

    print(f'Removed {len(removed)} non-PowerPC target library entries:')
    for line in removed[:10]:
        print(f'  {line}')
    if len(removed) > 10:
        print(f'  ...and {len(removed) - 10} more')

    with open(path, 'w') as f:
        f.writelines(kept)

    print(f'\nDone. Patched {path}')

if __name__ == '__main__':
    main()
