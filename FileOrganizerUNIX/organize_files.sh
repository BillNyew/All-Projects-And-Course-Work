#!/bin/bash

RC_SUCCESS=0
RC_ERROR_ARG=2
RC_ERROR_SAME=3
RC_ERROR_INVALID_OPTION=1
RC_ERROR=1

get_file_size() {
    local f_path="$1"
    if stat --version &>/dev/null; then
        stat --format=%s "$f_path"
    else
        stat -f%z "$f_path"
    fi
}

debug_msg() {
    if [ "$DEBUG" -ge 1 ]; then
        echo "DEBUG: $@" >&2
    fi
}

dry_run_msg() {
    echo "INFO: dry-run: $@"
}

error_msg() {
    echo "ERROR: $@" >&2
}

get_size_category() {
    local size=$1
    if [ "$size" -le 1024 ]; then
        echo "tiny"
    elif [ "$size" -le 10240 ]; then
        echo "small"
    elif [ "$size" -le 102400 ]; then
        echo "medium"
    elif [ "$size" -le 1048576 ]; then
        echo "large"
    else
        echo "huge"
    fi
}

validate_args() {
    if [ -z "$SOURCE_DIR" ]; then
        error_msg "source-directory is required"
        print_help >&2
        echo "" >&2
        return $RC_ERROR_ARG
    fi

    if [ ! -d "$SOURCE_DIR" ]; then
        error_msg "source directory must be a directory: $SOURCE_DIR"
        return $RC_ERROR_ARG
    fi

    if [ -z "$DEST_DIR" ]; then
        error_msg "destination-directory is required"
        print_help >&2
        echo "" >&2
        return $RC_ERROR_SAME
    fi

    if [ "$SOURCE_DIR" == "$DEST_DIR" ]; then
        error_msg "source and destination directories must be different"
        return $RC_ERROR_SAME
    fi

    return $RC_SUCCESS
}

prepare_dest_dir() {
    if [ "$DRY_RUN" -eq 1 ]; then
        debug_msg "Dry run: skipping actual changes to dest dir."
        if [ -d "$DEST_DIR" ]; then
            dry_run_msg "rm -rf $DEST_DIR"
        fi
        dry_run_msg "mkdir $DEST_DIR"
        return $RC_SUCCESS
    fi

    if [ -d "$DEST_DIR" ]; then
        debug_msg "Removing existing dest dir."
        rm -rf "$DEST_DIR" || return $RC_ERROR
    fi

    debug_msg "Creating new dest dir."
    mkdir -p "$DEST_DIR" || return $RC_ERROR

    return $RC_SUCCESS
}

process_files() {
    find "$SOURCE_DIR" -type f | while read -r file; do
        size=$(get_file_size "$file")
        category=$(get_size_category "$size")

        target_dir="$DEST_DIR/$category"
        if [ ! -d "$target_dir" ]; then
            if [ "$DRY_RUN" -eq 1 ]; then
                dry_run_msg "mkdir $target_dir"
            else
                mkdir -p "$target_dir" || return $RC_ERROR
            fi
        fi

        link_name="$target_dir/$(basename "$file")"

        if [ "$DRY_RUN" -eq 1 ]; then
            dry_run_msg "ln -s $file $link_name"
        else
            ln -s "$file" "$link_name" || return $RC_ERROR
        fi
    done

    return $RC_SUCCESS
}

print_help() {
    echo "organize_files.sh -h | [-d] [-n] <source-directory> <destination-directory>" >&2
    echo "    -h   print help message and exit" >&2
    echo "    -d   turn on debug messaging; twice for shell tracing" >&2
    echo "    -n   dry-run; do not create or change <destination-directory>" >&2
}

main() {
    DRY_RUN=0
    DEBUG=0

    while getopts ":hnd" opt; do
        case $opt in
            h)
                print_help >&2
                exit 0
                ;;
            n)
                DRY_RUN=1
                ;;
            d)
                DEBUG=$((DEBUG + 1))
                ;;
            ?)
                error_msg "invalid option: -$OPTARG"
                exit $RC_ERROR_INVALID_OPTION
                ;;
        esac
    done

    shift $((OPTIND - 1))

    SOURCE_DIR="$1"
    DEST_DIR="$2"

    if [ "$DEBUG" -ge 2 ]; then
        set -x
    fi

    validate_args || exit $?
    prepare_dest_dir || exit $?
    process_files || exit $?

    exit 0
}

main "$@"
