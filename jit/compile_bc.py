import os
import subprocess
from concurrent.futures import ThreadPoolExecutor, as_completed

# 设置输入和输出目录
src_directory = 'tests'
include_directory = 'include'
output_directory = 'jit/jit_output'

# 确保输出目录存在
os.makedirs(output_directory, exist_ok=True)

def compile_cpp(src_path, output_path):
    command = [
        'clang', '-emit-llvm', '-c', src_path,
        '-I', include_directory,
        '-o', output_path
    ]
    return subprocess.run(command, capture_output=True, text=True), output_path

if __name__ == "__main__":
    # 使用线程池来并行处理文件
    with ThreadPoolExecutor() as executor:
        futures = []
        for filename in os.listdir(src_directory):
            if filename.endswith('.cpp'):
                src_path = os.path.join(src_directory, filename)
                output_file = os.path.splitext(filename)[0] + '.bc'
                output_path = os.path.join(output_directory, output_file)
                # 提交任务到线程池
                futures.append(executor.submit(compile_cpp, src_path, output_path))

        # 等待所有任务完成并处理结果
        for future in as_completed(futures):
            result, output_path = future.result()
            if result.returncode == 0:
                print(f"Successfully compiled {output_path}")
            else:
                print(f"Error compiling {output_path}: {result.stderr}")
