import os

def split_sql_file(input_file, output_dir):
    # 确保输出目录存在
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # 读取整个输入文件
    with open(input_file, 'r') as file:
        sql_content = file.read()

    # 以分号分割SQL查询，忽略空查询
    queries = [q.strip() for q in sql_content.split('\n\n\n') if q.strip()][1:]

    # 为每个查询创建一个新文件
    for i, query in enumerate(queries, start=1):
        output_file_path = os.path.join(output_dir, f'query{i}.sql')
        with open(output_file_path, 'w') as output_file:
            output_file.write(query)  

        print(f'Query {i} saved to {output_file_path}')

# file path
input_sql_file = '../query/all.sql'
output_directory = '../query'
split_sql_file(input_sql_file, output_directory)



