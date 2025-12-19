# Grading script for the organize_files.sh program
import filecmp
import inspect
import os
from pathlib import Path
import random
import shutil
import subprocess
import sys
import zipfile

# Size constants
TINY_MAX = 1024      # 1KB
SMALL_MAX = 10240    # 10KB
MEDIUM_MAX = 102400    # 100KB
LARGE_MAX = 1048576 # 1MB

# Return codes
RC_SUCCESS = 0
RC_INVALID_ARG = 1
RC_SOURCE_INVALID = 2
RC_DEST_INVALID = 3
RC_GENERAL_ERROR = 99

# Other constants
SUT = "organize_files.sh"
DEBUG = True
SUT_TIMEOUT_SEC = 60

# Global variables
g_test_count = 0
g_test_failures = 0

g_random_id = random.randint(10000, 99999)
g_tmp_folder = f"/tmp/{g_random_id}_organize_files_grader"
g_zip_file = None

# Utility functions

def assert_child_of(name, parent, child):
    parent_abs = parent.resolve()
    child_abs = child.resolve()

    try:
        # Use relative_to() to see if child is under parent
        child_abs.relative_to(parent_abs)
        test_pass(f"{name}:assert_child_of")
    except ValueError:
        test_fail_simple(f"{name}:assert_child_of:{parent_abs}:{child_abs}")


def assert_dir_exists(name, path):
    if not path.is_dir():
        test_fail_simple(f"{name}:assert_dir_exists:{path}")
    else:
        test_pass(f"{name}:assert_dir_exists")

def assert_file_exists(name, path):
    if not path.is_file():
        test_fail_simple(f"{name}:assert_file_exists:{path}")
    else:
        test_pass(f"{name}:assert_file_exists")

def assert_samefile(name, path1, path2):
    if not path1.samefile(path2):
        test_fail_simple(f"{name}:assert_samefile:{path1}:{path2}")
    else:
        test_pass(f"{name}:assert_samefile")

def assert_symlink_exists(name, path):
    if not path.is_symlink():
        test_fail_simple(f"{name}:assert_symlink_exists:{path}")
    else:
        test_pass(f"{name}:assert_symlink_exists")

def assert_path_not_exists(name, path):
    if path.exists():
        test_fail_simple(f"{name}:assert_path_not_exists:{path}")
    else:
        test_pass(f"{name}:assert_path_not_exists")

def debug(msg):
    if DEBUG:
        print("DEBUG:", msg, file=sys.stderr)

def ensure_exact_trees(dir1_path, dir2_path):
    errors_found = False

    # Walk through the first directory
    for root, _, files in os.walk(dir1_path):
        rel_root = Path(root).relative_to(dir1_path)
        
        for fp in files:
            rel_path = Path(rel_root, fp)
            path1 = Path(dir1_path, rel_path)
            path2 = Path(dir2_path, rel_path)

            if not path2.exists():
                error(f"{rel_path} does not exist in {dir2_path}")
                errors_found = True

            elif path1.is_file() and path2.is_file():
                if not filecmp.cmp(str(path1), str(path2), shallow=False):
                    error(f"file contents for {rel_path} are different between {dir1_path} and {dir2_path}")
                    errors_found = True
            else:
                error(f"object type for {rel_path} are different between {dir1_path} and {dir2_path}")
                errors_found = True

    # Find files unique to the second directory
    for root, _, files in os.walk(dir2_path):
        rel_root = Path(root).relative_to(dir2_path)
        
        for fp in files:
            rel_path = Path(rel_root, fp)
            path1 = Path(dir1_path, rel_path)

            if not path1.exists():
                error(f"{rel_path} does not exist in {dir1_path}")
                errors_found = True

    if errors_found:
        error(f"directories {dir1_path} and {dir2_path} are not identical...cannot continue.")
        syst.exit(1)

def error(msg):
    print("ERROR:", msg, file=sys.stderr)

def extract_zip(zip_path, extract_dir):
    # Ensure the extraction directory exists
    extract_dir.mkdir(parents=True)
    
    # Extract all files
    with zipfile.ZipFile(zip_path, 'r') as zip_ref:
        zip_ref.extractall(extract_dir)

def get_size_category(path):
    size = path.stat().st_size

    if size < TINY_MAX:
        return "tiny"
    elif size < SMALL_MAX:
        return "small"
    elif size < MEDIUM_MAX:
        return "medium"
    elif size < LARGE_MAX:
        return "large"
    else:
        return "huge"

def ws_clean(text):
    # should be pretty good cross-platform to remove all whitespace
    return "".join(text.split())

def run_sut(sut_args):
    command = [ 'bash', SUT ]
    # positional parameters
    command.extend(sut_args)

    try:
        # Run the command with timeout and output capture
        result = subprocess.run(
            command,
            capture_output=True,
            text=True,
            check=False,          # Prevent CalledProcessError if return code != 0
            timeout=SUT_TIMEOUT_SEC      # Raises TimeoutExpired if process takes too long
        )

        # Process completed, result is in the exit_code
        return {
            'stdout': result.stdout,
            'stderr': result.stderr,
            'exit_code': result.returncode
        }
        
    except TimeoutExpired as e:
        # Command took too long to complete
        return {
            'stdout': None,
            'stderr': f'Command timed out after {SUT_TIMEOUT_SEC} seconds',
            'exit_code': -1
        }
        
    except FileNotFoundError:
        # Command executable not found
        return {
            'stdout': None,
            'stderr': f'Command not found: {command[0]}',
            'exit_code': -1
        }

def test_fail_simple(msg):
    global g_test_count, g_test_failures

    g_test_count += 1
    g_test_failures += 1
    print("FAIL:", ("=" * 10), msg)

def test_fail(name, expected, actual):
    global g_test_count, g_test_failures
    
    print("FAIL:", ("=" * 10), "START:", name)

    if expected['exit_code'] != actual['exit_code']:
        print("FAIL:", (" " * 15), "exit code: expected=<", expected['exit_code'], "> actual=<", actual['exit_code'], ">")

    e_clean = ws_clean(expected['stdout'])
    a_clean = ws_clean(actual['stdout'])

    if e_clean != a_clean:
        print("stdout EXPECTED (whitespace ignored):", (" " * 15))
        print(expected['stdout'])
        print("stdout ACTUAL:", (" " * 15))
        print(actual['stdout'])

    e_clean = ws_clean(expected['stderr'])
    a_clean = ws_clean(actual['stderr'])

    if e_clean != a_clean:
        print("stderr EXPECTED (whitespace ignored):", (" " * 15))
        print(expected['stderr'])
        print("stderr ACTUAL:", (" " * 15))
        print(actual['stderr'])

    print("FAIL:", ("=" * 10), "END:", name)
    print()

    g_test_count += 1
    g_test_failures += 1

def test_pass(msg):
    global g_test_count
    
    g_test_count += 1
    print("PASS:", ("=" * 10), msg)
    #print(".", end='')

def test_sut(name, params, expected_exit_code, expected_stdout, expected_stderr):
    expected = {
        'exit_code' : expected_exit_code,
        'stdout' : expected_stdout,
        'stderr' : expected_stderr,
    }
    # clean the whitespace from the expected values
    expected_stdout = ws_clean(expected_stdout)
    expected_stderr = ws_clean(expected_stderr)

    actual = run_sut(params)

    # clean the whitespace form the actual values
    actual_exit_code = actual['exit_code']
    actual_stdout = ws_clean(actual['stdout'])
    actual_stderr = ws_clean(actual['stderr'])

    if actual_exit_code != expected_exit_code or actual_stdout != expected_stdout or actual_stderr != expected_stderr:
        test_fail(name, expected, actual)
        return False
    else:
        test_pass(name)
        return True

# ========== Test case functions ===============================================

def test_case_usage(name, tmpdir):
    exit_code = RC_SUCCESS
    stdout = ""
    stderr = """organize_files.sh -h | [-d] [-n] <source-directory> <destination-directory>
    -h   print help message and exit
    -d   turn on debug messaging; twice for shell tracing
    -n   dry-run; do not create or change <destination-directory>
"""
    test_sut(name, ['-h'], exit_code, stdout, stderr)

def test_case_no_args(name, tmpdir):
    exit_code = RC_SOURCE_INVALID
    stdout = ''
    stderr = """ERROR: source-directory is required
organize_files.sh -h | [-d] [-n] <source-directory> <destination-directory>
    -h   print help message and exit
    -d   turn on debug messaging; twice for shell tracing
    -n   dry-run; do not create or change <destination-directory>
"""
    test_sut(name, [], exit_code, stdout, stderr)

def test_case_invalid_arg(name, tmpdir):
    exit_code = RC_INVALID_ARG
    stdout = ''
    stderr = 'ERROR: invalid option: -z'
    test_sut(name, [ '-z' ], exit_code, stdout, stderr)

def test_case_empty_source_dir(name, tmpdir):
    exit_code = RC_SOURCE_INVALID
    stdout = ''
    stderr = """ERROR: source-directory is required
organize_files.sh -h | [-d] [-n] <source-directory> <destination-directory>
    -h   print help message and exit
    -d   turn on debug messaging; twice for shell tracing
    -n   dry-run; do not create or change <destination-directory>"""
    
    test_sut(name, [ '', 'something' ], exit_code, stdout, stderr)

def test_case_invalid_source_dir(name, tmpdir):
    exit_code = RC_SOURCE_INVALID
    stdout = ''
    stderr = 'ERROR: source directory must be a directory: does_not_exist'
    
    test_sut(name, [ 'does_not_exist', 'something' ], exit_code, stdout, stderr)

def test_case_empty_dest_dir(name, tmpdir):
    exit_code = RC_DEST_INVALID
    stdout = ''
    stderr = """ERROR: destination-directory is required
organize_files.sh -h | [-d] [-n] <source-directory> <destination-directory>
    -h   print help message and exit
    -d   turn on debug messaging; twice for shell tracing
    -n   dry-run; do not create or change <destination-directory>"""

    # create a temporary directory
    src_dir = Path(tmpdir, "source_dir")
    src_dir.mkdir(parents=True)

    # call with source directory and empty dest dir
    test_sut(name, [ src_dir, '' ], exit_code, stdout, stderr)
 
def test_case_same_dest_dir(name, tmpdir):
    exit_code = RC_DEST_INVALID
    stdout = ''
    stderr = 'ERROR: source and destination directories must be different'

    # create a temporary directory
    src_dir = Path(tmpdir, "source_dir")
    src_dir.mkdir(parents=True)

    # call with the same directory for source and dest
    test_sut(name, [ src_dir, src_dir ], exit_code, stdout, stderr)

def test_case_valid_empty_source_dir_dry_run(name, tmpdir):
    # create a temporary directory
    src_dir = Path(tmpdir, "source_dir")
    src_dir.mkdir(parents=True)

    dest_dir = Path(tmpdir, "dest_dir")

    exit_code = RC_SUCCESS
    stdout = f'INFO: dry-run: mkdir {dest_dir}'
    stderr = ''

    # call with the same directory for source and dest
    test_sut(name, [ "-n", src_dir, dest_dir ], exit_code, stdout, stderr)
    
    # additional assertions
    assert_path_not_exists(name, dest_dir)

 
def test_case_valid_empty_source_dir_wet_run(name, tmpdir):
    # create a temporary directory
    src_dir = Path(tmpdir, "source_dir")
    src_dir.mkdir(parents=True)

    dest_dir = Path(tmpdir, "dest_dir")
    dest_dir.mkdir(parents=True)

    exit_code = RC_SUCCESS
    stdout = ''
    stderr = f''

    # call with the same directory for source and dest
    test_sut(name, [ src_dir, dest_dir ], exit_code, stdout, stderr)
    
    # additional assertions
    assert_dir_exists(name, dest_dir)

def test_case_empty_source_dir_non_empty_dest_dir_dry_run(name, tmpdir):
    # create a temporary directory
    src_dir = Path(tmpdir, "source_dir")
    src_dir.mkdir(parents=True)

    dest_dir = Path(tmpdir, "dest_dir")
    dest_dir.mkdir(parents=True)

    # make a directory within dest_dir
    dest_dir_child = Path(dest_dir, "existing_folder")
    dest_dir_child.mkdir(parents=True)

    dest_dir_file = Path(dest_dir, "existing_file.txt")
    dest_dir_file.touch()

    exit_code = RC_SUCCESS
    stdout = f"""INFO: dry-run: rm -rf {dest_dir}
INFO: dry-run: mkdir {dest_dir}"""
    stderr = ''

    # call with the same directory for source and dest
    test_sut(name, [ "-n", src_dir, dest_dir ], exit_code, stdout, stderr)
    
    # additional assertions
    assert_dir_exists(name, dest_dir)
    assert_dir_exists(name, dest_dir_child)
    assert_file_exists(name, dest_dir_file)

def test_case_empty_source_dir_non_empty_dest_dir_wet_run(name, tmpdir):
    # create a temporary directory
    src_dir = Path(tmpdir, "source_dir")
    src_dir.mkdir(parents=True)

    dest_dir = Path(tmpdir, "dest_dir")
    dest_dir.mkdir(parents=True)

    # make a directory within dest_dir
    dest_dir_child = Path(dest_dir, "existing_folder")
    dest_dir_child.mkdir(parents=True)

    dest_dir_file = Path(dest_dir, "existing_file.txt")
    dest_dir_file.touch()

    exit_code = RC_SUCCESS
    stdout = ''
    stderr = ''

    # call with the same directory for source and dest
    test_sut(name, [ src_dir, dest_dir ], exit_code, stdout, stderr)
    
    # additional assertions
    assert_dir_exists(name, dest_dir)
    assert_path_not_exists(name, dest_dir_child)
    assert_path_not_exists(name, dest_dir_file)
    
def evaluate_zip_file(name, tmpdir):
    # extract once to have a clean copy of the ZIP contents
    zip_dir = Path(tmpdir, "original_zip")
    extract_zip(g_zip_file, zip_dir)
    
    # extract into the source_dir
    src_dir = Path(tmpdir, "source_dir")
    extract_zip(g_zip_file, src_dir)

    dest_dir = Path(tmpdir, "dest_dir")

    exit_code = RC_SUCCESS
    stdout = None # ignore the standard output for this one
    stderr = ''

    # call with the same directory for source and dest
    result = run_sut([ src_dir, dest_dir ])

    # make sure the files in the src_dir have not changed w.r.t. the
    # original zip if there is a change in the src_dir, the script
    # will exit immediately.
    ensure_exact_trees(zip_dir, src_dir)

    if result['exit_code'] != RC_SUCCESS:
        error_msg(f"script exited with: {result['exit_code']}")
        error_msg(f"files are in {tmpdir}")
        error_msg(f"script stdout:")
        print(result['stdout'], file=sys.stderr)
        error_msg(f"script stderr:")
        print(result['stderr'], file=sys.stderr)
        sys.exit(1)

    # now we have to make sure that all files in the source directory
    # are accurately categorized in the destination directory
    for root, _, files in os.walk(src_dir):
        rel_root = Path(root).relative_to(src_dir)
        
        for fp in files:
            rel_path = Path(rel_root, fp)
            src_path = Path(src_dir, rel_path)

            size_category = get_size_category(src_path)
            dest_path = Path(dest_dir, size_category, src_path.name)

            # check the symlink is in the correct size directory
            assert_symlink_exists(name, dest_path)

            # make sure the symlink refers back to the file in the
            # source directory
            if dest_path.is_symlink():
                target = dest_path.readlink()
            else:
                target = Path('/dev/null')
                
            assert_samefile(name, src_path, target)

    # in the dest_dir, file-like objects must be symlinks, and the
    # targets of the symlinks must be within the src_dir
    for root, _, files in os.walk(dest_dir):
        rel_root = Path(root).relative_to(dest_dir)
        
        for fp in files:
            rel_path = Path(rel_root, fp)
            dest_path = Path(dest_dir, rel_path)

            # check the symlink is in the correct size directory
            assert_symlink_exists(name, dest_path)

            # make sure the symlink refers back to the file in the
            # source directory
            target = dest_path.readlink()
            assert_child_of(name, src_dir, target)

def main():
    global g_test_count, g_test_failures, g_tmp_folder, g_zip_file

    if len(sys.argv) not in (1, 2):
        print("ERROR: usage: python grader.py [<ZipFileName>]", file=sys.stderr)
        sys.exit(1)

    # ============ Test Cases
    
    # find any functions in this module whose name starts with test_case
    current_module = sys.modules[__name__]
    test_cases = [ (name, obj) for name, obj in current_module.__dict__.items() if inspect.isfunction(obj) and name.startswith("test_case_") ]

    for func_name, func in test_cases:
        name = func_name[len("test_case_"):]
        # get the tmpdir
        tmpdir = Path(g_tmp_folder, name)
        # call the function
        func(name, tmpdir)

    # calculate the grade
    passed = g_test_count - g_test_failures
    tc_grade = (100.0 * passed) / (1.0 * g_test_count )
    tc_failures = (g_test_failures > 0)
    print()
    print(f"TEST-CASE RESULT: passed {passed} out of {g_test_count} test cases: {tc_grade}")

    # ============ Do ZIP evaluation
    if len(sys.argv) == 2:
        g_zip_file = Path(sys.argv[1])

        if not g_zip_file.is_file():
            print(f"ERROR: zip-file does not exist: {g_zip_file}")
            sys.exit(1)

        # reset the counters for ZIP
        g_test_count = 0
        g_test_failures = 0

        tmpdir = Path(g_tmp_folder, g_zip_file)
        evaluate_zip_file(str(g_zip_file), tmpdir)

        # calculate the grade
        passed = g_test_count - g_test_failures
        zip_grade = (100.0 * passed) / (1.0 * g_test_count )
        print()
        print(f"ZIP-FILE RESULT: passed {passed} out of {g_test_count} test cases: {zip_grade}")
        print()
        overall = sum( (tc_grade, zip_grade) ) / 2.0
        print(f"OVERALL GRADE (average of test cases and zip): {overall}")


    # cleanup
    if tc_failures or g_test_failures != 0:
        print()
        print(f"NOTE: temporary directories and files have been left in the folder {g_tmp_folder}")
    else:
        shutil.rmtree(g_tmp_folder)
        
if __name__ == "__main__":
    main()
