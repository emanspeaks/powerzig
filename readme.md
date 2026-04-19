# powerzig

Produces a Zig compiler binary that runs on **PowerPC 32-bit**
(`powerpc-linux-musleabihf`).

## What this repo does

Downloads pre-built LLVM artifacts from
[emanspeaks/powerzig-bootstrap](https://github.com/emanspeaks/powerzig-bootstrap)
and runs a standard `zig build -Dstatic-llvm` cross-compilation targeting
`powerpc-linux-musleabihf`.

The result is a self-contained `zig` binary + stdlib that can run on a
32-bit big-endian PowerPC Linux system.

## What this repo does NOT do

This repo does **not** build LLVM. That multi-hour step is handled upstream in
[emanspeaks/powerzig-bootstrap](https://github.com/emanspeaks/powerzig-bootstrap),
which publishes the LLVM artifacts as GitHub Releases.

## Relationship to powerzig-bootstrap

```
powerzig-bootstrap
  ├── Builds host LLVM + host Zig       ← build-time tools only
  └── Builds cross LLVM (all 20 targets, cross-compiled for powerpc32)
          │
          │  releases: llvm-host-zig.tar.xz
          │            llvm-cross-powerpc32.tar.xz
          ▼
powerzig
  └── zig build -Dstatic-llvm           ← links cross LLVM into zig binary
          │
          ▼
      zig-powerpc-linux-musleabihf-vN.tar.xz
```

## Releases

Releases are tagged `v1`, `v2`, … and contain a single tarball:

```
zig-powerpc-linux-musleabihf-vN.tar.xz   # bin/zig  +  lib/zig/ stdlib
```

A new release is created automatically whenever `powerzig-bootstrap` publishes
a new LLVM artifact release.
