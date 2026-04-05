# PowerZig

Cross-compiles the latest stable [Zig](https://ziglang.org) toolchain for **PowerPC 32-bit** via GitHub Actions, then publishes it as a GitHub Release for easy download.

Built for an iBook G3 Snow Clamshell (750fx CPU, 900 MHz) running PowerArch Linux, where native compilation fails due to thermal limits.

## How it works

The [`build-ppc.yml`](.github/workflows/build-ppc.yml) workflow:

1. Resolves the latest stable Zig release (or a version you specify manually).
2. Skips the build entirely if a release for that version already exists.
3. Clones [`zig-bootstrap`](https://github.com/ziglang/zig-bootstrap) at the matching tag and runs `./build powerpc-linux-musleabi baseline`, which cross-compiles LLVM and then Zig for the target.
4. Caches the compiled LLVM output so subsequent runs for the same Zig version only rebuild Zig itself (~30 min vs. 2–4 hours).
5. Publishes a GitHub Release with a `.tar.xz` archive ready to use.

**Target:** `powerpc-linux-musleabi` — fully static musl binary, no glibc version dependency, compatible with any 32-bit big-endian PowerPC including the 750fx (G3). AltiVec is intentionally excluded since the G3 does not support it.

## Schedule

Runs automatically every Sunday at 02:00 UTC. Can also be triggered manually from the **Actions** tab with an optional version override and force-rebuild flag.

## Installing on iBook G3

Find the latest release on the [Releases page](../../releases), then on the iBook:

```bash
wget https://github.com/emanspeaks/powerzig/releases/latest/download/zig-linux-powerpc-VERSION.tar.xz
tar xf zig-linux-powerpc-VERSION.tar.xz
export PATH="$PWD/zig-VERSION-powerpc/bin:$PATH"
zig version
```

Replace `VERSION` with the actual release version (e.g. `0.13.0`). To make the PATH permanent:

```bash
echo 'export PATH="$HOME/zig-VERSION-powerpc/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
```

## First build time

The very first build compiles LLVM from source for PowerPC, which takes **2–4 hours** on a standard GitHub Actions runner (2 cores). The LLVM output is then cached, so future builds for the same Zig version take ~30 minutes.
