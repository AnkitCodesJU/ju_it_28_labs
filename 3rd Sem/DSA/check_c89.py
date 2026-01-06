import glob
import subprocess
import os

target_dir = r"d:\Coding Playground\College\3rd Sem\DSA"
os.chdir(target_dir)
files = glob.glob("*.c")
results = []

print(f"Checking {len(files)} files in {target_dir}...")

for f in files:
    # Check for C89 compliance
    # -std=c89 : strict C89
    # -pedantic : strict ISO C conformance
    # -Werror : treat warnings as errors (to catch C99 extensions)
    # -Wno-comment : Allow // comments if you want, but old GCC might not. 
    # Actually user said "Ancient GCC". strict ANSI C does not support // comments.
    # But usually simple C compiler supports it. 
    # Let's stick to strict syntax for declaration first.
    # Using -fsyntax-only to speed up
    cmd = ["gcc", "-fsyntax-only", "-std=c89", "-pedantic", "-Werror", f]
    
    try:
        # We capture output to check what the error is
        subprocess.check_output(cmd, stderr=subprocess.STDOUT)
        results.append((f, "PASS"))
    except subprocess.CalledProcessError as e:
        # Get first line of error or first few lines
        output = e.output.decode('utf-8', errors='ignore')
        # We just want to know it failed
        first_error = output.strip().split('\n')[0] if output else "Unknown Error"
        results.append((f, f"FAIL"))

results.sort()
for f, res in results:
    print(f"{f} -> {res}")
