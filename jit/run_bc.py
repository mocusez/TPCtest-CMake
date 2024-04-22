import os
import subprocess
import time
from compile_bc import output_directory

def run_bc(output_path, jit_kind):
    start_time = time.time()  # 记录开始时间
    command = ['lli', '--jit-kind=' + jit_kind, output_path]
    result = subprocess.run(command, capture_output=True, text=True)
    end_time = time.time()  # 记录结束时间
    duration = end_time - start_time  # 计算运行时长
    return result, duration, jit_kind, output_path

if __name__ == "__main__":
    for filename in os.listdir(output_directory):
        if filename.endswith('.bc'):
            output_path = os.path.join(output_directory, filename)
            for jit_kind in ['orc', 'orc-lazy']:
                result, duration, jit_kind, output_path = run_bc(output_path, jit_kind)
                if result.returncode == 0:
                    print(f"Successfully ran {output_path} with {jit_kind} in {duration:.2f} seconds")
                else:
                    print(f"Error running {output_path} with {jit_kind}: {result.stderr}")
