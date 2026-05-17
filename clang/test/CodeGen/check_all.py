#!/usr/bin/env python3

import os
import subprocess
import sys
from pathlib import Path


def run_test(command, test_num, total_tests):
    """Run a single test and return success status."""
    print(f"\n===========")
    test_id = f"[TEST][{test_num}/{total_tests}]"
    print(f"*** {test_id} ***")
    print(f"Run command: {' '.join(command)}")

    try:
        result = subprocess.run(command, capture_output=True, text=True)

        if result.returncode == 0:
            print(f"*** {test_id} OK ***")
            return True
        else:
            print(f"*** {test_id} ERROR ***")
            print(f"Exit code: {result.returncode}")
            if result.stdout:
                print(f"STDOUT:\n{result.stdout}")
            if result.stderr:
                print(f"STDERR:\n{result.stderr}")
            return False

    except Exception as e:
        print(f"*** {test_id} EXCEPTION ***")
        print(f"Exception: {e}")
        return False


def main():
    # Get build directory from environment variable, default to ./build
    build_dir = os.environ.get('BUILD_DIR', 'build')
    bin_dir = os.path.join(build_dir, 'bin')

    # Check if clang exists
    clang_path = Path.cwd() / bin_dir / 'clang'
    if not clang_path.is_file():
        print(f"[ERROR] Clang not found: {clang_path}")
        print("Set BUILD_DIR environment variable if build is in a different location.")
        return 1

    # Verify llvm-lit exists
    lit_path = Path(bin_dir) / 'llvm-lit'
    if not lit_path.is_file():
        print(f"[ERROR] llvm-lit not found: {lit_path}")
        return 1

    # List of test files to run
    test_dir = "clang/test/CodeGen"
    test_files = [
        "pp-base.c",
        "pp-init.c",
        "pp-linked.c",
        "pp-tagged-generalization.c",
        "pp-tagged-create_spec.c",
        "pp-mm.c",
        "pp-mm-tag.c",
        "pp-spec-ptr.c",
        "pp-spec-base-types.c",
        "pp-mm-3d.c",
        "pp-mm-5d.c",
        "pp-compilation.c",
        "pp-shared-main.c",
        "pp-ext-gvinit-linkage.c",
        "pp-mm-default-eq0.c",
        "pp-mm-default-eq0-perimeter.c"
    ]

    # Convert to full commands
    commands = []
    for test_file in test_files:
        full_path = f"{test_dir}/{test_file}"
        command = [str(lit_path), full_path, "-v"]
        commands.append(command)

    # Run all tests
    total_tests = len(commands)
    failed_tests = 0

    print(f"Starting test suite with {total_tests} tests")
    print(f"Using build directory: {build_dir}")

    for i, cmd in enumerate(commands, 1):
        if not run_test(cmd, i, total_tests):
            failed_tests += 1

            # Check for --fail-fast argument
            if '--fail-fast' in sys.argv:
                print("Fail-fast mode enabled, stopping on first failure")
                break

    # Print summary
    print(f"\n===========")
    print(f"Test suite complete: {total_tests} tests run, {failed_tests} failed")

    return 1 if failed_tests > 0 else 0


if __name__ == "__main__":
    sys.exit(main())
