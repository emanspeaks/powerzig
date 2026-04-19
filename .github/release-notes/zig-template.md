Zig compiler cross-compiled for `$ZIG_TARGET`.

| Field | Value |
|---|---|
| Release tag | `$RELEASE_TAG` |
| Zig version | `$ZIG_VERSION` |
| Target | `$ZIG_TARGET` |
| CPU | `$ZIG_CPU` |
| LLVM artifact | `$LLVM_TAG` (from [powerzig-bootstrap $LLVM_TAG](https://github.com/$LLVM_REPO/releases/tag/$LLVM_TAG)) |
| zig-bootstrap commit | `$BOOTSTRAP_COMMIT` |

**Files:**
- `$ARCHIVE` — flat layout for `$ZIG_TARGET`: `zig` binary + `lib/` stdlib
