#!/bin/bash

# Compile your project
make || exit 1

TEST_DIR="test_dir"
mkdir -p "$TEST_DIR"
cd "$TEST_DIR"

# Create some test files
touch file1 file2
mkdir dir1
ln -s file1 link1
mkfifo fifo1
python3 -c 'import socket as s; sock = s.socket(s.AF_UNIX); sock.bind("socket1")'

# Commands to test
COMMANDS=(
  ""
  "-l"
  "-la"
  "-al"
)

# Loop over commands
for cmd in "${COMMANDS[@]}"; do
  echo "Testing ls $cmd"

  ../ft_ls $cmd > my_output.txt 2>&1
  ls $cmd > sys_output.txt 2>&1

  if diff my_output.txt sys_output.txt > /dev/null; then
    echo "✅ PASS for ls $cmd"
  else
    echo "❌ FAIL for ls $cmd"
    echo "Differences:"
    diff -u my_output.txt sys_output.txt
  fi

#   # Optional: Check for memory leaks
#   valgrind --leak-check=full --error-exitcode=1 ../ft_ls $cmd > /dev/null 2>&1
#   if [ $? -eq 0 ]; then
#     echo "✅ No memory leaks for ls $cmd"
#   else
#     echo "❌ Memory leaks detected for ls $cmd"
#   fi

  echo "-----------------------------"
done

# Cleanup
cd ..
rm -rf "$TEST_DIR"
