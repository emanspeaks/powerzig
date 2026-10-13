# PowerZig

Zig compiler builds for 32-bit PowerPC Linux (`powerpc-linux-musleabihf`, `baseline` CPU), such as a G3/G4 Mac running a PowerPC Linux distribution. The binary is statically linked against musl, so it runs regardless of the distribution's libc.

The build is defined in [zig-build](https://codeberg.org/emanspeaks/zig-build); this repo's workflow only runs those scripts on GitHub's runners and publishes the result:

1. Build a stage3 Zig for the runner (`build-stage3.sh`), cached between runs.
2. Download the cross LLVM from [powerzig-bootstrap](https://github.com/emanspeaks/powerzig-bootstrap) whose `llvm_key` matches.
3. Cross-compile Zig with LLVM statically linked (`build-zig-cross.sh`).
4. Smoke-test it under qemu (`test-zig-cross.sh`): `zig version`, then build and run a Zig and a C hello world with the PowerPC Zig itself.
5. Publish the Zig folder and a `manifest.json` as release `vN`.

A run only builds when no existing release has the same `zig_key`, so unchanged inputs never produce duplicate releases.

## Mac OS X on PowerPC

Not supported, and not currently possible: LLVM's PowerPC backend can only write ELF and XCOFF objects (its Mach-O support was removed upstream), Zig has no self-hosted PowerPC backend, and Zig's standard library does not support `powerpc-macos`. To use Zig on a PowerPC Mac, run Linux on it and use the Linux build above.

## Running it locally

On a Linux, macOS or BSD machine with a checkout of zig-build, after building the cross LLVM (see powerzig-bootstrap):

```sh
./build-zig-cross.sh powerpc-linux-musleabihf baseline
./test-zig-cross.sh powerpc-linux-musleabihf baseline   # needs qemu-user-static
```
